#include <iostream>
#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/ui/text/TestRunner.h>
#include "../keyboard_engine.hpp"
#include "../engine_core.hpp"

class KeyboardEngineTest : public CppUnit::TestFixture {

	private:
		RedEngine::KeyboardEngine kbdEngine;
		ALLEGRO_EVENT ev;

	public:
		void setUp()
		{
			std::cout << "Running KeyboardEngine Tests." << std::endl;
		}

		void testKeys()
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

		void tearDown() 
		{
		}

		static CppUnit::Test *suite()
  		{
			CppUnit::TestSuite* suite = new CppUnit::TestSuite( "KeyboardEngineTest" );
			suite->addTest( new CppUnit::TestCaller<KeyboardEngineTest>(
		                       "Key presses test", 
		                       &KeyboardEngineTest::testKeys));
		
			return suite;
  		}
};

int main(int argc, char** argv)
{	

	//Initializing allegro
	al_init();
	al_install_keyboard();
	al_init_image_addon();
	al_init_primitives_addon();
	al_install_audio();
	al_init_acodec_addon();

	CppUnit::TextUi::TestRunner runner;
	runner.addTest(KeyboardEngineTest::suite());
	runner.run();

	//return 1 if failed tests
	return 0;
}