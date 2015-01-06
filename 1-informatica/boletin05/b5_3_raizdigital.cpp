
// Informatica - Boletin 5 (30/XI/2013) - b5_3_raizdigital2.cpp
// Marcos Vives Del Sol
// Licencia: WTFPL

#include <iostream>
using namespace std;

/*** digital_root *************************************************************
 * 
 * Descripcion: Calcula la raiz digital de un numero dado
 * 
 * Parametros: 
 * Nombre Tipo         E/S Descripcion 
 * ------ ------------ --- ----------------------------------------------------
 * num    unsigned int  E  El numero
 * 
 * Valor devuelto: 
 * unsigned int
 *****************************************************************************/
unsigned int digital_root(unsigned int num)
{
	unsigned int root = 0;

	while (num > 0)
	{
		root += num % 10;
		num /= 10;
	}

	if (root >= 10)
		root = digital_root(root);

	return root;
}

/*** calculate_next_number ****************************************************
 * 
 * Descripcion: Calcula el primer numero entero mayor al introducido cuya raiz
 *              digital sea mayor que la raiz digital de su cuadrado
 * 
 * Parametros: 
 * Nombre Tipo         E/S Descripcion 
 * ------ ------------ --- ----------------------------------------------------
 * num    unsigned int  E  El numero inicial
 * 
 * Valor devuelto: 
 * unsigned int
 *****************************************************************************/
unsigned int calculate_next_number(unsigned int num)
{
	do
		num++;
	while (digital_root(num) <= digital_root(num * num));
	return num;
}

int main()
{
	unsigned int initial;

	cout << "Este programa determina el primer numero entero mayor que uno "
	"dado cuya suma digital sea mayor que la suma digital de su cuadrado."
	<< endl << endl;

	cout << "Introduce el numero inicial: ";
	cin >> initial;

	cout << "El primer numero mayor que " << initial << " que cumple las "
	"condiciones es " << calculate_next_number(initial) << endl;

	return 0;
}
