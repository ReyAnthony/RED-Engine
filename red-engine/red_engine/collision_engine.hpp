/*
    collision_engine.hpp is part of
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

#ifndef Red_COLLISION_ENGINE_HPP
#define Red_COLLISION_ENGINE_HPP

#include "engine_core.hpp"

namespace RedEngine {

    bool collision_engine(Sprite *spr1, Sprite *spr2);
}


#endif //Red_COLLISION_ENGINE_HPP
