//
// Created by Anthony REY on 30/12/2015.
//

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
