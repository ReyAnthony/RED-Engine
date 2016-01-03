package fr.anthonyrey.rednoz.mapeditor.model;

import java.awt.image.BufferedImage;

/**
 * Created by anthonyrey on 03/01/2016.
 */
public class AssocData {

    private BufferedImage image;
    private char value;


    public AssocData(BufferedImage image, char value) {
        this.image = image;
        this.value = value;
    }

    public BufferedImage getImage() {
        return image;
    }

    public char getValue() {
        return value;
    }
}
