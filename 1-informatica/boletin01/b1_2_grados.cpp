
// b1_2_grados.cpp
// Marcos Vives Del Sol - GII 17/X/2013
// License: WTFPL

#include <iostream>
#include <math.h>
using namespace std;

const double PI = 3.1415926544;

int main(void)
{
    // Doble por si alguien quiere meter grados con decimales para convertirlos a grados, minutos y segundos
    double sexDeg, sexMin, sexSec;
    double cenDeg, cenMin, cenSec;
    double radian;
    // Grados en forma de ratio [0, 1]. Se evitan "overflows" (minutos o segundos >= 60) y facilita el cálculo en otras unidades
    double ratio;
    // Doble temporal para intercambio de variables
    double td;


    cout << "Este programa nos pasa una medida de un ángulo en grados sexagesimales a su equivalente en grados centesimales y radianes." << endl << endl;
    cout << "Dame un ángulo en grados sexagesimales:" << endl;
    cout << " Dame grados: ";
    cin >> sexDeg;
    cout << " Dame minutos: ";
    cin >> sexMin;
    cout << " Dame segundos: ";
    cin >> sexSec;

    ratio = sexDeg / 360.0 + sexMin / (360.0 * 60.0) + sexSec / (360.0 * 60.0 * 60.0);

    // ---------------------
    // --- SEXAGESIMALES ---
    // ---------------------
    sexDeg = ratio * 360.0;

    // El fmod saca la parte decimal
    td = fmod(sexDeg, 1);
    sexMin = 60.0 * td;
    sexDeg -= td;

    td = fmod(sexMin, 1);
    sexSec = 60.0 * td;
    sexMin -= td;

    cout << "Grados sexagesimales: " << sexDeg << "º " << sexMin << "' " << sexSec << "\"" << endl;

    // --------------------
    // --- CENTESIMALES ---
    // --------------------
    cenDeg = ratio * 400.0;

    td = fmod(cenDeg, 1);
    cenMin = 100.0 * td;
    cenDeg -= td;

    td = fmod(cenMin, 1);
    cenSec = 100.0 * td;
    cenMin -= td;

    cout << "Grados centesimales: " << cenDeg << "g " << cenMin << "m " << cenSec << "s" << endl;

    // ----------------
    // --- RADIANES ---
    // ----------------
    radian = ratio * 2 * PI;
    cout << "Radianes: " << radian << endl;

    return 0;
}
