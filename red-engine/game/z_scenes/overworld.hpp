/*
	overworld.hpp is part of
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

#ifndef GAMESCENES_H
#define GAMESCENES_H

//TODO replace by a map loader
#define SOUTH_ISLAND_OVERWORLD_DATA "\
333333333333333332233333333333333333333333333332223333\n\
333333333333333332233333333333333333333333333332223333\n\
633333333333333332233333333333333333333333333222333333\n\
663333333333333332233333333333333333333333322233333333\n\
666633333333333332233333333333333333333333222333333333\n\
666630200000055002220000333333333333333333222000033333\n\
366302242220555200002000333333333333333332242200003333\n\
263322200002255200022200333333333333333333222000000333\n\
663332200000000000022200222200333333333333333300003333\n\
333320332033300300002000022220000333333333333333333333\n\
333302330033000300000000333302222003333333333333333333\n\
333333333333223333333333333333222222220003333333333333\n\
333333330255200033333333333330022222222220003333333333\n\
333300002055552202202333333333333300224220333333333333\n\
333333333325550220222233333333300222555553333333333333\n\
336666633332233320332033333333333003022503333333333333\n\
666666666662222022222033333333330000000003333333333333\n\
366666666662222002000022333333333000000333333333333333\n\
666333333333003333333333333333333333003333333333333333\n\
666387777779008777777777933333333333003333333333333333\n\
666633333555555533333333333333336666663333333333333333\n\
666663355555545555533333366336666666633333333333333333\n\
666663355555555555553333666666666600666666663333333333\n\
666663355555666666666666666666660550666666666633333333\n\
666666666666666666666666666666666666666666666666663333\n\
666666000006666666666666666666666666666666666666666663\n\
666666660006666666666666666666666666666666666666666666\n\
666666666666666666666666666666666666666666666666666666\n\
666666666666666666666666666666666666666666666666666666\n\
666666666666666666666666666666666666666666666666666666\n"

#include "red_engine/engine_core.hpp"
#include "red_engine/map.hpp"
#include "red_engine/transitions.hpp"
#include "../z_components/map.hpp"
#include "../z_components/snow.hpp"

class Overworld : public RedEngine::GameScene
{
	public:
		Overworld();
		~Overworld();
		//called when pushing scene
		void init();
		void update();
		void draw();

};

#endif