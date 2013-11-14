// b2_4_diasmes.cpp 
// Marcos Vives Del Sol - GII 19/X/2013
// License: WTFPL

#include <iostream>
using namespace std;

int main(void)
{
    int month, days;

    cout << "Este programa determina el numero de dias de un mes introducido"
    "por teclado." << endl << endl;

    cout << "Dime el mes: ";
    cin >> month;
    cout << endl << "El mes ";

    switch (month)
    {
        case 2:
            cout << "tiene 28 dias";
            break;
        case 4:
        case 6:
        case 9:
        case 11:
            cout << "tiene 30 dias";
            break;
        case 1:
        case 3:
        case 5:
        case 7:
        case 8:
        case 10:
        case 12:
            cout << "tiene 31 dias";
            break;
        default:
            cout << "no es valido";
    }

    cout << endl;

    return 0;
}
