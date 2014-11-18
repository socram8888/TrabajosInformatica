// b2_2_bisiestos.cpp
// Marcos Vives Del Sol - GII 20/X/2013
// License: WTFPL

#include <iostream>
using namespace std;

int main(void)
{
    int year;
    bool leap = false;
    cout << "Este programa calcula si un año es bisiesto o no" << endl << endl;
    cout << "Introduce el año: ";
    cin >> year;

    // Antes del año 46AC, el calendario ab urbe condita no contaba con bisiestos, así no hay necesidad de comprobarlos
    if (year >= -46) // Vigencia del calendario juliano
    {
        // Es bisiesto, en principio, si es divisible entre cuatro
        leap = (year % 4 == 0);

        // Si ha entrado en vigencia el calendario juliano (año >= 1582), el año es divisible entre 100, pero no entre 400, entonces no lo es
        if (leap && year >= 1582 && year % 100 == 0 && year % 400 != 0)
        {
            leap = false;
        }
    }

    cout << endl << "El año " << year;
    if (!leap)
    {
        cout << " NO";
    }
    cout << " es bisiesto" << endl;

    return 0;
}
