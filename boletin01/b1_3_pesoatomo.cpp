
// b1_3_pesoatomo.cpp
// Marcos Vives Del Sol - GII 18/X/2013
// License: WTFPL

#include <iostream>
using namespace std;

const double AVOGADRO_NUM = 6.022e23;

int main(void)
{
    int substance;
    double atomicalMass;

    cout << "Este programa determina el peso de un solo átomo de una sustancia, a partir de su peso atómico." << endl << endl;
    cout << "Dime sustancia: ";
    cin >> substance;
    cout << "Dame su peso atómico: ";
    cin >> atomicalMass;

    cout << "El peso de un átomo de la sustancia " << substance << " es de " << atomicalMass / AVOGADRO_NUM << " gramos" << endl;

    return 0;
}
