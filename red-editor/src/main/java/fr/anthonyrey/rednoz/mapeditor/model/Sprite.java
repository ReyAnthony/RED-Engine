package fr.anthonyrey.rednoz.mapeditor.model;

import java.awt.*;
import java.awt.image.BufferedImage;
import java.io.IOException;
import java.io.Serializable;

/*
	Sprite.java is part of
	RED-ENGINE Map Editor - A map editor for RED-ENGINE
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

public class Sprite implements Serializable{

    private Image image;
    private Point position;
    private char assoc;

    public Sprite(BufferedImage image, Point position, char assoc) throws IOException {

        this.image =  image.getScaledInstance(AppConsts.SPRITE_SIZE,AppConsts.SPRITE_SIZE,0);
        this.position = position;
        this.assoc = assoc;
    }

    public Image getImage() {
        return image;
    }

    public int getX() {
        return position.x;
    }

    public int getY() {
        return position.y;
    }

    public boolean equals(Object other)
    {
        if(other instanceof Sprite)
        {
            Sprite spr = (Sprite) other;

            if(spr.position.equals(this.position) &&
                    spr.image.equals(this.image))
            {
                return true;
            }

        }

        return false;

    }

    public char getAssoc() {
        return assoc;
    }
}
