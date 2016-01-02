/*
	main.hpp is part of
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

#ifndef MAIN_HPP
#define MAIN_HPP

#include "z_scenes/overworld.hpp"
#include "red_engine/map.hpp"
#include <list>

void init_map_bindings(RedEngine::Manager* manager);
void init_resources(RedEngine::Manager* game);

#endif //MAIN_HPP
