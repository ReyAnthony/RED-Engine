/*
    sound_engine_tests.hpp is part of
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

#ifndef RED_ENGINE_SOUND_ENGINE_TESTS_HPP
#define RED_ENGINE_SOUND_ENGINE_TESTS_HPP

#include <iostream>
#include <cppunit/extensions/HelperMacros.h>
#include "../../collision_engine.hpp"
#include "../../engine_core.hpp"

class SoundEngineTests : public CppUnit::TestFixture {

public:

    void setUp();
    void testEngine();
    void tearDown();

    static CppUnit::Test *suite()
    {
        CppUnit::TestSuite* suite = new CppUnit::TestSuite( "ColEngineTest" );
        suite->addTest( new CppUnit::TestCaller<SoundEngineTests>(
                "Collision Test",
                &SoundEngineTests::testEngine));

        return suite;
    }

private :
    RedEngine::Manager *game;
};
#endif //RED_ENGINE_SOUND_ENGINE_TESTS_HPP
