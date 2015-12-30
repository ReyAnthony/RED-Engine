/*
	18/12/2015
	Anthony REY
*/

#ifndef MAP_H
#define MAP_H

#include "engine_core.hpp"
#include <vector>

namespace RedEngine
{
	//forward declarations
	class MapFactory;
	class IBinding;
	class MapAtom;
	class Map;
	class IGenerator;

	class MapFactory 
	{
		public:
			//no constructor, this is MOSTLY a factory
			//sprite => NOPE, needs a MapAtom (be careful not to use differents sprites, as it will increase mem usage)
			//contract : replace a binding if letterBinding already exist in the layer, BUT print a warning if so 
			//layers are created at runtime when requested
			static void bind(char letterBinding, int layer, bool isWalkable, std::string spriteName, Manager* manager);
			static void bind(char letterBinding, int layer, IBinding* customBinding);

			//Set the callBack used to create the map (eg : used for generating a subclass of MAP)
			static void bindGenerator(IGenerator* generator);

			//TODO unbind
			//static void unbind(char letterBinding, int layer);

			//the String being the whole map (ok that's bad, find better someday)
			//contract : fail if there's no map bindings / a map character is unknown
			static Map* generate(char* map, std::string mapName);

		private:
			//TODO not used right now
			//Arbitrary values are cool !
			const int MAX_LAYERS = 3;
			//this is a list of MapAtoms
			static std::vector<std::unordered_map<char, IBinding*>*> bindings;
			//if is null, instanciate a normal map
			static IGenerator* generator;
	};

	class IGenerator
	{
		public:
			//same constructor as the MAP
			//it's up to the developer to cast to the expected type
			//has to be given to MapFactory::BindGenerator(IGenerator* generator)
			virtual Map* generate(std::string mapName, std::vector<MapAtom***> atomsByLayers, int xmax, int ymax) = 0;
	};


	class IBinding
	{
		public:
			//the binding should return a MapAtom when called
			virtual MapAtom* bindingAction() = 0;
	};

	//generic binding for static void addBinding(char letterBinding, int layer, MapAtom MapAtom);
	//it will just give back the given atom
	class GenericBinding : public IBinding
	{
		public:
			GenericBinding(bool walkable, std::string spriteName, Manager* manager);
			~GenericBinding();
			//each time it creates a new MapAtom
			MapAtom* bindingAction();

		private:
			bool walkable;
			std::string spriteName;
			Manager* manager;
	};

	//A MapAtom is the tiniest part of a map
	class MapAtom 
	{
		public:
			MapAtom(bool walkable, Sprite* sprite);
			~MapAtom();
			Sprite* getSprite();
			bool isWalkable();

		private:
			//false by default but being explicit doesn't kill
			bool walkable = false;
			Sprite* sprite;
	};

	class Map : public GameComponent
	{
		public:
			Map(std::string mapName, std::vector<MapAtom***> atomsByLayers, int xmax, int ymax);
			~Map();

			void init();
			void update();
			void draw();

			void setOffsets(int x, int y);

			MapAtom* getMapAtom(int x, int y, int layer);
			std::vector<MapAtom***> getAtoms();

		private:
			std::vector<MapAtom***> atomsByLayers;
			std::string mapName;	
			int xmax, ymax;
			int x_offset = 0;
			int y_offset = 0;
	};
}

#endif