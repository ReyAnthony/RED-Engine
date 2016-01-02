/*
	snow.hpp is part of
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

#ifndef SNOW_HPP
#define SNOW_HPP

#include "red_engine/engine_core.hpp"

class SnowFlake
{
    public:
        SnowFlake(int x, int y, int size);
        ~SnowFlake();

        int getX();
        int getY();
        int getSize();

        int setX(int x);
        int setY(int y);
        int setSize(int size);

        void draw();

    private:
        int x;
        int y;
        int size;
};

class SnowComponent : public RedEngine::GameComponent
{
    public:
        SnowComponent(int count);
        ~SnowComponent();

        void init();
        void update();
        void draw();

    private:
        SnowFlake** snowFlakes;
        int snowFlakes_count;
};


#endif //Red-_SNOW_HPP
