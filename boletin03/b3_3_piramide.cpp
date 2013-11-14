// b3_3_piramide.cpp
// Marcos Vives Del Sol - GII 25/X/2013
// License: WTFPL

#include <iostream>
using namespace std;

int main(void)
{
    int height, i, j;

    cout << "Este programa muestra una piramide de numeros donde los "
    "vertices son unos y la base una sucesion creciente desde 1 hasta el "
    "centro de la base y decreciente hasta el final de la base." << endl;

    cout << "Dame altura de la piramide, entre 0 y 9: ";
    cin >> height;

	// i almacena el nivel actual
	i = 1;
	while (i <= height)
	{
		// Generamos padding a la izquierda
		j = height - i;
		while (j-- > 0)
			cout << " ";
		// Incrementamos el numero mientras sea menor para escribir los numeros
		// menores al nivel
		j = 1;
		while (j < i)
		{
			cout << j;
			j++;
		}
		// Mostramos el nivel actual y vamos decrementando mientras sea mayor
		// de cero
		j = i;
		while (j > 0)
		{
			cout << j;
			j--;
		}
		cout << endl;
		// Incrementamos el nivel
		i++;
	}

    return 0;
}
