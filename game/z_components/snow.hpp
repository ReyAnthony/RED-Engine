//
// Created by Anthony REY on 20/12/2015.
//

#ifndef SNOW_HPP
#define SNOW_HPP

#include "red_engine/engine_core.hpp"

class SnowFlake
{
    public:
        SnowFlake(int x, int y, int size);
        ~SnowFlake();

        int getX();
        int getY();
        int getSize();

        int setX(int x);
        int setY(int y);
        int setSize(int size);

        void draw();

    private:
        int x;
        int y;
        int size;
};

class SnowComponent : public RedEngine::GameComponent
{
    public:
        SnowComponent(int count);
        ~SnowComponent();

        void init();
        void update();
        void draw();

    private:
        SnowFlake** snowFlakes;
        int snowFlakes_count;
};


#endif //Red-_SNOW_HPP
