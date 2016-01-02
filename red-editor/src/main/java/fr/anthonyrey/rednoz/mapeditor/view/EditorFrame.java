package fr.anthonyrey.rednoz.mapeditor.view;

import javax.swing.*;
import java.awt.*;
import java.awt.image.BufferedImage;

/*
	EditorFrame.java is part of
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

public class EditorFrame extends JFrame {

    public JButton add;
    public JButton delete;
    public DrawingPanel drawingPanel;
    public JLabel cursorPos;
    public JScrollPane scrollPane;
    public JCheckBox showLayers;
    public JComboBox<String> selectedLayer;
    public JList<BufferedImage> components;
    public JButton removeAll;
    public JCheckBox showLayersNum;
    public JMenuItem newMap;
    public JMenuItem loadMap;
    public JMenuItem quit;
    public JMenuItem about;
    public JMenuItem saveMap;
    public JMenuItem centerView;
    public JComboBox<String> componentType;


    public EditorFrame()
    {
        this.setSize(640,512);
        this.setMinimumSize(new Dimension(800, 512));

        this.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        this.setFocusable(true);
        this.setTitle("RED Engine map editor");
        this.setLayout(new BorderLayout());

        JMenuBar menuBar = new JMenuBar();
        JMenu file = new JMenu("File");
        menuBar.add(file);

        newMap = new JMenuItem("New map");
        saveMap = new JMenuItem("Save map");
        loadMap = new JMenuItem("Load map");
        quit = new JMenuItem("Quit");

        file.add(newMap);
        file.add(loadMap);
        file.add(saveMap);
        file.add(quit);

        JMenu tools = new JMenu("Tools");
        centerView = new JMenuItem("Center view to pointer");
        tools.add(centerView);

        menuBar.add(tools);

        JMenu help = new JMenu("Help");
        about = new JMenuItem("About");

        help.add(about);

        menuBar.add(help);

        this.setJMenuBar(menuBar);

        JPanel toolbox = new JPanel();
        add = new JButton("Add");
        delete = new JButton("Delete");
        showLayers = new JCheckBox("Show all layers", true);
        selectedLayer = new JComboBox<>();
        removeAll = new JButton("Remove all");
        showLayersNum = new JCheckBox("Show layers nums on sprites", true);

        toolbox.add(add);
        toolbox.add(delete);
        toolbox.add(showLayers);
        toolbox.add(showLayersNum);
        toolbox.add(selectedLayer);
        toolbox.add(removeAll);


        drawingPanel = new DrawingPanel();
        scrollPane = new JScrollPane(drawingPanel);

        cursorPos = new JLabel();

        components = new JList<>();
        components.setPreferredSize(new Dimension(40,120));
        components.setSelectionMode(ListSelectionModel.SINGLE_SELECTION);

        this.add(toolbox, BorderLayout.PAGE_START);
        this.add(scrollPane, BorderLayout.CENTER);
        this.add(components, BorderLayout.LINE_END);
        this.add(cursorPos, BorderLayout.PAGE_END);
        this.setVisible(true);

    }
}
