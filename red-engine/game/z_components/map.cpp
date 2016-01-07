/*
	map.cpp is part of
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

#include "map.hpp"

WalkableMapGenerator::WalkableMapGenerator() {

}

PlayerMap::~PlayerMap() {

}

PlayerMap::PlayerMap(std::string mapName, std::vector<RedEngine::MapAtom ***> atomsByLayers,
                     int xmax, int ymax) : Map(mapName, atomsByLayers, xmax, ymax)
{

}

RedEngine::Map *WalkableMapGenerator::generate(std::string mapName,
                                                  std::vector<RedEngine::MapAtom ***> atomsByLayers, int xmax,
                                                  int ymax) {

    return new PlayerMap(mapName, atomsByLayers, xmax, ymax);
}

void PlayerMap::setPlayerComponent(PlayerComponent *playerComponent) {

    this->playerComponent = playerComponent;
}

void PlayerMap::init() {

    RedEngine::Map::init();
    playerComponent->setManager(this->getManager());
    playerComponent->init();
}

void PlayerMap::update() {

    RedEngine::Map::update();

    //last position of the player
    int last_x = playerComponent->getSprite()->getPosX();
    int last_y = playerComponent->getSprite()->getPosY();

    this->playerComponent->update();

    int current_x = playerComponent->getSprite()->getPosX();
    int current_y = playerComponent->getSprite()->getPosY();

    //TODO is this normal that the map is managing the collisions with the player ?
    //TODO add guards for currentX and currentY or else we crash if the get outside map
    RedEngine::MapAtom*** map = getAtoms().at(0);
    for (int y = (current_y - 128) / 64; y < (current_y + 128) / 64 ; y++)
    {
        for(int x = (current_x - 128) / 64 ; x < (current_x + 128) / 64; x++)
        {
            if(!map[y][x]->isWalkable())
            {
                if(RedEngine::collision_engine(playerComponent->getSprite(), map[y][x]->getSprite() ))
                {
                    this->playerComponent->getSprite()->setPosX(last_x);
                    this->playerComponent->getSprite()->setPosY(last_y);

                    //stopping the anim if there is a collision
                    this->playerComponent->getSprite()->switchAnimState(false);
                }
            }
        }
    }

    int y_border = this->getManager()->getHeight() - y_offset;
    int x_border = this->getManager()->getWidth() - x_offset;

    //if we go far on the right, the whole map is moving left
    if(current_x >= x_border - 128)
    {
        x_offset -= 2;
    }
    if(current_y >= y_border - 128)
    {
        y_offset -= 2;
    }
    if(current_x <= (x_offset * -1) + 128)
    {
        x_offset += 2;
    }
    if(current_y <= (y_offset * -1) + 128)
    {
        y_offset += 2;
    }

    this->setOffsets(x_offset, y_offset);
}

void PlayerMap::draw(){

    //everything is getting moved
	getManager()->transformTranslate(x_offset, y_offset);
    RedEngine::Map::draw();
    this->playerComponent->draw();
	getManager()->resetTransformTranslate();
}
