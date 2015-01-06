/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package es.uv.eu.photoeditor.view;

import es.uv.eu.photoeditor.controller.*;
import java.awt.*;
import javax.swing.*;

import lombok.Getter;

/**
 *
 * @author alumno
 */
public class SelectPanel extends JPanel {
    @Getter
    private final LineWidthPanel lineWidthPanel;

    @Getter
    private final ColorPanel linePanel;
    
    @Getter
    private final ColorPanel fillPanel;
    
    public SelectPanel() {
        setLayout(new GridBagLayout());
        GridBagConstraints c = new GridBagConstraints();
        c.insets = new Insets(5, 5, 5, 5);
        c.fill = GridBagConstraints.BOTH;
        c.weightx = 1.0;

        lineWidthPanel = new LineWidthPanel();
        lineWidthPanel.setBorder(BorderFactory.createEtchedBorder());
        c.weighty = 0.3;
        add(lineWidthPanel, c);

        linePanel = new ColorPanel("Color de línea");
        linePanel.setActionCommand("color.line");
        linePanel.setBorder(BorderFactory.createEtchedBorder());
        c.gridy = 1;
        c.weighty = 0.35;
        add(linePanel, c);

        fillPanel = new ColorPanel("Color de relleno");
        fillPanel.setActionCommand("color.fill");
        fillPanel.setBorder(BorderFactory.createEtchedBorder());
        c.gridy = 2;
        add(fillPanel, c);
    }

    public void setController(PhotoEditorController controller) {
        linePanel.addActionListener(controller);
        fillPanel.addActionListener(controller);
    }
}
