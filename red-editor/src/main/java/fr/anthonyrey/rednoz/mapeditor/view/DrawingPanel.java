package fr.anthonyrey.rednoz.mapeditor.view;

import fr.anthonyrey.rednoz.mapeditor.model.AppConsts;
import fr.anthonyrey.rednoz.mapeditor.model.Sprite;

import javax.swing.*;
import java.awt.*;
import java.util.ArrayList;

/*
	DrawingPanel.java is part of
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
public class DrawingPanel extends JPanel {

    //4 hardcoded layers
    public ArrayList<ArrayList<Sprite>> sprites;
    public Point selectorPos;
    public int selectedLayer;
    public boolean showAll;
    public boolean showNums;

    public DrawingPanel()
    {
        sprites = new ArrayList<>();
        sprites.add(new ArrayList<>());
        sprites.add(new ArrayList<>());
        sprites.add(new ArrayList<>());
        sprites.add(new ArrayList<>());

        selectorPos = new Point(0,0);
        selectedLayer = 0;
        showAll = true;
        showNums = true;
    }

    @Override
    public void paint(Graphics g) {
        super.paint(g);

        int i = 0;

        for(ArrayList<Sprite> layer : sprites)
        {
            if(!showAll && i != selectedLayer)
            {
                i++;
                continue;
            }


            for(Sprite spr : layer)
            {
                g.drawImage(spr.getImage(), spr.getX(), spr.getY(), null);

                if(showNums)
                {
                    g.setColor(new Color(255,0,0));
                    g.drawString(""+i, spr.getX(), spr.getY()+ AppConsts.SPRITE_SIZE);

                }

            }

            i++;

        }

        g.setColor(new Color(0,0,0));
        g.drawRect(selectorPos.x, selectorPos.y, AppConsts.SPRITE_SIZE, AppConsts.SPRITE_SIZE);

    }

    public void addSprite(Sprite spr)
    {

        for(Sprite spr2 : sprites.get(selectedLayer))
        {
            if(spr2.getX() == spr.getX() && spr2.getY() == spr.getY())
            {
                JOptionPane.showMessageDialog(this.getParent(), "You can't put two sprites at the same spot on the same layer");
                return;
            }
        }
        sprites.get(selectedLayer).add(spr);
        this.repaint();
    }

    public void removeSprite(Point position)
    {
        Sprite toDelete = null;

        for(Sprite spr : sprites.get(selectedLayer))
        {
            if(spr.getX() == position.x && spr.getY() == position.y)
                toDelete = spr;
        }

        if(toDelete != null)
        {
            sprites.get(selectedLayer).remove(toDelete);
        }

        this.repaint();

    }

    public void deleteAll()
    {
        sprites = new ArrayList<>();
        sprites.add(new ArrayList<>());
        sprites.add(new ArrayList<>());
        sprites.add(new ArrayList<>());
        sprites.add(new ArrayList<>());
        this.repaint();
    }

}
