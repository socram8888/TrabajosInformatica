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
public class StatusPanel extends JPanel {
    @Getter
    private final JLabel lineWidth;
    
    @Getter
    private final JTextField lineColor;
    
    @Getter
    private final JTextField fillColor;

    public StatusPanel() {
        super(new GridLayout(1, 3));

        JPanel panel;

        panel = new JPanel();
        panel.add(new JLabel("Grosor de línea"));
        lineWidth = new JLabel("X");
        lineWidth.setBorder(BorderFactory.createEtchedBorder());
        panel.add(lineWidth);
        add(panel);

        panel = new JPanel();
        panel.add(new JLabel("Color de línea"));
        lineColor = new JTextField(5);
        lineColor.setEnabled(false);
        panel.add(lineColor);
        add(panel);

        panel = new JPanel();
        panel.add(new JLabel("Color de relleno"));
        fillColor = new JTextField(5);
        fillColor.setEnabled(false);
        panel.add(fillColor);
        add(panel);
    }
}
