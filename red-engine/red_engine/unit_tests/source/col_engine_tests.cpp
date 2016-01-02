/*
    col_engine_tests.cpp is part of
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

//FIXME Ideally we should run tests for everything that is needed here before (sprites, manager etc...)

#include "col_engine_tests.hpp"

void ColEngineTest::setUp()
{
    std::cout << "Running ColEngine Tests." << std::endl;

    //We need a manager to create sprites
    game = new RedEngine::Manager(640, 480, "RedEngine Test");

    //we need some resources to create the sprites, otherwize it is impossible
    game->addSprite("null", "test_res/null.png");

}

void ColEngineTest::testCol()
{
    //let's test some case where the collision IS NOT HAPPENING
    //by default sprites are of sizex and sizey 64
    RedEngine::Sprite* a = game->createSprite("null", 0, 0);
    RedEngine::Sprite* b = game->createSprite("null" , 128, 128);

    //TEST 1 :
    //the two sprites are created to be NOT ON THE SAME X OR Y
    //vvvv SO THIS SHOULD BE FALSE vvvv
    CPPUNIT_ASSERT(!RedEngine::collision_engine(a, b));

    //TEST 2 :
    //BOTH ARE REALLY NEAR each other
    //(0 - 63 for the a)
    //vvvv SO THIS SHOULD BE FALSE vvvv
    a->setPosX(0);
    a->setPosY(0);

    b->setPosX(64);
    b->setPosY(0);
    CPPUNIT_ASSERT(!RedEngine::collision_engine(a, b));

    //TEST 3 :
    //They are touching (by 1 PX on X axis)
    //vvvv SO THIS SHOULD BE TRUE vvvv
    a->setPosX(0);
    a->setPosY(0);

    b->setPosX(63);
    b->setPosY(0);
    CPPUNIT_ASSERT(RedEngine::collision_engine(a, b));

    //TEST 4 :
    //OVERLAPING
    //vvvv SO THIS SHOULD BE TRUE vvvv
    a->setPosX(0);
    a->setPosY(0);

    b->setPosX(0);
    b->setPosY(0);
    CPPUNIT_ASSERT(RedEngine::collision_engine(a, b));

    //TEST 5 :
    //SAME AXIS X, but different Y
    //vvvv THIS SHOULD BE FALSE vvvv
    a->setPosX(0);
    a->setPosY(0);

    b->setPosX(0);
    b->setPosY(128);
    CPPUNIT_ASSERT(!RedEngine::collision_engine(a, b));

    //TEST 6 :
    //SAME AXIS Y, but different X
    //vvvv THIS SHOULD BE FALSE vvvv
    a->setPosX(0);
    a->setPosY(0);

    b->setPosX(128);
    b->setPosY(0);
    CPPUNIT_ASSERT(!RedEngine::collision_engine(a, b));

    //TEST 7 :
    //Negative ?
    //vvvv THIS SHOULD BE FALSE vvvv
    a->setPosX(-128);
    a->setPosY(-256);

    b->setPosX(128);
    b->setPosY(0);
    CPPUNIT_ASSERT(!RedEngine::collision_engine(a, b));

}

void ColEngineTest::tearDown()
{
    game->stop(RedEngine::TEST_EXIT);
    delete game;
}
