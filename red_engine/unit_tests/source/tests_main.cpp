//
// Created by Anthony REY on 30/12/2015.
//

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