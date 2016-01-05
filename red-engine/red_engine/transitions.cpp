/*
    transition.cpp is part of
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

#include "transitions.hpp"

namespace RedEngine {

    //a transition is never on the back
    TransitionTypeA::TransitionTypeA(bool showBackScene) : GameComponent(false)
    {
        this->showBackScene = showBackScene;
    }

    TransitionTypeA::~TransitionTypeA()
    {

    }

    void TransitionTypeA::init()
    {
        x = 0;
        y = 0;
        done = false;

        this->getManager()->shouldDrawBackScene(showBackScene, false);
    }

    void TransitionTypeA::start()
    {
        this->started = true;
    }

    void TransitionTypeA::update()
    {
        if(started) {
            y+= 10;

            if (y >= this->getManager()->getHeight()) {
                done = true;
                this->getManager()->shouldDrawBackScene(false, false);
            }
        }
    }

    void TransitionTypeA::draw()
    {
        if(!done && started)
        {
            //draw everything to the current y and x pos
            int cur_y;
            for(cur_y = 0; cur_y <= y; cur_y++)
            {
                //draw a line
                al_draw_line(0, cur_y, getManager()->getWidth(), cur_y, al_map_rgb(0,0,0), 1);
             }
        }
    }

    bool TransitionTypeA::isFinished()
    {
        return this->done;
    }


    //########## TRANSITION B #########

    void TransitionTypeB::init()
    {
        x = this->getManager()->getWidth();
        y = this->getManager()->getHeight();
        done = false;

        this->getManager()->shouldDrawBackScene(showBackScene, false);
    }

    void TransitionTypeB::update()
    {
        if(started) {
            y-= 25;

            if (y <= 0) {
                done = true;
                this->getManager()->shouldDrawBackScene(false, false);
            }
        }
    }

    void TransitionTypeB::draw()
    {
        if(!done && started)
        {
            al_draw_filled_rectangle(0, 0, getManager()->getWidth(), y, al_map_rgb(0,0,0));
        }
    }

}
