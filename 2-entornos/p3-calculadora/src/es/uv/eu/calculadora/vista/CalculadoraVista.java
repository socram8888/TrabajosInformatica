package es.uv.eu.calculadora.vista;

import java.awt.*;
import java.awt.event.ActionListener;
import javax.swing.*;

public class CalculadoraVista extends JFrame {
    public static final Color BACKGROUND = new Color(210, 210, 240);

    private final CalculadoraMenu calculadoraMenu;
    private final PantallaPanel pantallaPanel;
    private final NumerosPanel numerosPanel;
    private final OperacionesPanel operacionesPanel;
    private final FuncionPanel funcionPanel;
    
    public CalculadoraVista() {
       super("Calculadora");

       setLayout(new GridBagLayout());
       setSize(420, 420);

       GridBagConstraints c = new GridBagConstraints();
       c.fill = GridBagConstraints.BOTH;
       c.insets = new Insets(5, 5, 5, 5);

       calculadoraMenu = new CalculadoraMenu();
       setJMenuBar(calculadoraMenu);
       
       c.gridwidth = 2;
       c.gridx = 0;
       c.gridy = 0;
       c.weighty = 0.4;
       pantallaPanel = new PantallaPanel();
       add(pantallaPanel, c);

       c.gridwidth = 1;
       c.gridx = 0;
       c.gridy = 1;
       c.weightx = 0.75;
       c.weighty = 0.5;
       numerosPanel = new NumerosPanel();
       add(numerosPanel, c);

       c.gridx = 1;
       c.gridy = 1;
       c.weightx = 0.25;
       operacionesPanel = new OperacionesPanel();
       add(operacionesPanel, c);

       c.gridx = 0;
       c.gridy = 2;
       c.gridwidth = 2;
       c.weighty = 0.1;
       c.weightx = 0;
       funcionPanel = new FuncionPanel();
       add(funcionPanel, c);
    }

    public void setActionListener(ActionListener listener) {
        calculadoraMenu.setActionListener(listener);
        numerosPanel.setActionListener(listener);
        operacionesPanel.setActionListener(listener);
        funcionPanel.setActionListener(listener);
    }

    public PantallaPanel getPantalla() {
        return pantallaPanel;
    }
}
