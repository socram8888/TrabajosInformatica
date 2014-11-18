
#include <iostream>
#include "circulo.h"

Circulo::Circulo()
:x(0), y(0), radio(0)
{}

Circulo::Circulo(int x, int y, int radio)
{
    if (!cambiarPosicion(x,y) || !cambiarRadio(radio))
        cerr << "Circulo no valido\n";
}

bool Circulo::cambiarRadio(int nuevoRadio)
{
    bool ok = (nuevoRadio > 0);
    if (ok)
        radio = nuevoRadio;
    return ok;
}

bool Circulo::cambiarPosicion(int nuevaX, int nuevaY)
{
    bool ok = (nuevaX > 0 && nuevaY > 0);
    if (ok)
    {
        x = nuevaX;
        y = nuevaY;
    }
    return ok;
}

bool Circulo::desplazarCirculo(int despX, int despY)
{
    return cambiarPosicion(x + despX, y + despY);
}

int Circulo::obtenerRadio() {
	return radio;
}

int Circulo::obtenerCentroX() {
	return x;
}

int Circulo::obtenerCentroY() {
	return y;
}

istream& operator>>(istream& input, Circulo& c)
{
    int x, y, radio;
    char signo;
    
    input >> x >> signo >> y >> signo >> radio;

    if (!c.cambiarPosicion(x,y) || !c.cambiarRadio(radio))
        cerr << "Circulo no valido";

    return input;
}

ostream& operator<<(ostream& out, Circulo& c)
{
    out << "Posicion: " << c.x << ", " << c.y << "\n";
    out << "Radio: " << c.radio << endl;
    
    return out;
}
