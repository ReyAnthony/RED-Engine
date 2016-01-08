/*
	keyboard_engine.cpp is part of
	RED-ENGINE - An Object-Oriented game engine based on Allegro5
	Copyright (C) 2015 - 2016 Anthony REY

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

	char KeyboardEngine::getLastTyped()
	{
		char toRet = lastTyped;
		lastTyped = -1;
		return toRet;
	}

	int KeyboardEngine::getLastTypedKeycode()
	{
		int toRet = lastTypedKeycode;
		lastTypedKeycode = -1;
		return toRet;
	}

	//TODO wrapper for allegro keycodes
	bool KeyboardEngine::isKeyPressed(int key)
	{
		int key_ret = key_map[key];   
		return key_ret;
	}

	bool KeyboardEngine::isKeyPressedNoRepeat(int key)
	{
		int key_ret = key_map[key];
		key_map[key] = false;   
		return key_ret;
	}

	void KeyboardEngine::update(ALLEGRO_EVENT* ev)
	{
		//if key is pressed
		if (ev->type == ALLEGRO_EVENT_KEY_DOWN)
		{
			key_map[ev->keyboard.keycode] = true;
			key_map_no_repeat[ev->keyboard.keycode] = true;
		}
		else if (ev->type == ALLEGRO_EVENT_KEY_UP)
		{
			key_map[ev->keyboard.keycode] = false;
		}
		else if(ev->type == ALLEGRO_EVENT_KEY_CHAR)
		{
			char uni = (char)ev->keyboard.unichar;
			char keycode = (char)ev->keyboard.keycode;

			lastTyped = uni;
			lastTypedKeycode = keycode;
		}

	}
}

	
