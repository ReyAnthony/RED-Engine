/*
	sprite.hpp is part of
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

#ifndef SPRITE_H
#define SPRITE_H

#include "engine_core.hpp"

namespace RedEngine
{
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
}

#endif