/*
  datapool.cpp is part of
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

#include "datapool.hpp"

namespace RedEngine
{

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
}
