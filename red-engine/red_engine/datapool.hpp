/*
	datapool.hpp is part of
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

#ifndef DATAPOOL_H
#define DATAPOOL_H

#include "engine_core.hpp"

namespace RedEngine
{
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
}

#endif
