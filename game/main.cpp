/*
	9/12/2015
	Anthony REY
*/

#include "main.hpp"

void init_map_bindings(RedEngine::Manager* manager)
{
	RedEngine::MapFactory::bind('0', 0, true, "null", manager);
	RedEngine::MapFactory::bind('2', 0, true, "trees", manager);
	RedEngine::MapFactory::bind('3', 0, false, "mountains", manager);
	RedEngine::MapFactory::bind('4', 0, true, "castle", manager);
	RedEngine::MapFactory::bind('5', 0, true, "village", manager);
	RedEngine::MapFactory::bind('6', 0, false, "water", manager);
	RedEngine::MapFactory::bind('7', 0, false, "wall", manager);
	RedEngine::MapFactory::bind('8', 0, false, "l_wall", manager);
	RedEngine::MapFactory::bind('9', 0, false, "r_wall", manager);

	//This is used in order to generate a walkable map (playermap)
	RedEngine::MapFactory::bindGenerator(new WalkableMapGenerator());
}

void init_resources(RedEngine::Manager* game)
{
	game->addSprite("null", "res/sprites/null.png");
	game->addSprite("water", "res/sprites/water.png");
	game->addSprite("trees", "res/sprites/trees.png");
	game->addSprite("mountains", "res/sprites/mountains.png");
	game->addSprite("castle", "res/sprites/castle.png");
	game->addSprite("corpse", "res/sprites/corpse.png");
	game->addSprite("wall", "res/sprites/wall.png");
	game->addSprite("l_wall", "res/sprites/leftWall.png");
	game->addSprite("r_wall", "res/sprites/rightWall.png");
	game->addSprite("village", "res/sprites/village.png");
	game->addSprite("hilda", "res/sprites/hilda.png");
	game->addFont("arial_15", "res/fonts/Arial.ttf", 15);
	//game->addSound("overworld_music", "res/music/1.ogg");
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
	game->start();

	// CLEANING SECTION
	delete game;
	return 0;
}
		
