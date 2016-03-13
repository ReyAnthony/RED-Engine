/*
  graphic_engine.cpp is part of RED-ENGINE - An Object-Oriented game
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

#include "graphic_engine.hpp"

namespace RedEngine
{

    GraphicEngine::GraphicEngine(int virtual_width, int virtual_height,
				 int real_width, int real_height,
				 const char* title,
				 bool isFullscreen, bool isResizable)
    {
	this->virtual_width = virtual_width;
	this->virtual_height = virtual_height;
	this->real_width = real_width;
	this->real_height = real_height;

	this->title = title;
	this->isFullscreen = isFullscreen;
	this->isResizable = isResizable;
	init();
    }

    void GraphicEngine::init()
    {
	//Initializing allegro
	if (!al_init())
	    stop(AL_INIT_FAILED);

	//TODO they should be in the related subsystem...
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
	    al_set_new_display_flags(al_get_new_display_flags()
				     | ALLEGRO_RESIZABLE);
	}

	display = al_create_display(real_width, real_height);

	if(!display)
	    stop(DISPLAY_NULL);

	//TODO not working on osx ...
	al_set_window_title(display, title);
	bkg_color = al_map_rgb(0,0,0);

	timer = al_create_timer(1.0 / FPS);
	event_queue = al_create_event_queue();
	al_register_event_source(event_queue,
				 al_get_keyboard_event_source());
	al_register_event_source(event_queue,
				 al_get_timer_event_source(timer));
	al_register_event_source(event_queue,
				 al_get_display_event_source(display));

    }

     void GraphicEngine::update(GameScene *scene)
    {
	scene->updateComponents();
	game_scenes.top()->update();
    }

    void GraphicEngine::drawAll(GameScene* scene)
    {	
	game_scenes.top()->drawComponentsBack();
	game_scenes.top()->draw();
	game_scenes.top()->drawComponentsFront();
    }

    void GraphicEngine::draw(GameScene *scene)
    {
	//drawing on a bmp
	ALLEGRO_BITMAP* bmp = al_create_bitmap(virtual_width, virtual_height);
	al_set_target_bitmap(bmp);
	al_clear_to_color(bkg_color);

	drawAll(scene);
		
	//redrawing the scaled bitmap to the backbuffer
	//TODO add black box if 4/3 on a 16/9 screen
	al_set_target_backbuffer(this->display);
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

    void GraphicEngine::stop(int errorCode)
    {
	//do nothing
	//should throw an exception and be catched by manager
    }

    
    void GraphicEngine::setBackgroundColor(unsigned int r,
					   unsigned int g,
					   unsigned int b)
    {
	if(r <= 255 && g <= 255 && b <= 255)
	    bkg_color = al_map_rgb(r,g,b);
	else
	    stop(COLOR_CODE_ERROR);
	//stop won't work here
    }
    
    void GraphicEngine::transformTranslate(int x, int y)
    {
	al_identity_transform(&camera_transform);
        al_translate_transform(&camera_transform, x, y);
        al_use_transform(&camera_transform);
    }
	
    void GraphicEngine::resetTransformTranslate()
    {
	transformTranslate(0,0);
    }

    int GraphicEngine::getHeight()
    {
	return virtual_height;
    }

    int GraphicEngine::getWidth()
    {
	return virtual_width;
    }    
}
