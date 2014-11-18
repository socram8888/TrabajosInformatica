/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package es.uv.eu.calculadora.vista;

import java.awt.event.ActionListener;
import javax.swing.JMenu;
import javax.swing.JMenuBar;
import javax.swing.JMenuItem;

/**
 *
 * @author Marcos Vives Del Sol
 */
public class CalculadoraMenu extends JMenuBar {
    private final JMenu calculadora;
    private final JMenuItem salir;
    
    public CalculadoraMenu(){
        calculadora = new JMenu("Archivo");
        salir = new JMenuItem("salir");
        calculadora.add(salir);
        
        this.add(calculadora);
    }
    
    public void setActionListener(ActionListener actionListener) {
        salir.addActionListener(actionListener);
    }
}
