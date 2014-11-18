
// Informatica - Boletin 4 (11/XI/2013) - b4_4_invertir.cpp
// Marcos Vives Del Sol
// Licencia: WTFPL

#include <iostream>
using namespace std;

int revert(int original)
{
	int reversed = 0;

	while (original != 0)
	{
		// Multiplicamos el numero invertido por diez para añadir un cero a la derecha, y le sumamos el digito inferior del original
		reversed = reversed * 10 + original % 10;
		// Eliminamos el digito que acabamos de introducir
		original /= 10;
	}

	return reversed;
}

int main(void) 
{ 
	int x; 

	cout << "Este programa invierte un numero entero positivo introducido por teclado." << endl << endl;

	cout << "Dame un numero entero: "; 
	cin >> x; 

	x = revert(x); 
	cout << "El numero invertido es: " << x; 

	return 0; 
}
