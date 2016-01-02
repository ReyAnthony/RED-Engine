/*
	map.cpp is part of
	RED-ENGINE - An Object-Oriented game engine based on Allegro5
	Copyright (C) 2015 Anthony REY

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
namespace RedEngine
{	

	//statics
	std::vector<std::unordered_map<char, IBinding*>*> MapFactory::bindings;
	IGenerator* MapFactory::generator;

	//########## MAP FACTORY #############
	void MapFactory::bind(char letterBinding, int layer, bool isWalkable, std::string spriteName, Manager* manager)
	{	
		//TODO factorise
		if(MapFactory::bindings.empty())
		{
			MapFactory::bindings.push_back(new std::unordered_map<char, IBinding*>);
		}

		GenericBinding* toAdd = new GenericBinding(isWalkable, spriteName, manager);
		std::unordered_map<char, IBinding*>* map = MapFactory::bindings.at(0);
		(*map)[letterBinding] = toAdd;
	}

	void MapFactory::bind(char letterBinding, int layer, IBinding* customBinding)
	{
		if(MapFactory::bindings.empty())
		{
			MapFactory::bindings.push_back(new std::unordered_map<char, IBinding*>);
		}
		std::unordered_map<char, IBinding*>* map = MapFactory::bindings.at(0);
		(*map)[letterBinding] = customBinding;
	}

	void MapFactory::bindGenerator(IGenerator* generator)
	{
		MapFactory::generator = generator;
	}

	//contract : fail if there's no map bindings / a map character is unknown
	Map* MapFactory::generate(char* map, std::string mapName)
	{	
		//1) test if empty ...
		//2) read the file and do what the bindings are telling you to do
		//3) return the map
		//TODO test if map is square
		int x = 0;
		int y = 0;
		int index = 0;
		char buffer = 0;
		int xmax = 0;

		//TODO multiple layers
		std::vector<MapAtom***> layers;
	
		//allocating the Y
		MapAtom*** mapRep = (MapAtom***) malloc(sizeof(MapAtom**));

		while( (buffer = map[index]) != '\0')
		{
			if(buffer != '\n')
			{
				if(x == 0)
					mapRep[y] = (MapAtom**) malloc(sizeof(MapAtom*));
				else
					mapRep[y] = (MapAtom**) realloc(mapRep[y], sizeof(MapAtom*) * (x + 1));

				std::unordered_map<char, IBinding*>* dataMap = MapFactory::bindings.at(0);
				mapRep[y][x] = (*dataMap)[buffer]->bindingAction();
				//TODO remove 32 , use the sizeMax
				mapRep[y][x]->getSprite()->setPosX(x * 64);
				mapRep[y][x]->getSprite()->setPosY(y * 64);

				x++;

				if(x > xmax)
				{
					xmax = x;
				}
			}
			else
			{
				x = 0;
				y++;
				mapRep = (MapAtom***) realloc(mapRep, sizeof(MapAtom**) * (y+1) );
			}

			index++;	
		}
		
		layers.push_back(mapRep);

		if(nullptr != MapFactory::generator)
			return MapFactory::generator->generate(mapName, layers, xmax, y);	
		else
			return new Map(mapName, layers, xmax, y);
	}

	//######### GENERIC BINDING ############## 
	GenericBinding::GenericBinding(bool walkable, std::string spriteName, Manager* manager)
	{
		this->walkable = walkable;
		this->spriteName = spriteName;
		this->manager = manager;
	}

	GenericBinding::~GenericBinding()
	{/*nothing to clean*/}

	MapAtom* GenericBinding::bindingAction()
	{
		return new MapAtom(walkable, manager->createSprite(spriteName));
	}
	

	//###### MAP ATOM ######### 
	MapAtom::MapAtom(bool walkable, Sprite* sprite)
	{
		this->walkable = walkable;
		this->sprite = sprite;
	}

	MapAtom::~MapAtom()
	{

	}

	Sprite* MapAtom::getSprite()
	{
		return this->sprite;
	}

	bool MapAtom::isWalkable() {
		return walkable;
	}

	//####### MAP #######
	Map::Map(std::string mapName, std::vector<MapAtom***> atomsByLayers, int xmax, int ymax) : GameComponent(true)
	{
		this->mapName = mapName;
		this->atomsByLayers = atomsByLayers;
		this->xmax = xmax;
		this->ymax = ymax;
	}	

	Map::~Map()
	{

	}

	void Map::init()
	{
		//nothing to do ?
	}

	void Map::update()
	{

	}

	void Map::draw()
	{
		//TODO show only what we must
		int width = this->getManager()->getWidth();
		int height = this->getManager()->getHeight();

		int ymax = ((height / 64) + 2 - (y_offset / 64) );
		int xmax = ((width / 64) + 2 - (x_offset / 64) );

		int startx = (x_offset * -1) / 64;
		int starty = (y_offset * -1) / 64;

		MapAtom*** map = atomsByLayers.at(0);
		for (int y = starty; y < ymax; y++)
		{
			for(int x = startx; x < xmax; x++)
			{
				map[y][x]->getSprite()->draw();
			}
		}
	}

	MapAtom* Map::getMapAtom(int x, int y, int layer)
	{
		return atomsByLayers.at(layer)[x][y];
	}

	std::vector<MapAtom ***> Map::getAtoms() {
		return atomsByLayers;
	}

	void Map::setOffsets(int x, int y) {
		this->x_offset = x;
		this->y_offset = y;
	}
}