package es.uv.eu.photoeditor;

import es.uv.eu.photoeditor.model.PhotoEditorModel;
import es.uv.eu.photoeditor.view.PhotoEditorView;

/**
 *
 * @author Entornos de Usuario (2013)
 */
public class PhotoEditor {

    /**
     * @param args the command line arguments
     */
    public static void main(String[] args) {
        PhotoEditorModel model = new PhotoEditorModel();
        PhotoEditorView view = new PhotoEditorView();
        PhotoEditorController controlador = new PhotoEditorController(model, view);
    }
}
