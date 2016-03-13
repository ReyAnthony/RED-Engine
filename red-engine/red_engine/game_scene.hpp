/*
  game_scene.hpp is part of RED-ENGINE - An Object-Oriented game
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

#ifndef GAME_SCENE_H
#define GAME_SCENE_H

#include "game_components.hpp"
#include <list>

namespace RedEngine
{

    class Manager;
    
    class GameScene {
    public:
	virtual ~GameScene() = 0;
	// init is called after set manager when pushing scene
	void virtual init() = 0;
	void virtual update() = 0;
	void virtual draw() = 0;

	// This setup is done auto by the manager when pushing the scene
	Manager *getManager();
	void addComponent(GameComponent *component);

	friend class Manager;
	void setManager(Manager *manager);

    private:
	// auto draw for components;
	void drawComponentsBack();
	void drawComponentsFront();
	void updateComponents();

	Manager *manager;
	std::list<GameComponent *> components;
    };
}

#endif
