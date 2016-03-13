/*
  engine_core.cpp is part of RED-ENGINE - An Object-Oriented game
  engine based on Allegro5 Copyright (C) 2015 - 2016 Anthony REY

  This program is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "engine_core.hpp"

namespace RedEngine
{

    //##############  Manager class ############## 
    Manager::Manager(int virtual_width, int virtual_height,
		     int real_width, int real_height, const char* title,
		     bool isFullscreen, bool isResizable)
    {
	if(virtual_width < 640)
	    virtual_width = 640;
	if(virtual_height < 480)
	    virtual_height = 480;

	this->virtual_width = virtual_width;
	this->virtual_height = virtual_height;

	if(real_height < virtual_height)
	    this->real_height = virtual_height;
	if(real_width < virtual_width)
	    this->real_width = virtual_width;

	this->real_width = real_width;
	this->real_height = real_height;

	running = true;
       
	//Allegro
	display = nullptr;
	event_queue = nullptr;
	timer = nullptr;
	redraw = true;
	this->isFullscreen = isFullscreen;
	this->isResizable = isResizable;

	this->title = title;

	init();
    }

    Manager::~Manager()
    {
	if(display != nullptr)
	    al_destroy_display(display);
	if(event_queue != nullptr)
	    al_destroy_event_queue(event_queue);
	if(timer != nullptr)
	    al_destroy_timer(timer);

	//clean yo shit man, damn
	//we clean the scene stack
	while (!game_scenes.empty())
	{
	    GameScene* toDelete = game_scenes.top();
	    game_scenes.pop();

	    if(toDelete != nullptr)
		delete toDelete;
	}

	//let the dataPool clean itself (destructor, will do to the job)
	delete datapool;
		

	//it seems that addons are automatically killed at the end
    }

    void Manager::init()
    {
	//let's create the datapool first, so if it bug, we don't have a nullptr ref 
	datapool = new DataPool();
	soundEngine = new SoundEngine(datapool);

	//Initializing allegro
	if (!al_init())
	    stop(AL_INIT_FAILED);

	//initializing subsystems
	//If any of them fail we exit with addon_init_failed status
	if ( !(al_install_keyboard() && al_init_image_addon()
	       && al_init_primitives_addon()
	       && al_install_audio() && al_init_acodec_addon()
	       && al_install_audio() ))
	{
	    stop(ADDON_INIT_FAILED);
	}

	al_init_font_addon();
	al_init_ttf_addon();
	al_init_acodec_addon();

	//reserving samples for sounds and music
	if(!al_reserve_samples(64))
	{
	    exit(CANNOT_RESERVE_SAMPLES);
	}

	if(isFullscreen)
	{
	    //TODO upon quitting there is an exception on OSX
	    al_set_new_display_flags(ALLEGRO_FULLSCREEN_WINDOW);
	}
		
	if(isResizable)
	{
	    al_set_new_display_flags(al_get_new_display_flags() | ALLEGRO_RESIZABLE);
	}

	display = al_create_display(real_width, real_height);

	if(!display)
	    stop(DISPLAY_NULL);

	//TODO not working on osx ...
	al_set_window_title(display, title);

	timer = al_create_timer(1.0 / FPS);

	event_queue = al_create_event_queue();
	al_register_event_source(event_queue, al_get_keyboard_event_source());
	al_register_event_source(event_queue, al_get_timer_event_source(timer));
	al_register_event_source(event_queue, al_get_display_event_source(display));

	bkg_color = al_map_rgb(0,0,0);
    }

    void Manager::start()
    {
	if (game_scenes.empty())
	    stop(EMPTY_SCENE_STACK);

	al_start_timer(timer);
				
	while(running)
	{

	    al_wait_for_event(event_queue, &ev);
	    //update
	    if (ev.type == ALLEGRO_EVENT_TIMER)
	    {
		update(&ev);		
		redraw = true;	
	    }
	    else if(ev.type == ALLEGRO_EVENT_KEY_DOWN 
		    || ev.type == ALLEGRO_EVENT_KEY_UP 
		    || ev.type == ALLEGRO_EVENT_KEY_CHAR)
	    {
		keyboard_engine.update(&ev);	
	    }


	    //drawing
	    if (al_is_event_queue_empty(event_queue) && redraw)
	    {
		draw();
		redraw = false;
	    }
	}
    }

    void Manager::stop(int code)
    {
	running = false;
	if(code != PLAYER_EXIT)
	    std::cerr << "STOPPED - " << "Stop Code : " <<  code << std::endl;
    }

    void Manager::update(ALLEGRO_EVENT* ev)
    {
	game_scenes.top()->updateComponents();
	game_scenes.top()->update();
    }

    void Manager::drawAll()
    {	
	game_scenes.top()->drawComponentsBack();
	game_scenes.top()->draw();
	game_scenes.top()->drawComponentsFront();
    }

    void Manager::draw()
    {
	//drawing on a bmp
	ALLEGRO_BITMAP* bmp = al_create_bitmap(virtual_width, virtual_height);
	al_set_target_bitmap(bmp);
	al_clear_to_color(bkg_color);

	drawAll();
		
	//resizing and drawing
	//TODO this might be pretty slow ?
	//TODO harcoded for 4/3 to 16/9
	//aspect ratio calculations
	//int width = (real_width / 4 ) * 3;

	//redrawing the scaled bitmap to the backbuffer
	//TODO add black box if 4/3 on a 16/9 screen
	al_set_target_backbuffer(this->display);
	/*al_draw_scaled_bitmap(bmp, 0, 0,
	  virtual_width,virtual_height,
	  (width / 3) / 2, 0 ,
	  width, real_height, 0); */
	al_clear_to_color(bkg_color);


        //TODO real_width and height don't get updated on OSX !!
        //To be precise, it seems that Windows is resizing the whole render
        //This might be because of DirectX

	al_draw_scaled_bitmap(bmp, 0, 0, 
			      virtual_width, virtual_height,
			      0,0, real_width, real_height, 0);

	al_flip_display();	

	al_destroy_bitmap(bmp);
    }

    void Manager::pushScene(GameScene* scene)
    {
	scene->setManager(this);
	scene->init();
	game_scenes.push(scene);
    }

    void Manager::popScene()
    {
	GameScene* scene = game_scenes.top();
	game_scenes.pop();
	delete scene;
    }

    SoundEngine* Manager::getSoundEngine() {
	return soundEngine;
    }

    ALLEGRO_BITMAP*& Manager::getSprite(std::string key)
    {
	//exception handling needed
	return datapool->getSprite(key);
    }

    ALLEGRO_SAMPLE* Manager::getSound(std::string key)
    {
	//exception handling needed
	return datapool->getSound(key);
    }

    ALLEGRO_FONT* Manager::getFont(std::string key)
    {
	//exception handling needed
	return datapool->getFont(key);
    }

    Sprite* Manager::createSprite(std::string key)
    {
	return new Sprite(getSprite(key));
    }

    Sprite* Manager::createSprite(std::string key, int x, int y)
    {
	return new Sprite(getSprite(key), x, y);
    }

    Sprite* Manager::createSprite(std::string key, int pos_x, 
				  int pos_y, int size_x, int size_y,
				  int frames_per_directions,
				  int frame_delay)
    {

	return new Sprite(getSprite(key),
			  pos_x, pos_y, size_x, size_y,
			  frames_per_directions, frame_delay);
    }

    //Mutators inline
    void Manager::addSprite(std::string key, const char* file)
    {	
	try
	{
	    datapool->addSprite(key, file);
	}
	catch(StopCodes e)
	{
	    stop(e);
	}
		
    }

    void Manager::addSound(std::string key, const char* file)
    {
	try
	{
	    datapool->addSound(key, file);
	}
	catch(StopCodes e)
	{
	    stop(e);
	}
			
    }

    void Manager::addFont(std::string key, const char* file, unsigned int size)
    {
	try
	{
	    datapool->addFont(key, file, size);	
	}
	catch(StopCodes e)
	{
	    stop(e);
	}		
    }

    void Manager::setBackgroundColor(unsigned int r, unsigned int g, unsigned int b)
    {
	if(r <= 255 && g <= 255 && b <= 255)
	    bkg_color = al_map_rgb(r,g,b);
	else
	    stop(COLOR_CODE_ERROR);
    }

    int Manager::getWidth()
    {
	return virtual_width;
    }

    int Manager::getHeight()
    {
	return virtual_height;
    }
	
    void Manager::transformTranslate(int x, int y)
    {
	al_identity_transform(&camera_transform);
        al_translate_transform(&camera_transform, x, y);
        al_use_transform(&camera_transform);
    }
	
    void Manager::resetTransformTranslate()
    {
	transformTranslate(0,0);
    }

    KeyboardEngine *Manager::getKeyBoardEngine() {
	return &keyboard_engine;
    }
}

