/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package es.uv.bd.view;

import es.uv.bd.model.Campista;
import es.uv.bd.model.CampistaDAO;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.sql.SQLException;
import java.text.ParseException;
import java.text.SimpleDateFormat;
import java.util.Arrays;
import java.util.Calendar;
import javax.swing.*;

/**
 *
 * @author diaz
 */
public class CampistaEditar extends JFrame {

    private final JTextField id = new JTextField();
    private final JTextField nombre = new JTextField();
    private final JTextField apellidos = new JTextField();
    private final JTextField nif = new JTextField();
    private final JTextArea direccion = new JTextArea();
    private final JTextField sip = new JTextField();
    private final JComboBox dia = new JComboBox();
    private final JComboBox mes = new JComboBox();
    private final JComboBox anyo = new JComboBox();
    private final JTextField tel1 = new JTextField();
    private final JTextField tel2 = new JTextField();
    private final JTextField tel3 = new JTextField();
    
    private JTable mascotaTable;
    private CampistaDAO mascotaDao = new CampistaDAO();
    private Campista campista;

    public CampistaEditar(int idMascota, JTable mascotaTable) {
        
        super("Editar campista");
        this.mascotaTable = mascotaTable;
        
        try {
            /*
             * Obtenemos el objeto a editar
             */
            campista = mascotaDao.leerCampista(idMascota);
            
            Container cp = this.getContentPane();
            cp.setLayout(new BorderLayout());
            
            /* Cabecera */
            JPanel cabecera = createCabecera();
      
            /* Formulario */
            JPanel form = createForm();
            
            /* Botón */
            JPanel boton = createButton();

            /* Añadimos todos los paneles al Container */
            cp.add(cabecera, BorderLayout.NORTH);
            cp.add(form, BorderLayout.CENTER);
            cp.add(boton, BorderLayout.SOUTH);
            
            setSize(600,400);
            pack();
            setVisible(true);
        } catch (ClassNotFoundException | InstantiationException | IllegalAccessException | SQLException | ParseException e) {
            JOptionPane.showMessageDialog(
                null,
                "Error modificiando campista: " + e.getMessage(),
                "Atención",
                JOptionPane.ERROR_MESSAGE);
        }
    }
   
    private JPanel createCabecera() {
        JPanel c = new JPanel();
        JLabel l = new JLabel("Editar campista");
        l.setForeground(Color.BLUE);
        l.setHorizontalAlignment(JLabel.CENTER);
        l.setFont(new Font("Arial",Font.BOLD | Font.ITALIC,22));
        c.add(l);
        
        return c;
    }
    
