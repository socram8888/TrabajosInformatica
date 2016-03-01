/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

package pr6_ej2;

/**
 *
 * @author alumno
 */
public class HiloMeter extends Thread {
    int cantidad;
    CuentaBancaria cuenta;

    public HiloMeter(CuentaBancaria cuenta, int cantidad) {
        this.cuenta = cuenta;
        this.cantidad = cantidad;
    }

    @Override
    public void run() {
        try {
            sleep((long) (Math.random() * 10));
        } catch (InterruptedException e) {
        };
        cuenta.meterDinero(cantidad);
    }
}
