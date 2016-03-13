/*
  game_components.hpp is part of RED-ENGINE - An Object-Oriented game
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

#ifndef GAME_COMPONENTS_H
#define GAME_COMPONENTS_H

namespace RedEngine
{
    class Manager;
    
    class GameComponent {
    public:
	GameComponent(bool back);
	//FIXME using virtual makes the program crash
	/*virtual*/  ~GameComponent();
	bool getIsBack();

	virtual void init() = 0;
	virtual void update() = 0;
	virtual void draw() = 0;

	friend class Manager;
	// when pushing into the manager, the GameScene will pass it into the method
	void setManager(Manager *manager);

    protected:
	Manager *getManager();

    private:
	// should it be drawn at the back ?
	bool isBack;
	Manager *manager;
    };
}
#endif
