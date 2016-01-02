/*
	tests_main.cpp is part of
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

#include "tests_main.hpp"

int main(int argc, char** argv)
{

    std::cout << "Starting Allegro" << std::endl;

    //Initializing allegro
    al_init();
    al_install_keyboard();
    al_init_image_addon();
    al_init_primitives_addon();
    al_install_audio();
    al_init_acodec_addon();

    std::cout << "Allegro init finished" << std::endl;
    std::cout << "Starting test runner" << std::endl;

    CppUnit::TextUi::TestRunner runner;
    runner.addTest(KeyboardEngineTest::suite());
    runner.run();

    //return 1 if failed tests
    return 0;
}