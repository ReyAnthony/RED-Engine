/*
    sound_engine_tests.cpp is part of
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

#include "sound_engine_tests.hpp"

void SoundEngineTests::setUp()
{
    std::cout << "Running SoundEngine Tests." << std::endl;

    //We need a manager to create sprites
    game = new RedEngine::Manager(640, 480, "RedEngine Test");

    //we need some resources to create the sounds
}

void SoundEngineTests::testEngine()
{
    //TODO
}

void SoundEngineTests::tearDown()
{
    game->stop(RedEngine::TEST_EXIT);
    delete game;
}
