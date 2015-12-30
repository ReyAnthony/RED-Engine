/*
keyboard_engine.cpp

Author  :	Anthony Rey
Date    :	19/10/2015
*/

#include "keyboard_engine.hpp"

namespace RedEngine
{
	KeyboardEngine::KeyboardEngine()
	{
	}
	
	//TODO
	KeyboardEngine::~KeyboardEngine()
	{
	}

	bool KeyboardEngine::isKeyPressed(int key)
	{
		return key_map[key];
	}

	void KeyboardEngine::update(ALLEGRO_EVENT* ev)
	{
		//if key is pressed
		if (ev->type == ALLEGRO_EVENT_KEY_DOWN)
		{
			key_map[ev->keyboard.keycode] = true;
		}
		else if (ev->type == ALLEGRO_EVENT_KEY_UP)
		{
			key_map[ev->keyboard.keycode] = false;
		}

	}
}

	
