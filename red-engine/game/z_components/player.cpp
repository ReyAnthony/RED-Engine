/*
	player.cpp is part of
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

#include "player.hpp"

//######## PLAYER COMPONENT ##########
PlayerComponent::PlayerComponent(int x, int y) : RedEngine::GameComponent(false)
{
    this->start_x = x;
    this->start_y = y;
}

PlayerComponent::~PlayerComponent()
{

}

void PlayerComponent::init()
{
    player = this->getManager()->createSprite("hilda", start_x, start_y, 64, 64, 3, 10);
}

void PlayerComponent::update()
{
    int speed = 2;
    RedEngine::KeyboardEngine* kbdEngine = getManager()->getKeyBoardEngine();

    if (kbdEngine->isKeyPressed(ALLEGRO_KEY_LEFT))
    {
        player->switchAnimState(true);
        player->setState(RedEngine::SpriteDirections::W_LEFT);
        player->setPosX(player->getPosX()- speed);
    }
    else if(kbdEngine->isKeyPressed(ALLEGRO_KEY_RIGHT))
    {
        player->switchAnimState(true);
        player->setState(RedEngine::SpriteDirections::W_RIGHT);
        player->setPosX(player->getPosX()+ speed);
    }
    else if (kbdEngine->isKeyPressed(ALLEGRO_KEY_UP))
    {
        player->switchAnimState(true);
        player->setState(RedEngine::SpriteDirections::W_UP);
        player->setPosY(player->getPosY()- speed);
    }
    else if(kbdEngine->isKeyPressed(ALLEGRO_KEY_DOWN))
    {
        player->switchAnimState(true);
        player->setState(RedEngine::SpriteDirections::W_DOWN);
        player->setPosY(player->getPosY()+ speed);
    }
    else
    {
        player->switchAnimState(false);
    }
}

void PlayerComponent::draw()
{
    this->player->draw();
}


RedEngine::Sprite *PlayerComponent::getSprite()
{
    return this->player;
}
