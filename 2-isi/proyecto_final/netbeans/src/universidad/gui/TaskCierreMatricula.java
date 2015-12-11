/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package universidad.gui;

import java.util.TimerTask;
import javax.swing.JFrame;
import javax.swing.JOptionPane;
import universidad.ctrl.Usuario;

/**
 *
 * @author Marcos
 */
public class TaskCierreMatricula extends TimerTask {
    private final Usuario usuario;
    private JFrame ventanaActual;
    private final Object lock = new Object();
    private boolean expirado;

    public TaskCierreMatricula(Usuario usuario) {
        this.usuario = usuario;
    }

    public void setVentanaActual(JFrame ventanaActual) {
        this.ventanaActual = ventanaActual;
    }

    @Override
    public void run() {
        synchronized (lock) {
            if (usuario.comprobarPlazoMatriculacion()) {
                return;
            }

            if (!cancel()) {
                return;
            }

            expirado = true;

            JOptionPane.showMessageDialog(ventanaActual, "Se ha cerrado el plazo de matriculación. No es posible realizar matrículas nuevas para su titulación.", "Error", JOptionPane.ERROR_MESSAGE);
            ventanaActual.dispose();

            new VistaAlumno(usuario).setVisible(true);
        }
    }

    public Object getLock() {
        return lock;
    }

    public boolean expirado() {
        return expirado;
    }
}
