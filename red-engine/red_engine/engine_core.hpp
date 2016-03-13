/*
  engine_core.hpp is part of RED-ENGINE - An Object-Oriented game
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

#ifndef RED_ENGINE_H
#define RED_ENGINE_H

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

#include "sprite.hpp"
#include "keyboard_engine.hpp"
#include "sound_engine.hpp"
#include "datapool.hpp"
#include "game_scene.hpp"
#include "game_components.hpp"

namespace RedEngine {

    enum StopCodes {
	PLAYER_EXIT, // 0
	AL_INIT_FAILED, // 1
	ADDON_INIT_FAILED, // 2
	DISPLAY_NULL, // 3
	EMPTY_SCENE_STACK, // 4
	RES_ADD_FAILED, // 5
	COLOR_CODE_ERROR, // 6
	RES_NOT_FOUND, // 7
	EMPTY_LABEL, // 8
	ALREADY_USED_LABEL, // 9
	CANNOT_RESERVE_SAMPLES, // 10
	TEST_EXIT // 11
    };


    class SoundEngine;
    class Sprite;
    
    //##############  Manager class ##############
    // This class manage the game
    class Manager {
    public:
	Manager(int virtual_width, int virtual_height, int real_width,
		int real_height, const char *title, bool isFullscreen,
		bool isResizable);
	~Manager();

	// must be called after creating the class
	void start();

	void stop(int error_code);
	void pushScene(GameScene *scene);
	void popScene();

	// TODO REFERENCES and PRIVATE
	ALLEGRO_SAMPLE *getSound(std::string key);
	ALLEGRO_FONT *getFont(std::string key);

	// const char* cause allegro is C not C++
	void addSprite(std::string key, const char *file);
	void addSound(std::string key, const char *file);
	void addFont(std::string key, const char *file, unsigned int size);

	void setBackgroundColor(unsigned int r, unsigned int g, unsigned int b);

	int getWidth();
	int getHeight();

	// negate the need for a getSprite
	// it's mostly a factory i guess
	Sprite *createSprite(std::string key);
	Sprite *createSprite(std::string key, int x, int y);
	Sprite *createSprite(std::string key, int pos_x, int pos_y, int size_x,
			     int size_y, int frames_per_directions, int frame_delay);

	SoundEngine *getSoundEngine();
	KeyboardEngine *getKeyBoardEngine();

	void transformTranslate(int x, int y);
	void resetTransformTranslate();

    private:
	// methods
	// called by the constructor
	void init();

	// they are calling the top of the stack
	void update(ALLEGRO_EVENT *ev);
	void drawAll();
	void draw();

	// DataPool access
	// We use a reference so that when we deallocate it and nullptr it
	// it becomes nullptr in sprite too
	ALLEGRO_BITMAP *&getSprite(std::string key);

	// scene at the top of the stack is played
	std::stack<GameScene *> game_scenes;

	DataPool *datapool; // when forward declaring you can only use a pointer
	KeyboardEngine keyboard_engine;
	SoundEngine *soundEngine;
	
	int virtual_width;
	int virtual_height;
	int real_width;
	int real_height;
	bool running;
	bool redraw;
	const char *title;
	bool isFullscreen;
	bool isResizable;

	ALLEGRO_DISPLAY *display;
	ALLEGRO_EVENT ev;
	ALLEGRO_EVENT_QUEUE *event_queue;
	ALLEGRO_TIMER *timer;

	// for moving the screen with transforms
	ALLEGRO_TRANSFORM camera_transform;
	ALLEGRO_COLOR bkg_color;

	static const int FPS = 60;
    };


}
#endif
