//
// Created by Anthony REY on 20/12/2015.
//

#include "collision_engine.hpp"

bool RedEngine::collision_engine(RedEngine::Sprite *spr1, RedEngine::Sprite *spr2)
{
    //is outside
    if ((spr1->getPosX() + spr1->getSizeX() <= spr2->getPosX())
        || (spr1->getPosX() >= spr2->getPosX() + spr2->getSizeX())
        || (spr1->getPosY() >= spr2->getPosY() + spr2->getSizeY())
        || (spr1->getPosY() + spr1->getSizeY() <= spr2->getPosY())) {

        return false;
    }
    else
        return true;
}