
// b1_1_laboratorio.cpp
// Marcos Vives Del Sol - GII 17/X/2013
// License: WTFPL

#include <iostream>
#include <stdlib.h>
using namespace std;

const double METER_INCH = 39.3700787;
const double METER_FEET = 3.2808399;
const double METER_YARD = 1.0936133;
const double METER_MILE = 0.000621371192;
const double METER_LEAGUE = 0.000207125;

int main(void)
{
    double meter;

    cout << "Este programa pasa una distancia en metros introducida por el teclado a distintas unidades de medida británicas" << endl << endl;
    cout << "Dame distancia en metros a convertir: ";
    cin >> meter;

    cout << endl << "La distancia de " << meter << " metros es:" << endl;
    cout << "  " << meter * METER_INCH << " pulgadas" << endl;
    cout << "  " << meter * METER_FEET << " pies" << endl;
    cout << "  " << meter * METER_YARD << " yardas" << endl;
    cout << "  " << meter * METER_MILE << " millas" << endl;
    cout << "  " << meter * METER_LEAGUE << " leguas" << endl;

    system("pause");
    return 0;
}
