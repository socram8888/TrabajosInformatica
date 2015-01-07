/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package ti.saxeith.sym;

import ti.saxeith.sym.ctrl.MainController;
import ti.saxeith.sym.dat.Game;
import ti.saxeith.sym.gui.MainWindow;

/**
 *
 * @author Marcos
 */
public class Main {

    /**
     * @param args the command line arguments
     */
    public static void main(String[] args) {
        Game game = new Game(2);
        MainWindow win = new MainWindow(game);
        new MainController(game, win);
    }
}
