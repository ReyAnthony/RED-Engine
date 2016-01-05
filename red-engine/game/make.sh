#!/usr/bin/env bash

g++ -std=gnu++1y -o RED.out -Wall \
main.cpp \
z_scenes/overworld.cpp \
z_scenes/transition_scene.cpp \
z_components/map.cpp \
z_components/player.cpp \
z_components/snow.cpp \
/usr/local/lib/red_engine/red_engine.a \
`pkg-config --cflags --libs allegro-5.0 allegro_acodec-5.0 allegro_audio-5.0 allegro_color-5.0 allegro_dialog-5.0 allegro_font-5.0 allegro_image-5.0 allegro_main-5.0 allegro_memfile-5.0 allegro_physfs-5.0 allegro_primitives-5.0 allegro_ttf-5.0`