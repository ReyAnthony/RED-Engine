/*
keyboard_engine.hpp

Author  :	Anthony Rey
Date    :	22/09/2015
*/

#ifndef KBD_ENGINE_H
#define KBD_ENGINE_H

#include <allegro5/allegro.h>
#include <allegro5/keyboard.h>

#include <unordered_map>

namespace RedEngine
{
	class KeyboardEngine
	{
		public:
			KeyboardEngine();
			~KeyboardEngine();

			bool isKeyPressed(int key);
			void update(ALLEGRO_EVENT* ev);

		private:

			//int == keycode
			//bool == isPressed 
			std::unordered_map<int, bool> key_map;

	};
}
#endif