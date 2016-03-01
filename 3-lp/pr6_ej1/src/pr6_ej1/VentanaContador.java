/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package pr6_ej1;

import java.awt.FlowLayout;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import javax.swing.JButton;
import javax.swing.JFrame;

/**
 *
 * @author alumno
 */
public class VentanaContador extends JFrame {

    JButton botonComenzar;
    JButton botonFinalizar;
    int contador;
    boolean continuar;
    HiloContador hilo;

    public VentanaContador() {
        botonComenzar = new JButton("Comenzar");
        botonFinalizar = new JButton("Finalizar");
        getContentPane().setLayout(new FlowLayout());
        getContentPane().add(botonComenzar);
        getContentPane().add(botonFinalizar);
        botonComenzar.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                if (hilo == null) {
                    hilo = new HiloContador(VentanaContador.this);
                    hilo.start();
                }
            }
        });
        botonFinalizar.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                if (hilo != null) {
                    hilo.interrupt();
                    hilo = null;
                }
            }
        });
        setSize(300, 80);
    }

    private static class HiloContador extends Thread {
        private final VentanaContador win;
        int valor;

        public HiloContador(VentanaContador win) {
            this.win = win;
        } 

        @Override
        public void run() {
            while (!isInterrupted()) {
                valor = (valor + 1) % 10;
                win.setTitle("" + valor);
            }
        }
    }
    public static void main(String[] argv) {
        (new VentanaContador()).setVisible(true);
    }
}
