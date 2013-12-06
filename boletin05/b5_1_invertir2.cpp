
// Informatica - Boletin 5 (30/XI/2013) - b5_1_invertir2.cpp
// Marcos Vives Del Sol
// Licencia: WTFPL

#include <iostream>
#include <cmath>
using namespace std;

/*** Invierte *****************************************************************
 * 
 * Descripcion: Invierte un numero entero positivo mediante recursividad
 * 
 * Parametros: 
 * Nombre Tipo         E/S Descripcion 
 * ------ ------------ --- ----------------------------------------------------
 * num    unsigned int  E  El numero a invertir
 * 
 * Valor devuelto: 
 * unsigned int El numero invertido
 *****************************************************************************/
unsigned int Invierte(unsigned int num)
{
	if (num > 10)
		num = num % 10 * pow(10, ceil(log(num) / log(10)) - 1) + Invierte(num / 10);
	return num;
}

int main(void)
{
	int x; 

	cout << "Dame un numero entero: ";
	cin >> x;

	x = Invierte (x);
	cout << "El numero invertido es: " << x;

	return 0;
}
