/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package ti.saxeith.sym.ctrl;

import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.io.File;
import java.io.IOException;
import javax.swing.JOptionPane;
import ti.saxeith.sym.dat.Game;
import ti.saxeith.sym.gui.LoadTextureDialog;
import ti.saxeith.sym.gui.MainWindow;
import ti.saxeith.sym.gui.NewGameWindow;

/**
 *
 * @author Marcos
 */
public class MainController implements ActionListener {
    private final Game game;
    private final MainWindow gui;

    public MainController(Game game, MainWindow gui) {
        this.game = game;
        this.gui = gui;
        gui.addActionListener(this);
        gui.setVisible(true);
    }

    @Override
    public void actionPerformed(ActionEvent e) {
        //System.out.println(e);

        switch (e.getActionCommand()) {
            case "file.exit":
                System.exit(0);
                
            case "stack.click":
                if (game.isFinished()) {
                    game.playAgain();
                } else {
                    game.requestCard();
                }
                gui.refreshWindow();
                break;

            case "stack.skip":
                if (game.isFinished()) {
                    game.playAgain();
                } else {
                    game.passPlayer();
                }
                gui.refreshWindow();
                break;
                
            case "file.restart":
                game.playAgain();
                gui.refreshWindow();
                break;
                
            case "file.newgame":
                gui.dispose();
                NewGameWindow ngw = new NewGameWindow();
                new NewGameController(ngw, gui.getRug().getDeckTexture());
                break;
                
            case "texture.load":
                LoadTextureDialog textDiag = new LoadTextureDialog();
                textDiag.setVisible(true);
                File textureFile = textDiag.getFile();
                if (textureFile != null) {
                    try {
                        gui.getRug().getDeckTexture().loadTexture(textureFile);
                        gui.refreshWindow();
                        gui.revalidate();
                        gui.repaint();
                    } catch (IOException exception) { }
                }
                break;

            case "texture.reset":
                gui.getRug().getDeckTexture().setDefault();
                gui.refreshWindow();
                gui.revalidate();
                gui.repaint();
                break;
                
            case "help.about":
                JOptionPane.showMessageDialog(gui,
                        "Programado por Marcos Vives Del Sol\n"
                                + "Texturas predeterminadas de Dinvaders"
                        );
                break;
                
            default:
                System.err.println("Dafuq. Unhanled event: " + e);
        }
    }
}
