// b3_4_simplificar.cpp
// Marcos Vives Del Sol - GII 25/X/2013
// License: WTFPL

#include <iostream>
#include <math.h>
using namespace std;

int main(void)
{
    int numerator, denominator, prime;

    cout << "Este programa simplifica una fraccion mostrando los pasos "
    "seguidos para hacerlo." << endl << endl;

    cout << "Dame numerador: ";
    cin >> numerator;
    cout << "Dame denominador: ";
    cin >> denominator;
	
	cout << endl << numerator << " / " << denominator;

	// 2 es el primer primo
	prime = 2;
	// Con comprobar hasta la mitad es suficiente, por encima solo dara
	// cero coma algo
	while (prime <= ceil(numerator / 2) && prime <= ceil(denominator / 2))
	{
		// Si ambos son divisibles, los dividimos
		if (numerator % prime == 0 && denominator % prime == 0)
		{
			numerator /= prime;
			denominator /= prime;
			cout << " = " << numerator << " / " << denominator;
		}
		else
		{
			// Si el primo es 2, incrementamos en uno para que el primo sea 3
			// Sino, incrementamos en dos, para solo comprobar numeros impares
			// Idealmente solo comprobariamos numeros primos pero eso requiere
			// matrices y functiones auxiliares y no se permiten
			if (prime == 2)
				prime = 3;
			else
				prime += 2;
		}
	}

	cout << endl;
    return 0;
}
