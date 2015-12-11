/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package universidad;

import universidad.gui.IniciarSesion;
import universidad.model.GestorUniversidad;
import universidad.ctrl.Usuario;

/**
 *
 * @author Marcos
 */
public class Main {
    private static final int TIEMPO_BACKUP = 10 * 1000;

    public static void main(String[] args) {
        GestorUniversidad gu = new GestorUniversidad(TIEMPO_BACKUP);
        Usuario usuario = new Usuario(gu.getUniversidad());
        new IniciarSesion(usuario).setVisible(true);
    }
}
