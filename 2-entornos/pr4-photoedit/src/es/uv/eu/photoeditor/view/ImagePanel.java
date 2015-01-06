/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package es.uv.eu.photoeditor.view;

import java.awt.Image;
import javax.swing.*;

import lombok.Getter;

/**
 *
 * @author alumno
 */
public class ImagePanel extends JPanel {
    @Getter
    private final JLabel label;

    public ImagePanel() {
        label = new JLabel(new ImageIcon());
        add(label);
    }

    public Image getImage() {
        return ((ImageIcon) label.getIcon()).getImage();
    }

    public void setImage(Image image) {
        ImageIcon icon = new ImageIcon(image);
        label.setIcon(icon);
    }
}
