/*
    transition.hpp is part of
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

#ifndef RED_ENGINE_TRANSITIONS_HPP
#define RED_ENGINE_TRANSITIONS_HPP

#include "engine_core.hpp"

namespace RedEngine
{
    class TransitionTypeA : public GameComponent
    {
        public:
            TransitionTypeA(bool showBackScene);
            ~TransitionTypeA();
            void start();
            bool isFinished();

    protected:

            int x;
            int y;
            bool done = false;
            bool started = false;
            bool showBackScene = false;
            int speed = 25;

            void init();
            void update();
            void draw();
    };

    class TransitionTypeB : public TransitionTypeA
    {
    public:
        using TransitionTypeA::TransitionTypeA;

    private:
        void init();
        void update();
        void draw();
    };
}
#endif //RED_ENGINE_TRANSITIONS_HPP
