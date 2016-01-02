/*
	engine_core.hpp is part of
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

#ifndef Red_ENGINE_H
#define Red_ENGINE_H

#include <allegro5/allegro.h>
#include <allegro5/keyboard.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_image.h>

#include <iostream>
#include <stack>
#include <unordered_map>
#include <string>
#include <list>

#include "keyboard_engine.hpp"

namespace RedEngine
{

	enum StopCodes
	{
		PLAYER_EXIT, 			//0
		AL_INIT_FAILED, 		//1
		ADDON_INIT_FAILED,		//2
		DISPLAY_NULL,			//3
		EMPTY_SCENE_STACK,		//4
		RES_ADD_FAILED, 		//5
		COLOR_CODE_ERROR,		//6
		RES_NOT_FOUND,			//7
		EMPTY_LABEL,			//8
		ALREADY_USED_LABEL,  	//9
		CANNOT_RESERVE_SAMPLES //10

	};

	//forward declarations
	class DataPool;
	class Manager;
	class GameScene;
	class ScrollScene;
	class KeyboardEngine;
	class Sprite;
	class GameComponent;
	class ScreenKeyScrollerComponent;
	class SoundEngine;
	
	//##############  Manager class ############## 
	//This class manage the game 
	class Manager
	{
		public:
			Manager(int width, int height, const char* title);
			~Manager();

			//must be called after creating the class
			void start();

			void stop(int error_code);
			void pushScene(GameScene* scene);
			void popScene();

			//TODO REFERENCES and PRIVATE
			ALLEGRO_SAMPLE* getSound(std::string key);		
			ALLEGRO_FONT* getFont(std::string key);	

			//Mutators 
			//const char* cause allegro is C not C++
			void addSprite(std::string key, const char* file);
			void addSound(std::string key, const char* file);
			void addFont(std::string key, const char* file, unsigned int size);

			void setBackgroundColor(unsigned int r, unsigned int g, unsigned int b);

			int getWidth();
			int getHeight();

			//negate the need for a getSprite
			//it's mostly a factory i guess
			Sprite* createSprite(std::string key);
			Sprite* createSprite(std::string key, int x, int y);
			Sprite* createSprite(std::string key, int pos_x, 
				int pos_y, int size_x, int size_y, int frames_per_directions,
				int frame_delay);

			SoundEngine* getSoundEngine();
			KeyboardEngine* getKeyBoardEngine();

		private:
			//methods
			//called by the constructor
			void init();

			//they are calling the top of the stack
			void update(ALLEGRO_EVENT* ev);
			void draw();	

			//DataPool access
			//We use a reference so that when we deallocate it and nullptr it 
			//it becomes nullptr in sprite too
			ALLEGRO_BITMAP*& getSprite(std::string key);

			//scene at the top of the stack is played
			std::stack<GameScene*> game_scenes;

			//Other game related
			DataPool* datapool; //when forward declaring you can only use a pointer
			KeyboardEngine keyboard_engine;
			SoundEngine* soundEngine;

			//variables
			int width;
			int height;
			bool running;
			bool redraw;
			const char* title;

			//allegro
			ALLEGRO_DISPLAY* display;
			ALLEGRO_EVENT ev;
			ALLEGRO_EVENT_QUEUE* event_queue;
			ALLEGRO_TIMER* timer;

			//bkg color
			ALLEGRO_COLOR bkg_color;

			//constants
			static const int FPS = 60;
	};

	//##############  GameScene class ############## 
	//TODO rendering pipeline ?
	class GameScene
	{
		public:
			virtual ~GameScene() = 0;
			//init is called after set manager when pushing scene
			void virtual init() = 0;
			void virtual update() = 0;
			void virtual draw() = 0;

			//This setup is done auto by the manager when pushing the scene
			Manager* getManager();
			void addComponent(GameComponent* component);

			friend class Manager;
			void setManager(Manager* manager);

		private:

			//auto draw for components;
			void drawComponentsBack();
			void drawComponentsFront();
			void updateComponents();

			Manager* manager;
			std::list<GameComponent*> components;

	};

	class GameComponent
	{
		public:
			GameComponent(bool back);
			~GameComponent();
			bool getIsBack();

			virtual void init() =0;
			virtual void update() =0;
			virtual void draw() =0;

			friend class Manager;
			//when pushing into the manager, the GameScene will pass it into the method
			void setManager(Manager* manager);

		protected:
			Manager* getManager();

		private:
			//should it be drawn at the back ?
			bool isBack;
			Manager* manager;
	};

	//############## DataPool class ############## 
	//This class stores loaded data for later reuse
	class DataPool
	{
		public:

			//Accessors 
			ALLEGRO_BITMAP*& getSprite(std::string key);
			ALLEGRO_SAMPLE* getSound(std::string key);
			ALLEGRO_FONT* getFont(std::string key);

			//Mutators 
			void addSprite(std::string key, const char* file);
			void addSound(std::string key, const char* file);
			void addFont(std::string key, const char* file, unsigned int size);

			//be sure they are not used anymore before deleting
			void deleteSprite(std::string key);
			void deleteSound(std::string key);
			void deleteFont(std::string key);
			
		private:

			//SUCKY DESIGN FTW
			friend class Manager;
			DataPool();
			~DataPool(); 

			//Variables
			std::unordered_map<std::string, ALLEGRO_BITMAP*> sprites_map;
			std::unordered_map<std::string, ALLEGRO_SAMPLE*> sounds_map;
			std::unordered_map<std::string, ALLEGRO_FONT*> fonts_map;
	};

	enum SpriteDirections
	{
		W_DOWN = 0,
		W_UP = 1,
		W_RIGHT = 2,
		W_LEFT = 3,
		W_NOT = 4
	};
	//################# Sprite class ####################
	//This class represents a drawable 
	class Sprite 
	{
		public: 
		
			//Acessors and mutators
			void setPosX(int pos_x);
			void setPosY(int pos_y);
			int getPosX();
			int getPosY();
			int getSizeX();
			int getSizeY();

			void setState(int state);
			void switchAnimState(bool value);

			void draw();

		private:

			//SUCKY DESIGN FTW
			friend class Manager;
			Sprite(ALLEGRO_BITMAP*& sprite);
			Sprite(ALLEGRO_BITMAP*& sprite, int pos_x, int pos_y);
			Sprite(ALLEGRO_BITMAP*& sprite, int pos_x, 
				int pos_y, int size_x, int size_y, int frames_per_directions,
				int frame_delay);
			~Sprite();

			//variables
			//The sprite is from the pool, so if you modify the pool it gets modified !!
			ALLEGRO_BITMAP*& sprite;
			int pos_x;
			int pos_y;

			//of ONE if animated (we need sprites with same size)
			int size_x = 64;
			int size_y = 64;

			int current_frame = 0;
			int frames_per_directions  = 1;
			int frame_delay_counter = 0;
			int frame_delay = 0;

			//using values from SpriteDirections enum
			int state = 0;

			bool is_animated = false;
	};

	class SoundEngine {

	public:
		SoundEngine(Manager* manager);
		~SoundEngine();
		void stopMusic();
		void startMusic(std::string res);
		void playSound(std::string res);

	private:
		ALLEGRO_SAMPLE_ID current_music;
		Manager* managerRef;
	};
}

#endif