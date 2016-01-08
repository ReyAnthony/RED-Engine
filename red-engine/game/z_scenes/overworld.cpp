/*
	overworld.cpp is part of
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

#include "overworld.hpp"
#include "../game_resources.hpp"
#include "transition_scene.hpp"

Overworld::Overworld()
{
}

Overworld::~Overworld()
{
}

//called when pushing scene
void Overworld::init()
{	

	PlayerMap * map = (PlayerMap *) RedEngine::MapFactory::generate(
			SOUTH_ISLAND_OVERWORLD_DATA, "South King's Island");
	PlayerComponent* player = new PlayerComponent(64*15,64*14);
	SnowComponent* snow = new SnowComponent(180);

	map->setPlayerComponent(player);
	addComponent(map);
	addComponent(snow);

	//shut up
	//getManager()->getSoundEngine()->startMusic(game_resources::OVERWORLD_MUSIC);
}

void Overworld::update()
{
	if(this->getManager()->getKeyBoardEngine()->isKeyPressed(ALLEGRO_KEY_ESCAPE))
	{
        this->getManager()->getSoundEngine()->stopMusic();
        //remove the current scene
        this->getManager()->popScene();
		this->getManager()->pushScene(new QuitTransitionScene());
	}
}

void Overworld::draw()
{
}
