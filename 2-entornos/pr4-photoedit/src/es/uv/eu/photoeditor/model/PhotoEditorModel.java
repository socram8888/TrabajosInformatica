package es.uv.eu.photoeditor.model;

import java.awt.BasicStroke;
import java.awt.Color;
import java.awt.Graphics2D;
import java.awt.Polygon;
import java.awt.image.BufferedImage;
import java.io.File;
import java.io.IOException;
import javax.imageio.ImageIO;

/**
 *
 * @author diaz
 */
public class PhotoEditorModel {
    private BufferedImage imagen;
    private String imagenFileName = "";

    public PhotoEditorModel() {
        try {
            imagenFileName = "imagenes/imagen_00.jpg";
            imagen = ImageIO.read(new File(imagenFileName));
        }
        catch (IOException e) {
            System.out.println("Problemas leyendo la imagen '" + this.imagenFileName + "'.");
            System.out.println("Motivo: " + e.getLocalizedMessage());
        }
    }

    public BufferedImage getImagen() {
        return imagen;
    }

    public String getImagenFileName() {
        return imagenFileName;
    }

    public void loadImagen(File imagenFile) {
        if (imagenFile != null) {
            this.imagenFileName = imagenFile.getName();
            try {
                imagen = ImageIO.read(imagenFile);
            }
            catch (IOException e) {
                System.out.println("Problemas leyendo la imagen '" + this.imagenFileName + "'.");
                System.out.println("Motivo: " + e.getLocalizedMessage());
            }
        }
    }

    public void saveImagen(File imagenFile) {
        if (imagenFile != null) {
            try {
                this.imagenFileName = imagenFile.getName();
                ImageIO.write(imagen,"jpg",imagenFile);
            } 
            catch (IOException e) {
                System.out.println("Problemas guardando la imagen '" + imagenFile.getName() + "'.");
                System.out.println("Motivo: " + e.getLocalizedMessage());
            }
        }
    }
    
    public void pintaPoligono(Polygon poly, int penWidth, Color penColor, Color fillColor) {
        Graphics2D gr = (Graphics2D)imagen.getGraphics();
        gr.setColor(fillColor);
        gr.fillPolygon(poly);
        gr.setColor(penColor);
        gr.setStroke(new BasicStroke(penWidth));
        gr.drawPolygon(poly);
    }
}
