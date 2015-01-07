/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package ti.saxeith.sym.gui;

import java.awt.Font;
import java.awt.GridLayout;
import java.awt.event.ActionListener;
import javax.swing.JButton;
import javax.swing.JFrame;

/**
 *
 * @author Marcos
 */
public class NewGameWindow extends JFrame {
    private static final Font BUTTON_FONT = new Font(Font.SANS_SERIF, Font.PLAIN, 32);
    
    private final JButton onePlayerButton;
    private final JButton twoPlayerButton;

    public NewGameWindow() {
        super("Siete y medio - nueva partida");

        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setLayout(new GridLayout(2, 1, 10, 10));

        onePlayerButton = new JButton("Un jugador");
        onePlayerButton.setFont(BUTTON_FONT);
        onePlayerButton.setActionCommand("newgame.1");
        add(onePlayerButton);

        twoPlayerButton = new JButton("Dos jugadores");
        twoPlayerButton.setFont(BUTTON_FONT);
        twoPlayerButton.setActionCommand("newgame.2");
        add(twoPlayerButton);

        pack();
        setSize(400, 400);
        setLocationRelativeTo(null);
    }

    public void addActionListener(ActionListener c) {
        onePlayerButton.addActionListener(c);
        twoPlayerButton.addActionListener(c);
    }
}
