/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package es.uv.eu.calculadora;

import es.uv.eu.calculadora.controlador.CalculadoraControlador;
import es.uv.eu.calculadora.modelo.CalculadoraModelo;
import es.uv.eu.calculadora.vista.CalculadoraVista;

/**
 *
 * @author Marcos Vives Del Sol
 */
public class Calculadora {
    public static void main(String[] args) {
        CalculadoraModelo model = new CalculadoraModelo();
        CalculadoraVista view = new CalculadoraVista();
        new CalculadoraControlador(model, view);
    }
}
