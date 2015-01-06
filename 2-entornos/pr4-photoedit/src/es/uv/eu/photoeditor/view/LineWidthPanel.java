/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package es.uv.eu.photoeditor.view;

import java.awt.*;
import javax.swing.*;

import lombok.Getter;

/**
 *
 * @author alumno
 */
public class LineWidthPanel extends JPanel {
    @Getter
    private final JSlider slider;

    public LineWidthPanel() {
        setLayout(new BorderLayout());
        slider = new JSlider(1, 10);
        slider.setMajorTickSpacing(1);
        slider.setLabelTable(slider.createStandardLabels(1));
        slider.setPaintTicks(true);
        slider.setPaintLabels(true);
        add(slider, BorderLayout.CENTER);

        add(new JLabel("Grosor de línea"), BorderLayout.NORTH);
    }
}
