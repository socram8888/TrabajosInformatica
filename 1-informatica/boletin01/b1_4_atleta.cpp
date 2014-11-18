
// b1_4_atleta.cpp
// Marcos Vives Del Sol - GII 18/X/2013
// License: WTFPL

#include <iostream>
using namespace std;

int main(void)
{
    // Dobles por si alguien quiere meter unidades con decimales
    double meter, min, sec, cent;
    double meterSec, kilometerHour;

    cout << "Este programa determina la velocidad a que corre un atleta a partir del tiempo empleado y la distancia recorrida." << endl << endl;
    cout << "Dime distancia en metros: ";
    cin >> meter;
    cout << "Dame el tiempo:" << endl << " Dame los minutos: ";
    cin >> min;
    cout << " Dame los segundos: ";
    cin >> sec;
    cout << " Dame las centésimas: ";
    cin >> cent;

    // Pasar a una unidad del sistema internacional
    sec += min * 60 + cent / 100;

    meterSec = meter / sec;
    kilometerHour = (meter / 1000) / (sec / 3600);

    cout << endl << "La velocidad del atleta es de " << kilometerHour << " km/h (" << meterSec << " m/s)" << endl;

    return 0;
}
