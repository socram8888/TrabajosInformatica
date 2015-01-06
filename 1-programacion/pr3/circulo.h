
#ifndef HAVE_CIRCULO_H
#define HAVE_CIRCULO_H

#include <iostream>
using namespace std;

class Circulo
{
    public:
        Circulo(); // Constructor por defecto
        Circulo(int, int, int); // Constructor con argumentos: x, y, radio
        bool cambiarRadio (int); // Cambia el radio del círculo
        bool cambiarPosicion(int, int);
        bool desplazarCirculo(int, int); // Desplaza el centro del circulo
		int obtenerRadio();
		int obtenerCentroX();
		int obtenerCentroY();
        friend istream& operator>>(istream&, Circulo&); // Lee de teclado centro y radio
        friend ostream& operator<<(ostream&, Circulo&); // Muestra los param del circulo

    private:
        int x, y; // posición inicio del rectángulo
        int radio; // radio del círculo
};

#endif // HAVE_CIRCULO_H
