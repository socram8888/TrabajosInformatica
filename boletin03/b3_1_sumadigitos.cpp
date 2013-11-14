// b3_1_sumadigitos.cpp 
// Marcos Vives Del Sol - GII 25/X/2013
// License: WTFPL

#include <iostream>
using namespace std;

int main(void)
{
    int num, tempnum, sum = 0;

    cout << "Este programa suma las cifras de un numero entero positivo"
    "introducido por teclado." << endl << endl;

    cout << "Dame numero entero positivo: ";
    cin >> num;

	tempnum = num;
	while (tempnum != 0)
	{
		sum += tempnum % 10;
		tempnum /= 10;
	}

    cout << "La suma de las cifras de " << num << " es " << sum << endl;

    return 0;
}
