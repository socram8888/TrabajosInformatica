package es.uv.eu.calculadora.vista;

import java.awt.*;
import javax.swing.*;

/**
 *
 * @author
 */
public class PantallaPanel extends JPanel {
    private final JLabel result;
    private final JLabel operation;

    public PantallaPanel() {
        setBorder(BorderFactory.createLineBorder(Color.BLACK, 10));
        setBackground(new Color(0xB4AA69));
        setLayout(new BorderLayout());

        result = new JLabel("0", SwingConstants.RIGHT);
        result.setFont(new Font(Font.SERIF, Font.BOLD, 48));
        add(result, BorderLayout.CENTER);

        operation = new JLabel("0", SwingConstants.LEFT);
        operation.setFont(new Font(Font.SERIF, Font.PLAIN, 20));
        add(operation, BorderLayout.SOUTH);
    }

    public void setResult(String resultText) {
        result.setText(resultText);
    }

    public void setOperation(String opText) {
        operation.setText(opText);
    }
}
