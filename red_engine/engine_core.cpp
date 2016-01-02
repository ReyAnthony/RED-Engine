/*
	engine_core.cpp is part of
	RED-ENGINE - An Object-Oriented game engine based on Allegro5
	Copyright (C) 2015 Anthony REY

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
	Manager::Manager(int width, int height, const char* title)
	{
		if(width < 640)
			width = 640;

		if(height < 480)
			height = 480;

		this->width = width;
		this->height = height;
		running = true;

		//Allegro
		display = nullptr;
		event_queue = nullptr;
		timer = nullptr;
		redraw = true;

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
		soundEngine = new SoundEngine(this);

		//Initializing allegro
		if (!al_init())
			stop(AL_INIT_FAILED);

		//initializing subsystems
		//If any of them fail we exit with addon_init_failed status
		if ( !(al_install_keyboard() && al_init_image_addon() && al_init_primitives_addon()
			 && al_install_audio() && al_init_acodec_addon() && al_install_audio() ))
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

		//TODO add params
		//al_set_new_display_flags(ALLEGRO_FULLSCREEN_WINDOW);

		display = al_create_display(width, height);

		if(!display)
			stop(DISPLAY_NULL);

		//not working on osx ...
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
			else
			{
				keyboard_engine.update(&ev);
				if (keyboard_engine.isKeyPressed(ALLEGRO_KEY_ESCAPE))
				{
					stop(PLAYER_EXIT);
				}
			}

			//drawing
			if (al_is_event_queue_empty(event_queue) && redraw)
			{
				redraw = false;
				draw();
			}
		}
	}

	void Manager::stop(int code)
	{
		running = false;
		if(code != PLAYER_EXIT)
			std::cout << "STOPPED - " << "Stop Code : " <<  code << std::endl;
	}

	void Manager::update(ALLEGRO_EVENT* ev)
	{
		game_scenes.top()->updateComponents();
		game_scenes.top()->update();
	}

	void Manager::draw()
	{	
		
		game_scenes.top()->drawComponentsBack();
		game_scenes.top()->draw();
		game_scenes.top()->drawComponentsFront();

		al_flip_display();
		al_clear_to_color(bkg_color);
	}

	void Manager::pushScene(GameScene* scene)
	{
		scene->setManager(this);
		scene->init();
		game_scenes.push(scene);
	}

	void Manager::popScene()
	{
		game_scenes.pop();
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
				int pos_y, int size_x, int size_y, int frames_per_directions,
				int frame_delay)
	{

		return new Sprite(getSprite(key), pos_x, pos_y, size_x, size_y, frames_per_directions, frame_delay);
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
		return width;
	}

	int Manager::getHeight()
	{
		return height;
	}

	//############## GameScene class ############## 
	GameScene::~GameScene()
	{}

	Manager* GameScene::getManager()
	{
		return this->manager;
	}

	void GameScene::setManager(Manager* manager)
	{
		this->manager = manager;
	}

	void GameScene::addComponent(GameComponent* component)
	{
		//TODO guards
		component->setManager(this->getManager());
		component->init();
		components.push_back(component);
	}

	void GameScene::drawComponentsBack()
	{
		std::list<RedEngine::GameComponent*>::const_iterator iterator;
		for (iterator = components.begin(); iterator != components.end(); ++iterator) {

			if( (*iterator)->getIsBack()) 
				(*iterator)->draw();
		}
	}	
	
	void GameScene::drawComponentsFront()
	{
		std::list<RedEngine::GameComponent*>::const_iterator iterator;
		for (iterator = components.begin(); iterator != components.end(); ++iterator) {
			
			if( ! (*iterator)->getIsBack()) 
				(*iterator)->draw();
		}

	}

	void GameScene::updateComponents()
	{
		std::list<RedEngine::GameComponent*>::const_iterator iterator;
		for (iterator = components.begin(); iterator != components.end(); ++iterator) {

				(*iterator)->update();
		}
	}

	//####### GameComponent ########

	GameComponent::GameComponent(bool isBack)
	{
		this->isBack = isBack;
	} 

	GameComponent::~GameComponent()
	{

	}

	bool GameComponent::getIsBack()
	{
		return isBack;
	}

	void GameComponent::setManager(Manager* manager)
	{
		this->manager = manager;
	}

	Manager* GameComponent::getManager()
	{
		return manager;
	}

	KeyboardEngine *Manager::getKeyBoardEngine() {
		return &keyboard_engine;
	}

	//############## Datapool class ############## 
	DataPool::DataPool()
	{
	}

	//TODO
	DataPool::~DataPool()
	{
		//must clean data !!!
	}
	//Accessors
	ALLEGRO_BITMAP*& DataPool::getSprite(std::string key)
	{
		//exception handling needed
		return sprites_map[key];
	}

	ALLEGRO_SAMPLE* DataPool::getSound(std::string key)
	{
		//exception handling needed
		return sounds_map[key];
	}

	ALLEGRO_FONT* DataPool::getFont(std::string key)
	{
		//exception handling needed
		return fonts_map[key];
	}

	//Mutators
	void DataPool::addSprite(std::string key, const char* file)
	{
		ALLEGRO_BITMAP* sprite = al_load_bitmap(file);
		al_convert_mask_to_alpha(sprite, al_map_rgb(0,0,0));
		if(nullptr != sprite)
		{
			sprites_map[key] = sprite;
		}
		else
		{
			throw RES_NOT_FOUND;
		}
		
	}

	void DataPool::addSound(std::string key, const char* file)
	{
		ALLEGRO_SAMPLE* sample = al_load_sample(file);
		if(nullptr != sample)
		{
			sounds_map[key] = sample;
		}
		else
		{
			throw RES_NOT_FOUND;
		}
		
	}

	void DataPool::addFont(std::string key, const char* file, unsigned int size)
	{
		ALLEGRO_FONT* font = al_load_ttf_font(file, size , 0);
		if(nullptr != font)
		{
			fonts_map[key] = font;
		}
		else
		{
			throw RES_NOT_FOUND;
		}
		
	}

	void DataPool::deleteSprite(std::string key)
	{
		//check if key exist
	}

	void DataPool::deleteSound(std::string key)
	{

	}
	
	void DataPool::deleteFont(std::string key)
	{

	}

	//################# Sprite class #################### 
	Sprite::Sprite(ALLEGRO_BITMAP*& sprite) : sprite(sprite)
	{
		if(sprite == nullptr)
		{
			throw RES_NOT_FOUND;
		}

		pos_x = 0;
		pos_y = 0;
		
	}

	Sprite::Sprite(ALLEGRO_BITMAP*& sprite, int pos_x, int pos_y) : sprite(sprite)
	{
		if(sprite == nullptr)
		{
			throw RES_NOT_FOUND;
		}
	
		this->pos_y = pos_y;
		this->pos_x = pos_x;
		
	}

	Sprite::Sprite(ALLEGRO_BITMAP*& sprite, int pos_x, 
				int pos_y, int size_x, int size_y, int frames_per_directions,
				int frame_delay) : sprite(sprite)
	{
		if(sprite == nullptr)
		{
			throw RES_NOT_FOUND;
		}
	
		this->pos_y = pos_y;
		this->pos_x = pos_x;
		
		this->size_x = size_x;
		this->size_y = size_y;
		this->frames_per_directions = frames_per_directions;
		this->frame_delay = frame_delay;

		this->is_animated = true;
	}

	void Sprite::setPosX(int pos_x)
	{
		this->pos_x = pos_x;
	}
	
	void Sprite::setPosY(int pos_y)
	{
		this->pos_y = pos_y;
	}

	int Sprite::getPosX()
	{
		return pos_x;
	}

	int Sprite::getPosY()
	{
		return pos_y;
	}

	void Sprite::setState(int state)
	{
		this->state = state;
	}

	void Sprite::switchAnimState(bool value)
	{
		is_animated = value;
	}

	void Sprite::draw()
	{
		//if is animated..
		if(is_animated)
		{
	 		if(frame_delay_counter <= frame_delay)
			 {
			 	//frame_delay is not in ms but in draw calls (this is dumb, YES)
			 	//usually 1 draw = 1/60 of sec 
			 	//so 60 = 1 sec ?
			 	frame_delay_counter++;
			 }
			 else
			 {
			 	
		 		frame_delay_counter = 0;
		 		if(current_frame < frames_per_directions - 1)
		 		{
		 			//next frame
		 			current_frame++;
		 		}
		 		else
		 		{
		 			//reset the anim
		 			current_frame = 0;
		 		}
			 }

			 al_draw_bitmap_region(sprite, 
			 	//define sprite of region
			 	(frames_per_directions * size_x * state)
			 	+
			 	//adding the current frame pos
			 	current_frame * size_x,
			 	0, size_x, size_y, pos_x, pos_y, 0); 

		}
		else
		{
			al_draw_bitmap_region(this->sprite,
			(frames_per_directions * size_x * state),	
			0, size_x, size_y, pos_x, pos_y, 0);
		}		 
	}

	Sprite::~Sprite()
	{
		//nothing do do for now ?
		//bmp are supposed to be managed by the pool
	}

	int Sprite::getSizeX() {
		return this->size_x;
	}

	int Sprite::getSizeY() {
		return this->size_y;
	}

	//##### SOUND ENGINE #####

	SoundEngine::SoundEngine(Manager* manager) {
		this->managerRef = manager;
	}

	SoundEngine::~SoundEngine() {

	}

	void SoundEngine::stopMusic() {

		al_stop_sample(&this->current_music);
	}

	void SoundEngine::startMusic(std::string res) {
		al_play_sample(managerRef->getSound(res),
					   1.0, 0,1.0, ALLEGRO_PLAYMODE_LOOP, &this->current_music);
	}

	void SoundEngine::playSound(std::string res) {
		al_play_sample(managerRef->getSound(res),
					   1.0, 0,1.0, ALLEGRO_PLAYMODE_ONCE, nullptr);
	}
}

