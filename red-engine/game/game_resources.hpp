/*
	game_resources.hpp is part of
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

#ifndef RED_ENGINE_GAME_RESOURCES_HPP
#define RED_ENGINE_GAME_RESOURCES_HPP

#include <string>

namespace game_resources
{
    //SPRITES
    static std::string SNOW = "null";
    static std::string TREES = "trees";
    static std::string MOUNTAINS = "mountains";
    static std::string WATER = "water";
    static std::string WALL = "wall";
    static std::string HILDA = "hilda";

    //FONTS
    static std::string SOURCE_CODE_15 = "source_15";
    static std::string VALIANT_50 = "valiant_50";
    static std::string VALIANT_25 = "valiant_25";

    //MUSIC & SOUND
    static std::string OVERWORLD_MUSIC = "overworld_music";
    static std::string TRANS_1 = "trans_1";
    static std::string TRANS_2 = "trans_2";
};

#endif //RED_ENGINE_GAME_RESOURCES_HPP
