cmake_minimum_required(VERSION 3.3)
project(RED_Engine)

set(game_VERSION_MAJOR 0)
set(game_VERSION_MINOR 1)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall")

set(ENGINE_SRC
        red_engine/engine_core.cpp
        red_engine/keyboard_engine.cpp
        red_engine/map.cpp
        red_engine/collision_engine.cpp
        red_engine/transitions.cpp
        )

ADD_LIBRARY(red_engine_lib STATIC
        ${ENGINE_SRC})

set(SOURCE_FILES
        game/z_scenes/
        game/main.cpp
        game/z_scenes/)
add_executable(RED_Engine ${SOURCE_FILES})

find_package(PkgConfig)
pkg_check_modules(ALLEGRO
        allegro-5.0
        allegro_acodec-5.0
        allegro_audio-5.0
        allegro_color-5.0
        allegro_dialog-5.0
        allegro_font-5.0
        allegro_image-5.0
        allegro_main-5.0
        allegro_memfile-5.0
        allegro_physfs-5.0
        allegro_primitives-5.0
        allegro_ttf-5.0)

target_include_directories(red_engine_lib PUBLIC ${ALLEGRO_INCLUDE_DIRS})
target_include_directories(red_engine_lib PUBLIC RED_engine/)

target_link_libraries(red_engine_lib rednoz_engine ${ALLEGRO_LIBRARIES} )



