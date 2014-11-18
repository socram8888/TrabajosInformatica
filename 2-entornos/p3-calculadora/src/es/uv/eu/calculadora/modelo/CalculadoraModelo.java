package es.uv.eu.calculadora.modelo;

import java.util.ArrayList;

/**
 *
 * @author
 */
public final class CalculadoraModelo {
    
    private ArrayList<String> pila = new ArrayList<>();
    private String numero;
    private boolean nuevoNumero;
    
    
    public CalculadoraModelo() {
        reset();
    }

    public void addDigit(String d) {
        if (nuevoNumero) {
            numero = d;
            nuevoNumero = false;
        }
        else {
            numero += d;
        }
    }
    
    public void addPoint() {
        if (nuevoNumero) {
            nuevoNumero = false;
            numero = "0.";
        }
        else if (!numero.contains(".")) {
            numero += ".";
        }
    }
    
    public void calc(String operacion) {
        float c;

        if ("+-*/".indexOf(operacion) != -1 && pila.isEmpty()) {
            // Apilamos las operaciones
            pila.add(numero);
            pila.add(operacion);
            nuevoNumero = true;
        }
        else if ("+-*/=".indexOf(operacion) != -1 && pila.size() == 2) {
            
            c = opera(pila.get(0), pila.get(1), numero); 
            numero = String.valueOf(c);
 
            // Borramos la pila y reiniciamos
            pila.clear();
            nuevoNumero = true;
            
            // Si la operacion debe continuar, apilamos
            if (!operacion.equals("=")) {
                pila.add(numero);           
                pila.add(operacion);
            } 
        }
    }

    public void deleteChar() {
        if (nuevoNumero) {
            reset();
        }
        else if (numero.length() > 1) {
            numero = numero.substring(0, numero.length()-1);
        }
        else if (numero.length() == 1) {
            nuevoNumero = true;
            numero = "0";
        }
    }
    
    public String getValor() {
        return numero;
    }

    public final void reset() {
        pila.clear();
        numero = "0";
        nuevoNumero = true;
    }
    
    public String getStatus() {
        if (pila.isEmpty()) {
            return numero;
        }
        else if (nuevoNumero) {
            return pila.get(0) + " " + pila.get(1);
        }
        else {
            return pila.get(0) + " " + pila.get(1) + " " + numero;
        }
    }

    private float opera(String m1, String op, String m2) {
        float a, b, c;

        try {
            a = Float.valueOf(m1);
        }
        catch (Exception anyException) {
            a = (float)0.0;
        }

        try {
            b = Float.valueOf(m2);
        }
        catch (Exception anyException) {
            b = (float)0.0;
        }

        // Operamos
        switch(op) {
            case "+":
                c = a+b;
                break;
                
            case "-": 
                c = a - b;
                break;
                    
            case "*": 
                c = a * b;
                break;
                    
            case "/":
                c = a / b;
                break;
                    
            default:
                c = (float)0.0;
                break;
        }
        return c;
    }     
}
