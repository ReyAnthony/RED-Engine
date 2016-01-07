/*
	sound_engine.hpp is part of
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

#ifndef SND_ENGINE_H
#define SND_ENGINE_H

#include "engine_core.hpp"

namespace RedEngine
{
	class DataPool;
	
	class SoundEngine {

		public:
			SoundEngine(DataPool* datapool);
			~SoundEngine();
			void stopMusic();
			void startMusic(std::string res);
			void playSound(std::string res);

		private:
			ALLEGRO_SAMPLE_ID current_music;
			DataPool* datapool;
	};
}

#endif