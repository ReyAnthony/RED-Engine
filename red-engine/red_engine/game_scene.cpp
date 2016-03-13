/*
  game_scene.cpp is part of RED-ENGINE - An Object-Oriented game
  engine based on Allegro5 Copyright (C) 2015 - 2016 Anthony REY

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

#include "game_scene.hpp"

namespace RedEngine
{
    GameScene::~GameScene()
    {}

    Manager* GameScene::getManager()
    {
	return this->manager;
    }

    void GameScene::setManager(Manager* manager)
    {
	this->manager = manager;
    }

    void GameScene::addComponent(GameComponent* component)
    {
	component->setManager(this->getManager());
	component->init();
	components.push_back(component);
    }

    void GameScene::drawComponentsBack()
    {
	std::list<RedEngine::GameComponent*>::const_iterator iterator;
	for (iterator = components.begin();
	     iterator != components.end(); ++iterator) {

	    if( (*iterator)->getIsBack()) 
		(*iterator)->draw();
	}
    }	
	
    void GameScene::drawComponentsFront()
    {
	std::list<RedEngine::GameComponent*>::const_iterator iterator;
	for (iterator = components.begin();
	     iterator != components.end(); ++iterator) {
			
	    if( ! (*iterator)->getIsBack()) 
		(*iterator)->draw();
	}

    }

    void GameScene::updateComponents()
    {
	std::list<RedEngine::GameComponent*>::const_iterator iterator;
	for (iterator = components.begin();
	     iterator != components.end(); ++iterator) {

	    (*iterator)->update();
	}
    }
}
