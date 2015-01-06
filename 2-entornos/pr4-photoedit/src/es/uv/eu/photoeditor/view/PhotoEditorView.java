/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package es.uv.eu.photoeditor.view;

import es.uv.eu.photoeditor.controller.PhotoEditorController;
import java.awt.*;
import javax.swing.*;

import lombok.Getter;

/**
 *
 * @author alumno
 */
public class PhotoEditorView extends JFrame {
    @Getter
    private final SelectPanel selectPanel;

    @Getter
    private final StatusPanel statusPanel;

    @Getter
    private final ImagePanel imagePanel;

    private final PhotoEditorMenuBar menu;

    public PhotoEditorView() {
        super("Editor de fotos");
        setSize(500, 200);

        setLayout(new GridBagLayout());
        GridBagConstraints c = new GridBagConstraints();
        c.insets = new Insets(5, 5, 5, 5);
        c.fill = GridBagConstraints.BOTH;

        selectPanel = new SelectPanel();
        c.weighty = 0.95;
        c.weightx = 0.1;
        add(selectPanel, c);

        imagePanel = new ImagePanel();
        c.gridx = 1;
        c.weightx = 0.9;
        add(imagePanel, c);

        statusPanel = new StatusPanel();
        c.gridx = 0;
        c.gridy = 1;
        c.weighty = 0.05;
        c.gridwidth = 2;
        add(statusPanel, c);

        menu = new PhotoEditorMenuBar();
        setJMenuBar(menu);
    }

    public void setController(PhotoEditorController controller) {
        selectPanel.setController(controller);
        //imagePanel.setController(controller);
        menu.setController(controller);
    }
}
