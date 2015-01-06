package es.uv.eu.calculadora.controlador;

import es.uv.eu.calculadora.modelo.CalculadoraModelo;
import es.uv.eu.calculadora.vista.CalculadoraVista;
import es.uv.eu.calculadora.vista.PantallaPanel;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.WindowAdapter;
import java.awt.event.WindowEvent;

/**
 *
 * @author Marcos Vives Del Sol
 */
public class CalculadoraControlador implements ActionListener {
    private final CalculadoraModelo model;
    private final CalculadoraVista view;

    public CalculadoraControlador(CalculadoraModelo model, CalculadoraVista view) {
        this.model = model;
        this.view = view;

        view.setActionListener(this);
        view.setVisible(true);

        view.addWindowListener(new WindowAdapter() {
            @Override
            public void windowClosing(WindowEvent e) {
                System.exit(0);
            }
        });
    }

    @Override
    public void actionPerformed(ActionEvent event) {
        String blocks[] = event.getActionCommand().split("_");

        switch (blocks[0]) {
            case "num":
                switch (blocks[1]) {
                    case ".":
                        model.addPoint();
                        break;
                        
                    case "C":
                        model.deleteChar();
                        break;
                        
                    default:
                        model.addDigit(blocks[1]);
                }
                break;

            case "op":
                model.calc(blocks[1]);
                break;
                
            case "func":
                model.reset();
                break;

            case "salir":
                System.exit(0);
        }

        PantallaPanel scr = view.getPantalla();
        scr.setResult(model.getValor());
        scr.setOperation(model.getStatus());
    }
}
