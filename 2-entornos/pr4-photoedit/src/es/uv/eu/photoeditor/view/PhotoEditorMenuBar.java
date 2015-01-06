/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package es.uv.eu.photoeditor.view;

import javax.swing.*;
import es.uv.eu.photoeditor.controller.PhotoEditorController;


/**
 *
 * @author alumno
 */
public class PhotoEditorMenuBar extends JMenuBar {
	private final JMenuItem load;
	private final JMenuItem save;
	private final JMenuItem exit;

    public PhotoEditorMenuBar() {
        JMenu file = new JMenu("Archivo");

        load = new JMenuItem("Abrir archivo...");
        load.setActionCommand("file.load");
        file.add(load);

        save = new JMenuItem("Guardar archivo...");
        save.setActionCommand("file.save");
        file.add(save);

        exit = new JMenuItem("Salir");
        exit.setActionCommand("file.exit");
        file.add(exit);

        add(file);
    }

    public void setController(PhotoEditorController controller) {
        load.addActionListener(controller);
        save.addActionListener(controller);
        exit.addActionListener(controller);
    }
}
