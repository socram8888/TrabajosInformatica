/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package es.uv.bd.view;

import es.uv.bd.model.Campista;
import es.uv.bd.model.CampistaDAO;
import java.sql.SQLException;
import java.text.ParseException;
import javax.swing.JOptionPane;
import javax.swing.JTable;

/**
 *
 * @author diaz
 */
public class CampistaBorrar {
    
    public CampistaBorrar(int id, JTable mascotaTable) {
    
        CampistaDAO mascotaDao = new CampistaDAO();
        Campista campista;

        try {
            // Recuperamos la campista a través de la clave primaria
            campista = mascotaDao.leerCampista(id);
        
            // Dialogo de confirmación
            int reply = JOptionPane.showConfirmDialog(
                null,
                "¿Borrar al campista '" + campista.getNombre() + " " + campista.getApellidos() + " (id = " + id + ")?",
                "Borrar Campista",
                JOptionPane.YES_NO_OPTION);

            if (reply == JOptionPane.YES_OPTION) {
                    // Borramos la campista de la base de datos
                    mascotaDao.borrarCampista(id);
                    /*
                    * Actualizamos el modelo
                    */
                    mascotaTable.setModel(mascotaDao.getTabla());
                    mascotaTable.updateUI();
                }
        } catch (ClassNotFoundException | InstantiationException | IllegalAccessException | SQLException | ParseException e) {
            JOptionPane.showMessageDialog(
                null,
                "Error borrando mascota: " + e.getMessage(),
                "Atención",
                JOptionPane.ERROR_MESSAGE);
        }
    }
}
