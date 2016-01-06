/*
	transition_scene.cpp is part of
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

#include <sys/time.h>
#include "transition_scene.hpp"
#include "../game_resources.hpp"

TransitionScene::TransitionScene() {

}

TransitionScene::~TransitionScene() {

}

void TransitionScene::init() {

    transition = new RedEngine::TransitionTypeB(true);
    addComponent(transition);
    transition->start();
    this->getManager()->getSoundEngine()->playSound(game_resources::TRANS_1);
}

void TransitionScene::update() {

    if(transition->isFinished())
    {
        this->getManager()->popScene();
    }
}

void TransitionScene::draw() {
    //no need to draw because the componenent is managing itself
}


//############ Quit transition scene #########

QuitTransitionScene::QuitTransitionScene() {

}

QuitTransitionScene::~QuitTransitionScene() {

}

void QuitTransitionScene::init() {

    transition = new RedEngine::TransitionTypeA(true);
    addComponent(transition);
    transition->start();
    this->getManager()->getSoundEngine()->playSound(game_resources::TRANS_2);
    getManager()->setBackgroundColor(0,0,0);

}

void QuitTransitionScene::update() {

    if(transition->isFinished())
    {
        counter++;
    }
}

void QuitTransitionScene::draw() {

    if(transition->isFinished())
    {
        //TODO remove allegro references and improve, as this is just to test...

        ALLEGRO_TRANSFORM camera_transform;
        al_identity_transform(&camera_transform);
        al_translate_transform(&camera_transform, 0, 0);
        al_use_transform(&camera_transform);

        int center_w = getManager()->getWidth() / 2;
        int center_h = getManager()->getHeight() / 2;

        al_draw_text(getManager()->getFont(game_resources::VALIANT_50), al_map_rgb(255,255,255),
                     center_w, center_h - 50, ALLEGRO_ALIGN_CENTRE, "Farewell !");
        al_draw_text(getManager()->getFont(game_resources::VALIANT_25), al_map_rgb(255,255,255),
                     center_w, center_h + 25, ALLEGRO_ALIGN_CENTRE,
                     "The scribes are writting down your gallant deeds ...");

        if(counter >= 120)
        {
            this->getManager()->stop(RedEngine::StopCodes::PLAYER_EXIT);
        }

    }
}
