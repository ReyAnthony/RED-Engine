/*
	keyboard_engine_tests.cpp is part of
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

#include "keyboard_engine_tests.hpp"

void KeyboardEngineTest::setUp()
{
	std::cout << "Running KeyboardEngine Tests." << std::endl;
}

void KeyboardEngineTest::testKeys()
{
	//TEST WITHOUT UPDATE
	//we should get false
	CPPUNIT_ASSERT(!kbdEngine.isKeyPressed(ALLEGRO_KEY_RIGHT));
	CPPUNIT_ASSERT(!kbdEngine.isKeyPressed(ALLEGRO_KEY_ESCAPE));
	CPPUNIT_ASSERT(!kbdEngine.isKeyPressed(ALLEGRO_KEY_1));

	//Key right is supposed to be pressed
	ev.keyboard.keycode = ALLEGRO_KEY_RIGHT;
	ev.type = ALLEGRO_EVENT_KEY_DOWN;

	kbdEngine.update(&ev);
	CPPUNIT_ASSERT(kbdEngine.isKeyPressed(ALLEGRO_KEY_RIGHT));
	CPPUNIT_ASSERT(!kbdEngine.isKeyPressed(ALLEGRO_KEY_LEFT));

	//Key left and key right are supposed to be pressed
	ev.keyboard.keycode = ALLEGRO_KEY_LEFT;
	ev.type = ALLEGRO_EVENT_KEY_DOWN;

	kbdEngine.update(&ev);
	CPPUNIT_ASSERT(kbdEngine.isKeyPressed(ALLEGRO_KEY_RIGHT));
	CPPUNIT_ASSERT(kbdEngine.isKeyPressed(ALLEGRO_KEY_LEFT));

	//Key left is UP and key right is DOWN
	ev.keyboard.keycode = ALLEGRO_KEY_LEFT;
	ev.type = ALLEGRO_EVENT_KEY_UP;

	kbdEngine.update(&ev);
	CPPUNIT_ASSERT(kbdEngine.isKeyPressed(ALLEGRO_KEY_RIGHT));
	CPPUNIT_ASSERT(!kbdEngine.isKeyPressed(ALLEGRO_KEY_LEFT));

	//Key left is UP and key right is UP
	ev.keyboard.keycode = ALLEGRO_KEY_RIGHT;
	ev.type = ALLEGRO_EVENT_KEY_UP;

	//Keys are all UP
	kbdEngine.update(&ev);
	CPPUNIT_ASSERT(!kbdEngine.isKeyPressed(ALLEGRO_KEY_RIGHT));
	CPPUNIT_ASSERT(!kbdEngine.isKeyPressed(ALLEGRO_KEY_LEFT));
}

void KeyboardEngineTest::tearDown()
{
}