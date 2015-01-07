/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package ti.saxeith.sym.gui;

import java.awt.BorderLayout;
import java.awt.event.ActionListener;
import javax.swing.JFrame;
import ti.saxeith.sym.dat.Game;

/**
 *
 * @author Marcos
 */
public class MainWindow extends JFrame {

    private final RugPanel rug;
    private final MainWindowBar bar;

    public MainWindow(Game game) {
        this(game, new DeckTexture());
    }

    public MainWindow(Game game, DeckTexture texture) {
        super("Siete y medio");

        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setLayout(new BorderLayout());

        bar = new MainWindowBar();
        setJMenuBar(bar);
        
        rug = new RugPanel(game, texture);
        add(rug, BorderLayout.CENTER);
        
        pack();
        setSize(800, 600);
        setLocationRelativeTo(null);
        refreshWindow();
    }

    public RugPanel getRug() {
        return rug;
    }

    public void refreshWindow() {
        rug.refreshRug();
    }
    
    public void addActionListener(ActionListener a) {
        bar.addActionListener(a);
        rug.addActionListener(a);
        repaint();
    }
}
