/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package universidad.model;

import java.io.File;
import java.io.FileInputStream;
import com.thoughtworks.xstream.XStream;
import com.thoughtworks.xstream.io.xml.DomDriver;
import java.io.FileWriter;
import java.io.IOException;
import java.util.Timer;
import java.util.TimerTask;

/**
 *
 * @author Marcos
 */
public class GestorUniversidad {
    private final XStream xstream;
    private Universidad universidad;
    private static final String XML_BACKUP = "build/universidad.xml";

    public GestorUniversidad(int tiempoBackup) {
        xstream = new XStream(new DomDriver());
        xstream.alias("universidad", Universidad.class);
        xstream.alias("alumno", Alumno.class);
        xstream.alias("profesor", Profesor.class);
        xstream.alias("administrador", Administrador.class);
        xstream.alias("subgrupo", Subgrupo.class);
        xstream.alias("horario", FranjaHoraria.class);
        xstream.alias("laboratorio", Laboratorio.class);
        xstream.alias("teoria", Teoria.class);
        xstream.alias("titulacion", Titulacion.class);
        xstream.omitField(Universidad.class, "gestorUniversidad");

        // Para el resto de veces cargar de fichero
        try {
            FileInputStream file_input_xml = new FileInputStream(new File(XML_BACKUP));
            universidad = (Universidad) xstream.fromXML(file_input_xml);
            if (universidad == null) {
                System.err.println("ERROR no se encuentra universidad");
                System.exit(-1);
            }
        } catch (Exception e) {
            //Se realiza la primera vez para tener un ejemplo de bibloteca en XML
            universidad = new Universidad();
            universidad.cargarDatos();
            realizarBackup();
        }
        universidad.setGestorUniversidad(this);

        programarBackup(tiempoBackup);
    }
    
    public void programarBackup(int tiempoBackup) {
        Timer timer = new Timer();
        timer.schedule(new TimerTask() {
            @Override
            public void run() {
                GestorUniversidad.this.realizarBackup();
            }
        }, tiempoBackup, tiempoBackup);
    }
    
    public void realizarBackup() {
        String xml = xstream.toXML(universidad);
        try {
            FileWriter file_output_xml = new FileWriter(new File(XML_BACKUP));
            file_output_xml.write("<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n");
            file_output_xml.write(xml);
            file_output_xml.close();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
    
    public Universidad getUniversidad() {
        return universidad;
    }
}
