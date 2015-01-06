/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package es.uv.eu.photoeditor.view;

import java.awt.*;
import java.awt.event.*;
import javax.swing.*;
import es.uv.eu.photoeditor.ColorTools;
import es.uv.eu.photoeditor.NamedColor;
import java.util.LinkedList;
import java.util.List;

import lombok.Getter;
import lombok.Setter;

/**
 *
 * @author alumno
 */
public class ColorPanel extends JPanel {
    private static final NamedColor[] DEFAULT_COLORS = new NamedColor[] {
        new NamedColor(Color.BLACK, "Negro"),
        new NamedColor(Color.CYAN, "Cian"),
        new NamedColor(Color.DARK_GRAY, "Gris oscuro"),
        new NamedColor(Color.GRAY, "Gris"),
        new NamedColor(Color.LIGHT_GRAY, "Gris claro"),
        new NamedColor(Color.MAGENTA, "Magenta"),
        new NamedColor(Color.ORANGE, "Naranja"),
        new NamedColor(Color.PINK, "Rosa"),
        new NamedColor(Color.YELLOW, "Amarillo"),
        new NamedColor(Color.WHITE, "Blanco"),
        new NamedColor(Color.RED, "Rojo"),
        new NamedColor(Color.BLUE, "Azul"),
        new NamedColor(Color.GREEN, "Verde"),
    };

    private final NamedColor[] colors;
    private final JButton[] buttons;
    private final List<ActionListener> listeners = new LinkedList<>();

    @Getter @Setter
    private String actionCommand = "changecolor";
    private int selectedColor = 0;

    public ColorPanel(String what) {
        this(what, DEFAULT_COLORS);
    }

    public ColorPanel(String what, NamedColor[] colors) {
        this(what, DEFAULT_COLORS, 0);
    }

    public ColorPanel(String what, NamedColor[] colors, int selectedColor) {
        if (selectedColor < 0 && selectedColor >= colors.length) {
            selectedColor = 0;
        }

        this.colors = colors;
        this.selectedColor = selectedColor;

        setLayout(new GridLayout((colors.length + 2) / 2, 2, 5, 5));
        add(new JLabel(what));

        ActionListener selectionHandler = new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent event) {
                ColorPanel.this.buttons[ColorPanel.this.selectedColor].setEnabled(true);
                ColorPanel.this.selectedColor = Integer.parseInt(event.getActionCommand());
                ColorPanel.this.buttons[ColorPanel.this.selectedColor].setEnabled(false);
                ActionEvent childEvent = new ActionEvent(this, ActionEvent.ACTION_PERFORMED, actionCommand);
                for (ActionListener listener : ColorPanel.this.listeners) {
                    listener.actionPerformed(childEvent);
                }
            }
	};

        buttons = new JButton[colors.length];
        for (int i = 0; i < colors.length; i++) {
            buttons[i] = new JButton(colors[i].getName());
            buttons[i].setBackground(colors[i].getColor());
            buttons[i].setForeground(ColorTools.getReadableColor(colors[i].getColor()));
            buttons[i].setActionCommand(Integer.toString(i));
            buttons[i].addActionListener(selectionHandler);
            add(buttons[i]);
        }

        buttons[selectedColor].setEnabled(false);
    }

    public NamedColor getSelectedColor() {
        return colors[selectedColor];
    }

    public void addActionListener(ActionListener listener) {
        listeners.add(listener);
    }
}