    private JPanel createForm() {
        JPanel form = new JPanel();
        Font labelFont = new Font("Arial", Font.BOLD, 12);
        Font textfFont = new Font("Arial", Font.PLAIN, 12);

        form.setLayout(new GridLayout(10, 2));

        id.setFont(textfFont);
        id.setColumns(4);
        id.setEnabled(false);

        nombre.setFont(textfFont);
        nombre.setColumns(30);
        apellidos.setFont(textfFont);
        apellidos.setColumns(30);

        JLabel idLabel = new JLabel("ID:");
        idLabel.setFont(labelFont);
        idLabel.setHorizontalAlignment(JLabel.RIGHT);
        form.add(idLabel);
        form.add(id);
        id.setText(Integer.toString(campista.getId()));

        JLabel nombreLabel = new JLabel("Nombre:");
        nombreLabel.setFont(labelFont);
        nombreLabel.setHorizontalAlignment(JLabel.RIGHT);
        form.add(nombreLabel);
        form.add(nombre);
        nombre.setText(campista.getNombre());

        JLabel apellidosLabel = new JLabel("Apellidos:");
        apellidosLabel.setFont(labelFont);
        apellidosLabel.setHorizontalAlignment(JLabel.RIGHT);
        form.add(apellidosLabel);
        form.add(apellidos);
        apellidos.setText(campista.getApellidos());

        JLabel nifLabel = new JLabel("NIF:");
        nifLabel.setFont(labelFont);
        nifLabel.setHorizontalAlignment(JLabel.RIGHT);
        form.add(nifLabel);
        form.add(nif);
        nif.setText(campista.getNif());

        JLabel direccionLabel = new JLabel("Dirección:");
        direccionLabel.setFont(labelFont);
        direccionLabel.setHorizontalAlignment(JLabel.RIGHT);
        form.add(direccionLabel);
        form.add(direccion);
        direccion.setText(campista.getDireccion());
        
        JLabel sipLabel = new JLabel("SIP:");
        sipLabel.setFont(labelFont);
        sipLabel.setHorizontalAlignment(JLabel.RIGHT);
        form.add(sipLabel);
        form.add(sip);
        sip.setText(Integer.toString(campista.getSip()));

        JLabel fechaNacimientoLabel = new JLabel("Fecha de nacimiento:");
        fechaNacimientoLabel.setFont(labelFont);
        fechaNacimientoLabel.setHorizontalAlignment(JLabel.RIGHT);
        form.add(fechaNacimientoLabel);

        JPanel fechaPanel = new JPanel();
        fechaPanel.setLayout(new FlowLayout());

        dia.setModel(new DefaultComboBoxModel(new String[]{"01", "02", "03", "04", "05", "06", "07", "08", "09", "10",
            "11", "12", "13", "14", "15", "16", "17", "18", "19", "20",
            "21", "22", "23", "24", "25", "26", "27", "28", "29", "30", "31"}));
        mes.setModel(new DefaultComboBoxModel(new String[]{"01", "02", "03", "04", "05", "06", "07", "08", "09", "10",
            "11", "12"}));
        anyo.setModel(new DefaultComboBoxModel(new String[]{"1990", "1991", "1992", "1993", "1994", "1995", "1996",
            "1997", "1998", "1999", "2000", "2001", "2002", "2003", "2004", "2005", "2006", "2007", "2008", "2009", "2010",
            "2011", "2012"}));

        fechaPanel.add(dia);
        Calendar clnd = Calendar.getInstance();
        clnd.setTime(campista.getFechaNacimiento());
        dia.setSelectedIndex(clnd.get(Calendar.DAY_OF_MONTH));
        fechaPanel.add(new JLabel("-"));
        fechaPanel.add(mes);
        mes.setSelectedIndex(clnd.get(Calendar.MONTH));
        fechaPanel.add(new JLabel("-"));
        fechaPanel.add(anyo);
        anyo.setSelectedIndex(clnd.get(Calendar.YEAR) - 1990);

        form.add(fechaPanel);

        JLabel tel1Label = new JLabel("Teléfono 1:");
        tel1Label.setFont(labelFont);
        tel1Label.setHorizontalAlignment(JLabel.RIGHT);
        form.add(tel1Label);
        form.add(tel1);
        if (campista.getTelefonos().size() > 0) {
            tel1.setText(campista.getTelefonos().get(0));
        }
        
        JLabel tel2Label = new JLabel("Teléfono 2:");
        tel2Label.setFont(labelFont);
        tel2Label.setHorizontalAlignment(JLabel.RIGHT);
        form.add(tel2Label);
        form.add(tel2);
        if (campista.getTelefonos().size() > 1) {
            tel2.setText(campista.getTelefonos().get(1));
        }
        
        JLabel tel3Label = new JLabel("Teléfono 3:");
        tel3Label.setFont(labelFont);
        tel3Label.setHorizontalAlignment(JLabel.RIGHT);
        form.add(tel3Label);
        form.add(tel3);
        if (campista.getTelefonos().size() > 2) {
            tel3.setText(campista.getTelefonos().get(2));
        }
        
        return form;
    }

    private JPanel createButton() {
        
        JPanel botonPanel = new JPanel();
        
        JButton boton = new JButton("Modificar");
        boton.setActionCommand("botonMascota");
        boton.addActionListener(new ButtonListener());
        botonPanel.add(boton);
        return botonPanel;
    }
    
    private class ButtonListener implements ActionListener {
        @Override
        public void actionPerformed(ActionEvent event) {
            try {
                String key = event.getActionCommand();
                switch (key) {
                    case "botonMascota":
                        SimpleDateFormat sdf = new SimpleDateFormat("dd-MM-yyyy");
                        campista.setNombre(nombre.getText());
                        campista.setApellidos(apellidos.getText());
                        campista.setNif(nif.getText());
                        campista.setDireccion(direccion.getText());
                        campista.setSip(sip.getText().length() > 0 ? Integer.parseInt(sip.getText()) : 0);
                        String f = (String)dia.getSelectedItem() + "-" + 
                            (String)mes.getSelectedItem() + "-" +
                            (String)anyo.getSelectedItem();
                        campista.setFechaNacimiento(sdf.parse(f));
                        campista.setTelefonos(Arrays.asList(tel1.getText(), tel2.getText(), tel3.getText()));

                        CampistaDAO mascotaDao = new CampistaDAO();
                        mascotaDao.actualizarCampista(campista);
                        /*
                         * Actualizamos el modelo
                         */
                        mascotaTable.setModel(mascotaDao.getTabla());
                        mascotaTable.updateUI();
                        /*
                         * Cerramos la ventana
                         */
                        dispose();
                        break;
                    default:
                        System.out.println("MascotaCrear: Accion '" + key + "' no reconocida.");
                        break;
                }
            }
            catch (ClassNotFoundException | InstantiationException | IllegalAccessException | SQLException | ParseException e) {
                JOptionPane.showMessageDialog(
                null,
                "Error modificiando mascota: " + e.getMessage(),
                "Atención",
                JOptionPane.ERROR_MESSAGE);
            }
        }
    }
}
