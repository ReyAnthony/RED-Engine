package fr.anthonyrey.rednoz.mapeditor.controller;

import fr.anthonyrey.rednoz.mapeditor.model.ImageCellRenderer;
import fr.anthonyrey.rednoz.mapeditor.model.Sprite;
import fr.anthonyrey.rednoz.mapeditor.view.EditorFrame;

import javax.imageio.ImageIO;
import javax.swing.*;
import java.awt.*;
import java.awt.event.*;
import java.awt.image.BufferedImage;
import java.io.*;
import java.util.ArrayList;

/*
	EditorController.java is part of
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

public class EditorController implements ActionListener, AWTEventListener, MouseListener, ItemListener{

    private EditorFrame view;
    private Point position;

    public EditorController()
    {

        view = new EditorFrame();
        position = new Point(0,0);

        view.add.addActionListener(this);
        view.drawingPanel.addMouseListener(this);
        Toolkit.getDefaultToolkit().addAWTEventListener(this, AWTEvent.KEY_EVENT_MASK);
        setPosition();
        view.drawingPanel.setPreferredSize(new Dimension(1024,1024));

        for(int i = 0; i < view.drawingPanel.sprites.size(); i++)
        {
            view.selectedLayer.addItem("Layer "+i);
        }

        view.selectedLayer.addItemListener(this);
        view.showLayers.addItemListener(this);
        view.showLayersNum.addItemListener(this);
        view.removeAll.addActionListener(this);
        view.delete.addActionListener(this);
        view.about.addActionListener(this);
        view.quit.addActionListener(this);
        view.centerView.addActionListener(this);

        view.saveMap.addActionListener(this);

        //TODO jar bug
        DefaultListModel<BufferedImage> model =  new DefaultListModel<>();

        try {
            for(File f : new File(this.getClass().getResource("/fr/anthonyrey/rednoz/sprites/").getPath()).listFiles((dir, name) -> {
                if(name.endsWith(".png"))
                    return true;
                else
                    return false;
            })) {
                model.addElement(ImageIO.read(f));
            }
        } catch (IOException e) {
            e.printStackTrace();
        }

        view.components.setCellRenderer(new ImageCellRenderer());
        view.components.setModel(model);
        view.components.setSelectedIndex(0);


    }

    private void setPosition()
    {
        view.cursorPos.setText("X : "+position.x+ " - Y : "+position.y);

    }

    @Override
    public void itemStateChanged(ItemEvent e) {

        if(e.getSource().equals(view.selectedLayer))
            view.drawingPanel.selectedLayer = view.selectedLayer.getSelectedIndex();

        if(e.getSource().equals(view.showLayers))
            view.drawingPanel.showAll = !view.drawingPanel.showAll;

        if(e.getSource().equals(view.showLayersNum))
            view.drawingPanel.showNums = !view.drawingPanel.showNums;

        view.drawingPanel.repaint();

    }

    @Override
    public void actionPerformed(ActionEvent e) {

        if(e.getSource().equals(view.add))
        {
            try {
                view.drawingPanel.addSprite(new Sprite(view.components.getSelectedValue(),
                        (Point) position.clone()));
            } catch (IOException e1) {
                e1.printStackTrace();
            }
        }

        if(e.getSource().equals(view.removeAll))
            view.drawingPanel.deleteAll();

        if(e.getSource().equals(view.delete))
            view.drawingPanel.removeSprite(position);

        if(e.getSource().equals(view.about))
            JOptionPane.showMessageDialog(view, "The 'RED Engine map editor' is copyright (c) 2015-2016, Anthony REY");

        if(e.getSource().equals(view.quit))
            System.exit(0);

        if(e.getSource().equals(view.saveMap))
            saveMap();

        if(e.getSource().equals(view.centerView))
        {
            int posX = (int) view.drawingPanel.selectorPos.getX();
            int posY = (int) view.drawingPanel.selectorPos.getY();

            view.scrollPane.getHorizontalScrollBar().setValue(posX);
            view.scrollPane.getVerticalScrollBar().setValue(posY);

        }


    }

    private void loadMap()
    {

    }

    private void saveMap()
    {
        try {

            JFileChooser chooser = new JFileChooser();
            chooser.showSaveDialog(view);
            File f;

            if((f = chooser.getSelectedFile()) != null)
            {
                ObjectOutputStream oos =  new ObjectOutputStream(new FileOutputStream(f));
                oos.writeObject(view.drawingPanel);
            }

        } catch (IOException e) {
            e.printStackTrace();
        }


    }

    private void saveMapXml()
    {
        ArrayList<ArrayList<Sprite>>  base = view.drawingPanel.sprites;
        StringBuilder xmlOut = new StringBuilder();

        int layer = 0;
        xmlOut.append("<layers>\n");

        for (ArrayList<Sprite> listSpr : base)
        {

            xmlOut.append("\t<layer id="+ layer+ ">\n");

            for(Sprite spr : listSpr)
            {
                xmlOut.append("\t\t<sprite x="+spr.getX()+" y="+spr.getY()+ "/>\n");
            }

            xmlOut.append("\t</layer>\n");
            layer++;
        }

        xmlOut.append("</layers>");

        JFileChooser chooser = new JFileChooser();
        chooser.showSaveDialog(view);

        File f = chooser.getSelectedFile();

        if(f != null)
        {


            try ( FileOutputStream fos = new FileOutputStream(f)) {

                try (DataOutputStream dos = new DataOutputStream(fos)) {
                    dos.writeBytes(xmlOut.toString());
                }


            } catch (IOException e) {

                JOptionPane.showMessageDialog(view, "Error while writing the file", null, JOptionPane.ERROR_MESSAGE);
            }

        }
        else
        {
            JOptionPane.showMessageDialog(view, "You must select an output file", null, JOptionPane.ERROR_MESSAGE);

        }

        System.out.println(xmlOut);
    }


    @Override
    public void eventDispatched(AWTEvent event) {

        if(!view.components.hasFocus())
        {

            int width = view.drawingPanel.getWidth();
            int height = view.drawingPanel.getHeight();

            KeyEvent e = (KeyEvent) event;

            if(e.getID() == KeyEvent.KEY_PRESSED)
            {
                if(e.getKeyCode() == KeyEvent.VK_RIGHT)
                {
                    if(position.x +32 < width)
                        position.x += 32;
                }
                else if(e.getKeyCode() == KeyEvent.VK_LEFT)
                {
                    if(position.x -32 >= 0)
                        position.x -= 32;
                }
                else if(e.getKeyCode() == KeyEvent.VK_UP)
                {
                    if(position.y -32 >= 0)
                        position.y -= 32;
                }
                else if(e.getKeyCode() == KeyEvent.VK_DOWN)
                {
                    if(position.y +32 < height)
                        position.y += 32;
                }

            //Buggy
            int posX = view.scrollPane.getViewport().getViewPosition().x;
            int posY = view.scrollPane.getViewport().getViewPosition().y;

            if(position.x >= posX + view.scrollPane.getWidth() - 32)
            {
                view.scrollPane.getHorizontalScrollBar().setValue(posX+32);
            }
            else if(position.x <=  posX)
            {
                view.scrollPane.getHorizontalScrollBar().setValue(posX-32);

            }

            if(position.y >= posY + view.scrollPane.getHeight() - 32)
            {
                view.scrollPane.getVerticalScrollBar().setValue(posY+32);
            }
            else if(position.y <=  posY)
            {
                view.scrollPane.getVerticalScrollBar().setValue(posY-32);

            }

                view.drawingPanel.selectorPos = position;
                view.drawingPanel.repaint();
                setPosition();

            }

        }


    }

    @Override
    public void mouseClicked(MouseEvent e) {

        if(e.getSource().equals(view.drawingPanel))
        {
            view.requestFocus();
        }
    }

    @Override
    public void mousePressed(MouseEvent e) {

    }

    @Override
    public void mouseReleased(MouseEvent e) {

    }

    @Override
    public void mouseEntered(MouseEvent e) {

    }

    @Override
    public void mouseExited(MouseEvent e) {

    }


}
