/*******************************************************************/
/*                                                                 */
/*                    Rectangulo.H                                 */
/*                                                                 */
/* Declaraci�n de una clase para Rectangulos. Un rect�ngulo se     */
/* representa por una posci�n (x,y), su base y su altura           */
/*******************************************************************/

#ifndef _RECTANGULO_H
#define _RECTANGULO_H

#include <iostream>
#include "circulo.h"
using namespace std;

class Rectangulo 
{ 

public:

    Rectangulo();                       // Constructor por defecto
    Rectangulo (int, int, int, int);
    //Metodos modificadores
    bool cambiarAncho (int);            // Modifica la anchura del rect�ngulo
    bool cambiarAlto (int);             // Modifica la altura del rect�ngulo
    bool cambiarPosicion (int, int);    // Modifica la posicion del rectangulo
    bool desplazarRectangulo(int, int); // Desplaza el rect�ngulo horizontalmente y verticalmente
    int  calcularArea();                // Devuelve el �rea del rect�ngulo
    int  calcularPerimetro();
    bool estaDentroPunto(int, int);     // Indica si un punto est� en el interior del rect�ngulo.
	bool estaDentroCirc(Circulo);

    //Entrada y salida
    friend istream& operator>>(istream&, Rectangulo&);              // Pide la posicion y dimensiones del rect�ngulo
    friend ostream& operator<<(ostream&, Rectangulo&);           // Muestra por pantalla los par�metros del rect�ngulo (x, y, ancho y alto).

private:
    int x, y;                           // posici�n inicio del rect�ngulo
    int base, altura;                    // dimensiones del rect�ngulo
};

#endif
