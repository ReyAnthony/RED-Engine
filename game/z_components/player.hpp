//
// Created by Anthony REY on 20/12/2015.
//

#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "red_engine/engine_core.hpp"

class PlayerComponent : public RedEngine::GameComponent
{
    public:
        PlayerComponent(int x, int y);
        ~PlayerComponent();

        void init();
        void update();
        void draw();

        RedEngine::Sprite* getSprite();

    private:
        RedEngine::Sprite* player;
        int start_x;
        int start_y;
};

#endif //PLAYER_HPP
