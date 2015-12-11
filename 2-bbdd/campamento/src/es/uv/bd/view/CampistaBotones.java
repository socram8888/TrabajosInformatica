package es.uv.bd.view;

import es.uv.bd.model.CampistaDAO;
import java.awt.GridLayout;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.sql.SQLException;
import javax.swing.JButton;
import javax.swing.JOptionPane;
import javax.swing.JPanel;
import javax.swing.JTable;
import javax.swing.table.DefaultTableModel;

/**
 *
 * @author diaz
 */
public class CampistaBotones extends JPanel {
    private static JButton[] button = new JButton[3];
    private static String[] buttonName = { "Nuevo campista", "Editar campista", "Borrar campista" };
    private static String[] buttonAction = { "insertar", "editar", "borrar" };
    private JTable mascotaTable;

    public CampistaBotones(JTable mascotaTable) {
    
        this.mascotaTable = mascotaTable;
        MascotaButtonListener mascotaButtonListener = new MascotaButtonListener();
        setLayout(new GridLayout(1,3));
        
        for (int i = 0; i < button.length; i++) {
            button[i] = new JButton(buttonName[i]);
            button[i].setActionCommand(buttonAction[i]);
            button[i].addActionListener(mascotaButtonListener);
            this.add(button[i]);
        }
    }
     
    private class MascotaButtonListener implements ActionListener {
            
        @Override
        public void actionPerformed(ActionEvent event) {
            
            int row, idMascota;
            CampistaDAO mascotaDao = new CampistaDAO();
            
            String key   = event.getActionCommand();
            switch (key) {
                case "insertar":
                    CampistaCrear mascotaCrear = new CampistaCrear(mascotaTable);
                    break;
                case "editar":
                    row = mascotaTable.getSelectedRow();
                    if (row == -1) {
                        showSelectionMessage();
                    }
                    else {
                        idMascota = (int)mascotaTable.getModel().getValueAt(row, 0);
                        CampistaEditar mascotaEditar = new CampistaEditar(idMascota, mascotaTable);
                    }
                    break;
                case "borrar":
                    // Fila seleccionada
                    row = mascotaTable.getSelectedRow();
                    if (row == -1) {
                        showSelectionMessage();
                    }
                    else {
                        idMascota = (int)mascotaTable.getModel().getValueAt(row, 0);
                        CampistaBorrar mascotaBorrar = new CampistaBorrar(idMascota, mascotaTable);
                    }
                    break;
                default:
                    System.out.println("MascotaButtonListener: Accion '" + key + "' no reconocida.");
                    break;
            }
        }
        
        private void showSelectionMessage() {
            JOptionPane.showMessageDialog(
                    null,
                    "Por favor, selecciona una fila de la tabla",
                    "Sin selección",
                    JOptionPane.INFORMATION_MESSAGE);
        }
        
        private void mascotaBorrar(int row) {                        
            CampistaDAO mascotaDao = new CampistaDAO();
        
            // No hay ninguna fila seleccionada
            if (row == -1) {
                JOptionPane.showMessageDialog(
                    null,
                    "Por favor, selecciona una fila de la tabla",
                    "Sin selección",
                    JOptionPane.INFORMATION_MESSAGE);
            }
            else {
                // Clave primaria de la fila seleccionada
                int idMascota = (int)mascotaTable.getModel().getValueAt(row, 0);
                String nombreMascota = (String)mascotaTable.getModel().getValueAt(row, 1);
            
                // Dialogo de confirmación
                int reply = JOptionPane.showConfirmDialog(
                    null,
                    "¿Borrar al campista '" + nombreMascota + "' (idCampista = " + idMascota + ")?",
                    "Borrar Mascota",
                    JOptionPane.YES_NO_OPTION);
                if (reply == JOptionPane.YES_OPTION) {
                    try {
                        // Borramos la mascota de la base de datos
                        mascotaDao.borrarCampista(idMascota);
                        // y actualizamos la tabla
                        DefaultTableModel mascotaModel = (DefaultTableModel)mascotaTable.getModel();
                        mascotaModel.removeRow(row);
                        mascotaTable.updateUI();
                    }
                    catch (Exception e) {
                        JOptionPane.showMessageDialog(
                            null,
                            "Error borrando campista: " + e.getMessage(),
                            "Atención",
                            JOptionPane.ERROR_MESSAGE);
                    }
                }
            }
        }
    }
}
