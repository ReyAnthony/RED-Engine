/*
	sprite.cpp is part of
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

#include "sprite.hpp"
namespace RedEngine
{
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

}
