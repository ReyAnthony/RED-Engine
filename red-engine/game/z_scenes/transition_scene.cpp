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

#include "transition_scene.hpp"

TransitionScene::TransitionScene() {

}

TransitionScene::~TransitionScene() {

}

void TransitionScene::init() {

    transition = new RedEngine::TransitionTypeB(true);
    addComponent(transition);
    transition->start();
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