/*
  graphic_engine.hpp is part of RED-ENGINE - An Object-Oriented game
  engine based on Allegro5 Copyright (C) 2015 - 2016 Anthony REY

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

#ifndef GRAPHIC_ENGINE_H
#define GRAPHIC_ENGINE_H

#include "engine_core.hpp"

namespace RedEngine
{
    class GraphicEngine
    {

    public:

	GraphicEngine(int virtual_width, int virtual_height,
		     int real_width, int real_height, const char* title,
		     bool isFullscreen, bool isResizable);

	void setBackgroundColor(unsigned int r, unsigned int g, unsigned int b);

	int getWidth();
	int getHeight();

	void stop(int errorCode);
	      
       	void transformTranslate(int x, int y);
	void resetTransformTranslate();

       	void update(GameScene* scene);
	void drawAll(GameScene* scene);
	void draw(GameScene* scene);


    private :

	void init();
		
	const char *title;
	
	int virtual_width;
	int virtual_height;
	int real_width;
	int real_height;
	bool isFullscreen;
	bool isResizable;

	ALLEGRO_COLOR bkg_color;
	ALLEGRO_TRANSFORM camera_transform;
	ALLEGRO_DISPLAY *display;

	bool running;
	bool redraw;

	ALLEGRO_EVENT ev;
	ALLEGRO_EVENT_QUEUE *event_queue;
	ALLEGRO_TIMER *timer;

	static const int FPS = 60;
    };

}

#endif


