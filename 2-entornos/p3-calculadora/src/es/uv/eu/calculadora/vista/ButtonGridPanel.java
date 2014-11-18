package es.uv.eu.calculadora.vista;

import java.awt.Color;
import java.awt.GridLayout;
import java.awt.event.ActionListener;
import java.util.ArrayList;
import java.util.List;
import javax.swing.JButton;
import javax.swing.JPanel;

/**
 *
 * @author
 */
class ButtonGridPanel extends JPanel {
    protected final List<JButton> buttons = new ArrayList<>();

    public ButtonGridPanel(String prefix, String[] buttons, int width, int height) {
        super(new GridLayout(height, width, 5, 5));
        for (String button : buttons) {
            addButton(prefix, button);
        }
    }

    public ButtonGridPanel(String prefix, String buttons, int width, int height) {
        super(new GridLayout(height, width, 5, 5));
        for (int i = 0; i < buttons.length(); i++) {
            addButton(prefix, buttons.substring(i, i + 1));
        }
    }

    private void addButton(String prefix, String text) {
        JButton button = new JButton(text);
        button.setActionCommand(prefix + "_" + text);
        add(button);
        buttons.add(button);
    }

    public void setSpecial(int i) {
        buttons.get(i).setForeground(Color.BLUE);
    }

    public void setActionListener(ActionListener listener) {
        for (JButton button : buttons) {
            button.addActionListener(listener);
        }
    }
}
