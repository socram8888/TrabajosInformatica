/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package ti.saxeith.sym.ctrl;

import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import ti.saxeith.sym.dat.Game;
import ti.saxeith.sym.gui.DeckTexture;
import ti.saxeith.sym.gui.MainWindow;
import ti.saxeith.sym.gui.NewGameWindow;

/**
 *
 * @author Marcos
 */
public class NewGameController implements ActionListener {
    
    private final NewGameWindow window;
    private final DeckTexture texture;
    
    public NewGameController(NewGameWindow window, DeckTexture texture) {
        this.window = window;
        this.texture = texture;
        window.addActionListener(this);
        window.setVisible(true);
    }

    @Override
    public void actionPerformed(ActionEvent e) {
        Game game = null;
        
        switch (e.getActionCommand()) {
            case "newgame.1":
                game = new Game(2);
                break;
            
            case "newgame.2":
                game = new Game(3);
                break;
        }
        
        if (game != null) {
            window.dispose();
            MainWindow mainWindow = new MainWindow(game, texture);
            new MainController(game, mainWindow);
        }
    }
}
