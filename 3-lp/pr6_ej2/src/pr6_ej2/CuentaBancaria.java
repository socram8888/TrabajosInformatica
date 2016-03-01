/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

package pr6_ej2;

import java.util.concurrent.atomic.AtomicInteger;
import java.util.logging.Level;
import java.util.logging.Logger;

/**
 *
 * @author alumno
 */
public class CuentaBancaria {

    private int dinero;

    public CuentaBancaria(int inicial) {
        this.dinero = inicial;
    }

    public synchronized int getDinero() {
        return dinero;
    }

    public synchronized void meterDinero(int delta) {
        dinero += delta;
        notifyAll();
    }

    public synchronized boolean sacarDinero(int delta) {
        while (delta > dinero) {
            //System.out.println("Esperando para sacar " + delta);
            try {
                wait();
            } catch (InterruptedException e) {
                return false;
            }
        }

        dinero -= delta;
        return true;
    }

    /**
     * @param args the command line arguments
     */
    public static void main(String[] args) {
        CuentaBancaria cuenta = new CuentaBancaria(0);
        Thread[] hilos = new Thread[10000];
        for (int i = 0; i < hilos.length; i += 2) {
            hilos[i + 0] = new HiloMeter(cuenta, i);
            hilos[i + 1] = new HiloSacar(cuenta, i);
        }

        Randomize.randomize(hilos);

        for (int i = 0; i < 10000; i++) {
            hilos[i].start();
        }

        for (int i = 0; i < 10000; i++) {
            try {
                hilos[i].join();
            } catch (InterruptedException ex) {
                Logger.getLogger(CuentaBancaria.class.getName()).log(Level.SEVERE, null, ex);
            }
        }
        
        System.out.println("Dinero final: " + cuenta.getDinero());
    }
    
}
