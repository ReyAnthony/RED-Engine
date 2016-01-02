package fr.anthonyrey.rednoz.mapeditor.model;

import javax.swing.*;
import java.awt.*;
import java.awt.image.BufferedImage;

/*
	ImageCellRenderer.java is part of
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
public class ImageCellRenderer extends JLabel implements ListCellRenderer<BufferedImage> {

    public ImageCellRenderer()
    {
        this.setOpaque(true);
    }

    @Override
    public Component getListCellRendererComponent(JList<? extends BufferedImage> list, BufferedImage value, int index,
                                                  boolean isSelected, boolean cellHasFocus) {
        Color background;

        this.setIcon(new ImageIcon(value));
        this.setHorizontalAlignment(JLabel.CENTER);

        if(!isSelected)
        {
            background = Color.WHITE;
        }
        else
        {
            background = Color.BLUE;
        }

        setBackground(background);
        return this;
    }
}
