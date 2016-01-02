#!/usr/bin/env bash

g++ -std=gnu++1y \
source/keyboard_engine_tests.cpp \
source/col_engine_tests.cpp \
source/tests_main.cpp \
source/sound_engine_tests.cpp \
-o tests.out -lcppunit /usr/local/lib/red_engine/red_engine.a \
`pkg-config --cflags --libs allegro-5.0 allegro_acodec-5.0 allegro_audio-5.0 allegro_color-5.0 allegro_dialog-5.0 allegro_font-5.0 allegro_image-5.0 allegro_main-5.0 allegro_memfile-5.0 allegro_physfs-5.0 allegro_primitives-5.0 allegro_ttf-5.0`

./tests.out