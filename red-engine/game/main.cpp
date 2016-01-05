/*
	main.cpp is part of
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

    ################

 	Other copyrights :

	"The isle"
 	"Curious Wanderer"
 	"One of Many"
	by Jasmine Cooper
	www.jasminecoopermusic.net

    prince_valiant.tff
    from Dieter Steffman
    http://www.steffmann.de/
*/

#include "main.hpp"

void init_map_bindings(RedEngine::Manager* manager)
{
	RedEngine::MapFactory::bind('0', 0, true, game_resources::NULL_RES, manager);
	RedEngine::MapFactory::bind('2', 0, true, game_resources::TREES, manager);
	RedEngine::MapFactory::bind('3', 0, false, game_resources::MOUNTAINS, manager);
	RedEngine::MapFactory::bind('4', 0, true, game_resources::CASTLE, manager);
	RedEngine::MapFactory::bind('5', 0, true, game_resources::VILLAGE, manager);
	RedEngine::MapFactory::bind('6', 0, false, game_resources::WATER, manager);
	RedEngine::MapFactory::bind('7', 0, false, game_resources::WALL, manager);
	RedEngine::MapFactory::bind('8', 0, false, game_resources::L_WALL, manager);
	RedEngine::MapFactory::bind('9', 0, false, game_resources::R_WALL, manager);

	//This is used in order to generate a walkable map (playermap)
	RedEngine::MapFactory::bindGenerator(new WalkableMapGenerator());
}

void init_resources(RedEngine::Manager* game)
{
	game->addSprite(game_resources::NULL_RES, "res/sprites/null.png");
	game->addSprite(game_resources::WATER, "res/sprites/water.png");
	game->addSprite(game_resources::TREES, "res/sprites/trees.png");
	game->addSprite(game_resources::MOUNTAINS, "res/sprites/mountains.png");
	game->addSprite(game_resources::CASTLE, "res/sprites/castle.png");
	game->addSprite(game_resources::CORPSE, "res/sprites/corpse.png");
	game->addSprite(game_resources::WALL, "res/sprites/wall.png");
	game->addSprite(game_resources::L_WALL, "res/sprites/leftWall.png");
	game->addSprite(game_resources::R_WALL, "res/sprites/rightWall.png");
	game->addSprite(game_resources::VILLAGE, "res/sprites/village.png");
	game->addSprite(game_resources::HILDA, "res/sprites/hilda.png");

	game->addFont(game_resources::ARIAL_15, "res/fonts/Arial.ttf", 15);
    game->addFont(game_resources::VALIANT_25, "res/fonts/prince_valiant.ttf", 25);
    game->addFont(game_resources::VALIANT_50, "res/fonts/prince_valiant.ttf", 50);

	game->addSound(game_resources::OVERWORLD_MUSIC, "res/music/CuriousWanderer.ogg");
	game->addSound(game_resources::TRANS_1, "res/sounds/trans_1.wav");
    game->addSound(game_resources::TRANS_2, "res/sounds/trans_2.wav");
}

int main(int argc, char** argv)
{

	//TODO exceptions instead of STOP codes
	//TODO GUI Builder
	//TODO resolution independance 

	RedEngine::Manager* game = new RedEngine::Manager(640, 480, "RedEngine Test");

	game->setBackgroundColor(170,170,170);
	init_resources(game);
	init_map_bindings(game);

	game->pushScene(new Overworld());
	game->pushScene(new TransitionScene());
	game->start();

	// CLEANING SECTION
	delete game;
	return 0;
}
		
