// b3_2_capicua.cpp
// Marcos Vives Del Sol - GII 25/X/2013
// License: WTFPL

#include <iostream>
using namespace std;

int main(void)
{
    int num, tempNum, reverseNum;

    cout << "Este programa determina si un entero introducido por teclado"
    "es o no un numero capicua" << endl << endl;

    cout << "Dame numero entero positivo: ";
    cin >> num;

	// Invertimos el numero
	tempNum = num;
	reverseNum = 0;
	while (tempNum != 0)
	{
		// Sacamos digitos y los metemos en el orden inverso
		reverseNum = reverseNum * 10 + tempNum % 10;
		tempNum /= 10;
	}

	cout << "El numero " << num << " ";
	if (num != reverseNum)
	{
		cout << "NO ";
	}
	cout << "es capicua" << endl;

    return 0;
}
