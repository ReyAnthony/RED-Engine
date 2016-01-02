//
// Created by Anthony REY on 30/12/2015.
//

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