/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package ti.saxeith.sym.gui;

import java.awt.event.ActionListener;
import javax.swing.JMenu;
import javax.swing.JMenuBar;
import javax.swing.JMenuItem;

/**
 *
 * @author Marcos
 */
public class MainWindowBar extends JMenuBar {
    private final JMenuItem restart;
    private final JMenuItem newGame;
    private final JMenuItem changeTexture;
    private final JMenuItem resetTexture;
    private final JMenuItem exit;
    private final JMenuItem help;
    private final JMenuItem about;

    public MainWindowBar() {
        JMenu file = new JMenu("Archivo");

        restart = new JMenuItem("Partida nueva");
        restart.setActionCommand("file.restart");
        file.add(restart);
        
        newGame = new JMenuItem("Reiniciar juego...");
        newGame.setActionCommand("file.newgame");
        file.add(newGame);

        exit = new JMenuItem("Salir");
        exit.setActionCommand("file.exit");
        file.add(exit);

        add(file);
        
        JMenu textureMenu = new JMenu("Textura");

        changeTexture = new JMenuItem("Cambiar textura...");
        changeTexture.setActionCommand("texture.load");
        textureMenu.add(changeTexture);
        
        resetTexture = new JMenuItem("Por defecto");
        resetTexture.setActionCommand("texture.reset");
        textureMenu.add(resetTexture);
        
        add(textureMenu);
        
        JMenu helpMenu = new JMenu("Ayuda");

        help = new JMenuItem("Ayuda...");
        help.setActionCommand("help.help");
        helpMenu.add(help);
        
        about = new JMenuItem("Acerca de...");
        about.setActionCommand("help.about");
        helpMenu.add(about);

        add(helpMenu);
    }
    
    public void addActionListener(ActionListener a) {
        restart.addActionListener(a);
        newGame.addActionListener(a);
        changeTexture.addActionListener(a);
        resetTexture.addActionListener(a);
        exit.addActionListener(a);
        help.addActionListener(a);
        about.addActionListener(a);
    }
}
