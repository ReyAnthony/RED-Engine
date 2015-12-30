//
// Created by Anthony REY on 20/12/2015.
//

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

int SnowFlake::setX(int x)
{
    this-> x = x;
}

int SnowFlake::setY(int y)
{
    this->y = y;
}

int SnowFlake::setSize(int size)
{
    this->size = size;
}

void SnowFlake::draw()
{
    al_draw_filled_circle(x, y, size, al_map_rgb(255,255,255));
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
    ALLEGRO_TRANSFORM camera_transform;
    al_identity_transform(&camera_transform);
    al_translate_transform(&camera_transform, 0, 0);
    al_use_transform(&camera_transform);

    int i;
    for(i = 0; i < snowFlakes_count; i++)
    {
        snowFlakes[i]->draw();
    }
}
