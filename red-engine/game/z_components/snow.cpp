/*
	snow.cpp is part of
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

#include "snow.hpp"

//########## SnowFlake ###########
SnowFlake::SnowFlake(int x, int y, int size)
{
    this->x = x;
    this->y = y;
    this->size = size;
}

SnowFlake::~SnowFlake()
{

}

int SnowFlake::getX()
{
    return x;
}

int SnowFlake::getY()
{
    return y;
}

int SnowFlake::getSize()
{
    return size;
}

void SnowFlake::setX(int x)
{
    this-> x = x;
}

void SnowFlake::setY(int y)
{
    this->y = y;
}

void SnowFlake::setSize(int size)
{
    this->size = size;
}

void SnowFlake::draw()
{
    al_draw_filled_circle(x, y, size, al_map_rgb(240,240,240));
}

//######### SNOW COMPONENT #########
SnowComponent::SnowComponent(int count) : RedEngine::GameComponent(false)
{
    this->snowFlakes_count = count;
}

SnowComponent::~SnowComponent()
{

}

void SnowComponent::init()
{
    snowFlakes = new SnowFlake*[snowFlakes_count];
    int i;
    for(i = 0; i < snowFlakes_count; i++)
    {
        int x = rand() % getManager()->getWidth();
        int y = rand() % getManager()->getHeight();
        int size = rand() % 4;
        snowFlakes[i] = new SnowFlake(x, y, size);
    }

}

void SnowComponent::update()
{
    for(int i = 0; i < snowFlakes_count; i++)
    {
        snowFlakes[i]->setY(snowFlakes[i]->getY() + rand()%7);
        snowFlakes[i]->setX(snowFlakes[i]->getX() + rand()%2 - snowFlakes[i]->getSize());

        if(snowFlakes[i]->getY() > getManager()->getHeight())
        {
            snowFlakes[i]->setY(0);
            snowFlakes[i]->setSize(rand() % 4);
        }

        if(snowFlakes[i]->getX() < 0)
            snowFlakes[i]->setX(getManager()->getWidth());
    }
}

void SnowComponent::draw()
{

    al_identity_transform(&camera_transform);
    al_translate_transform(&camera_transform, 0, 0);
    al_use_transform(&camera_transform);

    int i;
    for(i = 0; i < snowFlakes_count; i++)
    {
        snowFlakes[i]->draw();
    }
}
