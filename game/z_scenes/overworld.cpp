#include "overworld.hpp"

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

	//getManager()->getSoundEngine()->startMusic("overworld_music");
}

void Overworld::update()
{
	//could use it, but we won't
	
}

void Overworld::draw()
{	
	//could use it, but we won't
}
