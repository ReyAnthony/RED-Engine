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

    All tiles but hilda.png are from David E. Gervais
    and are released under CC-BY 3.0
    water.png has been modified by me in order to be animated

    hilda.png is from Anthony Rey and is licenced
    under CC BY-NC-ND
*/

#include "main.hpp"

void init_map_bindings(RedEngine::Manager* manager)
{
	RedEngine::MapFactory::bind('0', 0, true, game_resources::SNOW, manager);
	RedEngine::MapFactory::bind('2', 0, true, game_resources::TREES, manager);
	RedEngine::MapFactory::bind('3', 0, false, game_resources::MOUNTAINS, manager);
	RedEngine::MapFactory::bind('6', 0, new RedEngine::AnimBinding(false, game_resources::WATER, manager, 4, 20));
	RedEngine::MapFactory::bind('7', 0, false, game_resources::WALL, manager);

	//This is used in order to generate a walkable map (playermap)
	RedEngine::MapFactory::bindGenerator(new WalkableMapGenerator());
}

void init_resources(RedEngine::Manager* game)
{
	game->addSprite(game_resources::SNOW, "res/sprites/snow.png");
	game->addSprite(game_resources::WATER, "res/sprites/water.png");
	game->addSprite(game_resources::TREES, "res/sprites/tree.png");
	game->addSprite(game_resources::MOUNTAINS, "res/sprites/mountains.png");
	game->addSprite(game_resources::WALL, "res/sprites/wall.png");
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
	//TODO resolution independance (started but hardcoded for 16/9)

	//TODO borg
	/*
	 * 	The borg should have the following phases :
	 *
	 * 	1) EXPLORATION_PHASE
	 * 		During this phase, the borg is pathfinding to every reachable locations
	 * 		on the map.
	 * 		As soon as it cannot find any unvisited place anymore, the borg will go
	 * 		to the EXIT_CAVE phase.
	 *
	 * 	2) EXIT_CAVE
	 * 		The borg will go to the nearest exit point (upward if there is no downward exit)
	 *
	 * 	3) THREAT_ASSESSEMENT
	 * 		If there is enemies in the borg's line of sight, it will assess the threat.
	 * 		If the threat is LOW or NORMAL, the borg will go to the FIGHT phase.
	 * 		Otherwize, the FLEE phase is used.
	 *
	 *	4) FIGHT
	 *		The borg will try to defeat his opponents.
	 *
	 *	5) FLEE
	 *		The borg will try to loose its opponenents
	 *
	 *	6) STATUS_CHECK
	 *		Each time the borg is damaged, it performs a STATUS_CHECK.
	 *		It tries to :
	 *			- Eat
	 *			- Heal itself
	 *			- etc...
	 */
	
	//WVGA (720x480)
    //TODO fix resize for OSX
	RedEngine::Manager* game = new RedEngine::Manager(720, 480, 1280, 720, "RedEngine Test", false, false);

	game->setBackgroundColor(0,0,0);
	init_resources(game);
	init_map_bindings(game);

	game->pushScene(new Overworld());
	game->pushScene(new TransitionScene());
	game->start();

	// CLEANING SECTION
	delete game;
	return 0;
}
		
