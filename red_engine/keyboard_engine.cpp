/*
	keyboard_engine.cpp is part of
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

	
