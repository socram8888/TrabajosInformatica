/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package es.uv.bd.view;

import es.uv.bd.model.CampistaDAO;
import java.awt.BorderLayout;
import java.awt.Color;
import java.awt.Container;
import java.awt.Font;
import javax.swing.*;
import javax.swing.table.JTableHeader;

    
/**
 *
 * @author diaz
 */
public class CampistaView extends JFrame {

    private JTable campistaTable;
    private JPanel campistaBotones;
    
    private CampistaDAO campistaDao = new CampistaDAO();
    
    public CampistaView() {
        super("Gestión de Campistas");
        
        Container cp = this.getContentPane();
        cp.setLayout(new BorderLayout());
        
        /* Cabecera */
        JPanel cabecera = createCabecera();
  
        /* Tabla */
        campistaTable = createTablePanel();
        campistaTable.setModel(campistaDao.getTabla());
        // Ponemos la tabla dentro de un JScrollPane
        JScrollPane jsp = new JScrollPane(campistaTable);

        /* Botonera */
        campistaBotones = new CampistaBotones(campistaTable);
        
        /* Añadimos todos los paneles al Container */
        cp.add(cabecera, BorderLayout.NORTH);
        cp.add(jsp, BorderLayout.CENTER);
        cp.add(campistaBotones, BorderLayout.SOUTH);
        
        setSize(800,400);
        setVisible(true);
    }
   
    private JPanel createCabecera() {
        JPanel c = new JPanel();
        JLabel l = new JLabel("Lista de Campistas");
        l.setForeground(Color.RED);
        l.setHorizontalAlignment(JLabel.CENTER);
        l.setFont(new Font("Arial",Font.BOLD | Font.ITALIC,24));
        c.add(l);
        
        return c;
    }
 
    private JTable createTablePanel() {
        
        JTable tp = new JTable();
        /*
         * Cabecera de la tabla
         */
        JTableHeader th = tp.getTableHeader();
        th.setFont(new Font("Arial",Font.BOLD | Font.ITALIC,14));
        th.setBackground(Color.DARK_GRAY);
        th.setForeground(Color.WHITE);
        
        /*
         * Caracteristicas de la tabla
         */
        tp.setAutoResizeMode(JTable.AUTO_RESIZE_ALL_COLUMNS);
        tp.setFont(new Font("Arial",Font.BOLD,12));
        tp.setRowHeight(22);
        
        return tp;
    }
}
