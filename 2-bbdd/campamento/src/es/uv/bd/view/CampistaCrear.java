package es.uv.bd.view;

import es.uv.bd.model.Campista;
import es.uv.bd.model.CampistaDAO;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.text.SimpleDateFormat;
import java.util.Arrays;
import javax.swing.*;

/**
 *
 * @author diaz
 */
public class CampistaCrear extends JFrame {
    
    /*
    private int id;
    private String nombre;
    private String apellidos;
    private int dni;
    private String direccion;
    private int sip;
    private Date fechaNacimiento;
    private List<String> telefonos;
    */
    
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
    
    private final JTable campistaTable;
        
    public CampistaCrear(JTable campistaTable) {
        super("Nuevo campista");

        this.campistaTable = campistaTable;

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
    }
   
    private JPanel createCabecera() {
        JPanel c = new JPanel();
        JLabel l = new JLabel("Dar de alta campista");
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

        nombre.setFont(textfFont);
        nombre.setColumns(30);
        apellidos.setFont(textfFont);
        apellidos.setColumns(30);

        JLabel idLabel = new JLabel("ID:");
        idLabel.setFont(labelFont);
        idLabel.setHorizontalAlignment(JLabel.RIGHT);
        form.add(idLabel);
        form.add(id);

        JLabel nombreLabel = new JLabel("Nombre:");
        nombreLabel.setFont(labelFont);
        nombreLabel.setHorizontalAlignment(JLabel.RIGHT);
        form.add(nombreLabel);
        form.add(nombre);

        JLabel apellidosLabel = new JLabel("Apellidos:");
        apellidosLabel.setFont(labelFont);
        apellidosLabel.setHorizontalAlignment(JLabel.RIGHT);
        form.add(apellidosLabel);
        form.add(apellidos);

        JLabel nifLabel = new JLabel("NIF:");
        nifLabel.setFont(labelFont);
        nifLabel.setHorizontalAlignment(JLabel.RIGHT);
        form.add(nifLabel);
        form.add(nif);

        JLabel direccionLabel = new JLabel("Dirección:");
        direccionLabel.setFont(labelFont);
        direccionLabel.setHorizontalAlignment(JLabel.RIGHT);
        form.add(direccionLabel);
        form.add(direccion);
        
        JLabel sipLabel = new JLabel("SIP:");
        sipLabel.setFont(labelFont);
        sipLabel.setHorizontalAlignment(JLabel.RIGHT);
        form.add(sipLabel);
        form.add(sip);

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
        fechaPanel.add(new JLabel("-"));
        fechaPanel.add(mes);
        fechaPanel.add(new JLabel("-"));
        fechaPanel.add(anyo);

        form.add(fechaPanel);

        JLabel tel1Label = new JLabel("Teléfono 1:");
        tel1Label.setFont(labelFont);
        tel1Label.setHorizontalAlignment(JLabel.RIGHT);
        form.add(tel1Label);
        form.add(tel1);
        
        JLabel tel2Label = new JLabel("Teléfono 2:");
        tel2Label.setFont(labelFont);
        tel2Label.setHorizontalAlignment(JLabel.RIGHT);
        form.add(tel2Label);
        form.add(tel2);
        
        JLabel tel3Label = new JLabel("Teléfono 3:");
        tel3Label.setFont(labelFont);
        tel3Label.setHorizontalAlignment(JLabel.RIGHT);
        form.add(tel3Label);
        form.add(tel3);
        
        return form;
    }

    private JPanel createButton() {
        
        JPanel botonPanel = new JPanel();
        
        JButton boton = new JButton("Añadir");
        boton.setActionCommand("botonCampista");
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
                    case "botonCampista":
                        SimpleDateFormat sdf = new SimpleDateFormat("dd-MM-yyyy");
                        Campista campista = new Campista();
                        campista.setId(id.getText().length() > 0 ? Integer.parseInt(id.getText()) : 0);
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

                        CampistaDAO campistaDao = new CampistaDAO();
                        campistaDao.crearCampista(campista);
                        /*
                         * Actualizamos el modelo
                         */
                        campistaTable.setModel(campistaDao.getTabla());
                        campistaTable.updateUI();
                         /*
                         * Cerramos la ventana
                         */
                        dispose();
                        break;
                    default:
                        System.out.println("CampistaCrear: Accion '" + key + "' no reconocida.");
                        break;
                }
            }
            catch (Exception e) {
                JOptionPane.showMessageDialog(
                null,
                "Error creando campista: " + e.getMessage(),
                "Atención",
                JOptionPane.ERROR_MESSAGE);
            }
        }
    }
}
