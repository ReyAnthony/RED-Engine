//
// Created by Anthony REY on 20/12/2015.
//

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
