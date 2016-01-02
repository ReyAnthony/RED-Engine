/*
	keyboard_engine_tests.hpp is part of
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

#ifndef RED_ENGINE_KEYBOARD_ENGINE_TESTS_HPP
#define RED_ENGINE_KEYBOARD_ENGINE_TESTS_HPP

#include <iostream>
#include <cppunit/extensions/HelperMacros.h>
#include "../../keyboard_engine.hpp"

class KeyboardEngineTest : public CppUnit::TestFixture {

private:
    RedEngine::KeyboardEngine kbdEngine;
    ALLEGRO_EVENT ev;

public:

    void setUp();
    void testKeys();
    void tearDown();

    static CppUnit::Test *suite()
    {
        CppUnit::TestSuite* suite = new CppUnit::TestSuite( "KeyboardEngineTest" );
        suite->addTest( new CppUnit::TestCaller<KeyboardEngineTest>(
                "Key presses test",
                &KeyboardEngineTest::testKeys));

        return suite;
    }
};

#endif //RED_ENGINE_KEYBOARD_ENGINE_TESTS_HPP
