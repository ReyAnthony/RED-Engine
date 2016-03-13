#Makefile
#RED-Engine
#GPLv3
#Copyright (c) 2015-2016 Anthony REY

#WINDOWS USERS :
    #You need to download Allegro mingw from : https://www.allegro.cc/files/ and put the files in mingw dir.
    #You need to install mingw (with g++ as this is C++)
    #I personnaly run the makefile from babun shell on Windows (don't forget to add mingw/bin to path)
    #UNCOMMENT THE FOR WIN VALUES AND COMMENT THE OTHERS

#THIS PROJECT USE ASPECTC++ It needs to be added to the path
ASPECTCC=ag++
CC=g++

#WINDOWS
#-Wl,--subsystem,windows prevent the console from running in the background
#CCFLAGS=-std=gnu++1y -Wall -O3 -DDEBUG -Wl,--subsystem,windows
#LIB_PATH=c:/mingw/
#ALLEGRO=$(LIB_PATH)lib/liballegro-5.0.10-monolith-mt.a
#OUTPUT=RED.exe

#OSX (Linux ?)
CCFLAGS= -std=c++11 -Wall -O3 -DDEBUG
LIB_PATH=/usr/local/
ALLEGRO=`pkg-config --cflags --libs allegro-5.0 allegro_acodec-5.0 allegro_audio-5.0 allegro_color-5.0 allegro_dialog-5.0 allegro_font-5.0 allegro_image-5.0 allegro_main-5.0 allegro_memfile-5.0 allegro_physfs-5.0 allegro_primitives-5.0 allegro_ttf-5.0`
OUTPUT=RED.out

engine=./
game=../game/

all:$(OUTPUT)

#We should have one goal for each .cpp file
$(OUTPUT) : red_engine.a
	$(CC)  $(CCFLAGS) \
	-o $(game)$(OUTPUT) \
	$(game)main.cpp \
	$(game)z_scenes/overworld.cpp \
	$(game)z_scenes/transition_scene.cpp \
	$(game)z_components/map.cpp \
	$(game)z_components/player.cpp \
	$(game)z_components/snow.cpp \
	$(LIB_PATH)lib/red_engine.a \
	$(ALLEGRO)

#TODO tests

# ENGINE
red_engine.a: engine_core.o keyboard_engine.o map.o collision_engine.o transitions.o sound_engine.o sprite.o datapool.o game_components.o game_scene.o copy_hpp
	ar rvs $(LIB_PATH)lib/red_engine.a \
	engine_core.o \
	keyboard_engine.o \
	map.o \
	collision_engine.o \
	transitions.o \
	sound_engine.o \
	sprite.o \
	datapool.o \
	game_components.o \
	game_scene.o
	ranlib $(LIB_PATH)lib/red_engine.a

copy_hpp:
	mkdir -p $(LIB_PATH)include/red_engine/
	cp $(engine)keyboard_engine.hpp $(LIB_PATH)include/red_engine/keyboard_engine.hpp
	cp $(engine)engine_core.hpp $(LIB_PATH)include/red_engine/engine_core.hpp
	cp $(engine)map.hpp $(LIB_PATH)include/red_engine/map.hpp
	cp $(engine)transitions.hpp $(LIB_PATH)include/red_engine/transitions.hpp
	cp $(engine)collision_engine.hpp $(LIB_PATH)include/red_engine/collision_engine.hpp
	cp $(engine)sound_engine.hpp $(LIB_PATH)include/red_engine/sound_engine.hpp
	cp $(engine)sprite.hpp $(LIB_PATH)include/red_engine/sprite.hpp
	cp $(engine)datapool.hpp $(LIB_PATH)include/red_engine/datapool.hpp
	cp $(engine)game_components.hpp $(LIB_PATH)include/red_engine/game_components.hpp
	cp $(engine)game_scene.hpp $(LIB_PATH)include/red_engine/game_scene.hpp		

$(engine).cpp.o:
	$(ASPECTCC) $(CCFLAGS) -c \
	$(engine)$<

#CLEAN
clean:clean-engine
	rm $(game)$(OUTPUT)
	rm -r $(LIB_PATH)include/red_engine/

clean-engine:
	rm *.o

