#!/usr/bin/env bash
g++ -std=gnu++1y -Wall -c engine_core.cpp keyboard_engine.cpp map.cpp collision_engine.cpp transitions.cpp
mkdir /usr/local/lib/red_engine/
ar rvs /usr/local/lib/red_engine/red_engine.a engine_core.o keyboard_engine.o map.o collision_engine.o transitions.o
rm *.o
mkdir /usr/local/include/red_engine/
cp keyboard_engine.hpp /usr/local/include/red_engine/keyboard_engine.hpp
cp engine_core.hpp /usr/local/include/red_engine/engine_core.hpp
cp map.hpp /usr/local/include/red_engine/map.hpp
cp transitions.hpp /usr/local/include/red_engine/transitions.hpp
cp collision_engine.hpp /usr/local/include/red_engine/collision_engine.hpp