package fr.anthonyrey.rednoz.mapeditor.controller;

import fr.anthonyrey.rednoz.mapeditor.model.AppConsts;
import fr.anthonyrey.rednoz.mapeditor.model.AssocData;
import fr.anthonyrey.rednoz.mapeditor.model.ImageCellRenderer;
import fr.anthonyrey.rednoz.mapeditor.model.Sprite;
import fr.anthonyrey.rednoz.mapeditor.view.EditorFrame;

import javax.imageio.ImageIO;
import javax.swing.*;
import java.awt.*;
import java.awt.event.*;
import java.io.File;
import java.io.IOException;
import java.io.InputStream;
import java.util.ArrayList;
import java.util.List;
import java.util.Properties;

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
    private AssocData nullAssoc;

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

        try {
            createSideSelectionBar();
        } catch (Exception e) {
            new JOptionPane().showMessageDialog(view, e.getMessage(), "Error", JOptionPane.ERROR_MESSAGE );
            e.printStackTrace();
            System.exit(0);
        }

    }

    private void createSideSelectionBar() throws Exception {
        //TODO won't work inside a jar (can't create a file from a jar (need path / url)

        //1) we get associated values from the properties files
        Properties assocProp = new Properties();
        assocProp.load(this.getClass().getResourceAsStream("/fr/anthonyrey/rednoz/assoc/assoc.properties"));
        checkPropertiesKeys(assocProp);
        checkPropertiesValues(assocProp);
        DefaultListModel<AssocData> model = createModel( generateAssocData(assocProp));

        view.components.setCellRenderer(new ImageCellRenderer());
        view.components.setModel(model);
        view.components.setSelectedIndex(0);
    }

    private void checkPropertiesKeys(Properties assocProp) throws Exception {

        for(Object s : assocProp.keySet())
        {
           if(((String) s).length() > 1)
           {
               //too lazy to create an exception, who cares it's a map editor
               throw new Exception("Propertie file is invalid : has a 2+ chars key, program will halt");
           }
        }
    }

    private void checkPropertiesValues(Properties assocProp) throws Exception {

        boolean hasANullValue = false;

        for(Object s : assocProp.keySet())
        {
            String propValue = assocProp.getProperty((String) s);

            //first null
            if(propValue.equalsIgnoreCase("null") && !hasANullValue)
            {
                hasANullValue = true;
                //no need to check if it is a null for the .png check
                continue;
            }
            //2+
            else if(propValue.equalsIgnoreCase("null") && hasANullValue)
            {
                throw new Exception("Only 1 null value is needed in the config file");
            }

            if(!propValue.endsWith(".png"))
            {
                //too lazy to create an exception, who cares it's a map editor
                throw new Exception("The mapped data should be a .png file");
            }
        }
    }

    private List<AssocData> generateAssocData(Properties assocProp) throws IOException {

        ArrayList<AssocData> assocData = new ArrayList<>();

        for(Object s : assocProp.keySet())
        {
            String propValue = assocProp.getProperty((String) s);
            if(propValue.equalsIgnoreCase("null"))
            {
                //jumps it, that's normal, we'll use the mapped key for void cells
                //but it hsould be there only once, we check for it before anyway
                nullAssoc = new AssocData(null, ((String) s).charAt(0));
            }
            else
            {
                InputStream image = this.getClass().getResourceAsStream(propValue);
                assocData.add(new AssocData(ImageIO.read(image) , ((String) s).charAt(0)));
            }

        }

        return assocData;
    }

    private DefaultListModel<AssocData> createModel(List<AssocData> list)
    {
        DefaultListModel<AssocData> model = new DefaultListModel<>();
        for(AssocData element : list)
        {
            model.addElement(element);
        }

        return model;
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
                view.drawingPanel.addSprite(new Sprite(view.components.getSelectedValue().getImage(),
                        (Point) position.clone(), view.components.getSelectedValue().getValue()));
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

        JFileChooser chooser = new JFileChooser();
        chooser.showSaveDialog(view);
        File f;

        //first we check the size of the map
        int width = view.drawingPanel.getWidth() / AppConsts.SPRITE_SIZE;
        int height = view.drawingPanel.getHeight() / AppConsts.SPRITE_SIZE;



        if((f = chooser.getSelectedFile()) != null)
        {
            for(ArrayList<Sprite> layer : view.drawingPanel.sprites)
            {
                for(Sprite spr : layer)
                {

                }
            }
        }


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
                    if(position.x +AppConsts.SPRITE_SIZE < width)
                        position.x += AppConsts.SPRITE_SIZE;
                }
                else if(e.getKeyCode() == KeyEvent.VK_LEFT)
                {
                    if(position.x -AppConsts.SPRITE_SIZE >= 0)
                        position.x -= AppConsts.SPRITE_SIZE;
                }
                else if(e.getKeyCode() == KeyEvent.VK_UP)
                {
                    if(position.y -AppConsts.SPRITE_SIZE >= 0)
                        position.y -= AppConsts.SPRITE_SIZE;
                }
                else if(e.getKeyCode() == KeyEvent.VK_DOWN)
                {
                    if(position.y +AppConsts.SPRITE_SIZE < height)
                        position.y += AppConsts.SPRITE_SIZE;
                }

            //Buggy
            int posX = view.scrollPane.getViewport().getViewPosition().x;
            int posY = view.scrollPane.getViewport().getViewPosition().y;

            if(position.x >= posX + view.scrollPane.getWidth() - AppConsts.SPRITE_SIZE)
            {
                view.scrollPane.getHorizontalScrollBar().setValue(posX+AppConsts.SPRITE_SIZE);
            }
            else if(position.x <=  posX)
            {
                view.scrollPane.getHorizontalScrollBar().setValue(posX-AppConsts.SPRITE_SIZE);

            }

            if(position.y >= posY + view.scrollPane.getHeight() - AppConsts.SPRITE_SIZE)
            {
                view.scrollPane.getVerticalScrollBar().setValue(posY+AppConsts.SPRITE_SIZE);
            }
            else if(position.y <=  posY)
            {
                view.scrollPane.getVerticalScrollBar().setValue(posY-AppConsts.SPRITE_SIZE);

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
