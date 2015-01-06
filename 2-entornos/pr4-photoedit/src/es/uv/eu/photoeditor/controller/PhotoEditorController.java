/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package es.uv.eu.photoeditor.controller;

import java.awt.event.*;
import es.uv.eu.photoeditor.model.*;
import es.uv.eu.photoeditor.view.*;
import java.awt.Color;
import java.awt.Polygon;
import java.io.File;

/**
 *
 * @author alumno
 */
public class PhotoEditorController implements ActionListener {
    private final PhotoEditorModel model;
    private final PhotoEditorView view;
    private final LoadImage loadImage;
    private final SaveImage saveImage;
    private final Polygon polygon = new Polygon();

    public PhotoEditorController(PhotoEditorModel model, PhotoEditorView view) {
        this.model = model;
        this.view = view;
        view.setController(this);
        view.addWindowListener(new WindowAdapter() {
            @Override
            public void windowClosing(WindowEvent e) {
                System.exit(0);
            }
        });
        view.setVisible(true);
        loadImage = new LoadImage();
        saveImage = new SaveImage();

        view.getImagePanel().setImage(model.getImagen());
        view.getImagePanel().getLabel().addMouseListener(new MouseAdapter() {
            @Override
            public void mouseClicked(MouseEvent e) {
                System.out.println(e);
                polygon.addPoint(e.getX(), e.getY());
                if (e.getButton() != MouseEvent.BUTTON1) {
                    PhotoEditorController.this.model.pintaPoligono(polygon,
                            PhotoEditorController.this.view.getSelectPanel().getLineWidthPanel().getSlider().getValue(),
                            PhotoEditorController.this.view.getSelectPanel().getLinePanel().getSelectedColor().getColor(),
                            PhotoEditorController.this.view.getSelectPanel().getFillPanel().getSelectedColor().getColor());
                    PhotoEditorController.this.view.getImagePanel().setImage(PhotoEditorController.this.model.getImagen());
                    polygon.reset();
                }
            }
        });
    }

    @Override
    public void actionPerformed(ActionEvent event) {
        File file;
        String cmd = event.getActionCommand();
        System.out.println(cmd);
        switch (cmd) {
            case "color.fill":
                view.getStatusPanel().getFillColor().setBackground(view.getSelectPanel().getFillPanel().getSelectedColor().getColor());
                break;
                        
            case "color.line":
                view.getStatusPanel().getLineColor().setBackground(view.getSelectPanel().getLinePanel().getSelectedColor().getColor());
                break;

            case "file.load":
                file = loadImage.getFile();
                if (file != null) {
                    model.loadImagen(file);
                    view.getImagePanel().setImage(model.getImagen());
                }
                break;

            case "file.save":
                file = saveImage.getFile();
                model.saveImagen(file);
                break;

            case "file.exit":
                System.exit(0);
                break;
        }
    }
}
