/*******************************************************************/
/*                                                                 */
/*                    Rectangulo.H                                 */
/*                                                                 */
/* Declaración de una clase para Rectangulos. Un rectángulo se     */
/* representa por una posción (x,y), su base y su altura           */
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
    bool cambiarAncho (int);            // Modifica la anchura del rectángulo
    bool cambiarAlto (int);             // Modifica la altura del rectángulo
    bool cambiarPosicion (int, int);    // Modifica la posicion del rectangulo
    bool desplazarRectangulo(int, int); // Desplaza el rectángulo horizontalmente y verticalmente
    int  calcularArea();                // Devuelve el área del rectángulo
    int  calcularPerimetro();
    bool estaDentroPunto(int, int);     // Indica si un punto está en el interior del rectángulo.
	bool estaDentroCirc(Circulo);

    //Entrada y salida
    friend istream& operator>>(istream&, Rectangulo&);              // Pide la posicion y dimensiones del rectángulo
    friend ostream& operator<<(ostream&, Rectangulo&);           // Muestra por pantalla los parámetros del rectángulo (x, y, ancho y alto).

private:
    int x, y;                           // posición inicio del rectángulo
    int base, altura;                    // dimensiones del rectángulo
};

#endif
