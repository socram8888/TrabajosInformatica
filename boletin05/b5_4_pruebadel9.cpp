
// Informatica - Boletin 5 (30/XI/2013) - b5_4_pruebadel9.cpp
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

/*** cast_nines ***************************************************************
 * 
 * Descripcion: Realiza la prueba del nueve
 * 
 * Parametros: 
 * Nombre  Tipo         E/S Descripcion 
 * ------- ------------ --- ---------------------------------------------------
 * factorA unsigned int  E  El primer factor de la multiplicacion
 * factorB unsigned int  E  El segundo operador de la multiplicacion
 * result  unsigned int  E  El valor calculado por el usuario
 * 
 * Valor devuelto: 
 * bool
 *****************************************************************************/
bool cast_nines(unsigned int factorA, unsigned int factorB, unsigned int result)
{
	unsigned int rootProduct;

	factorA = digital_root(factorA);
	factorB = digital_root(factorB);
	rootProduct = digital_root(factorA * factorB);
	result = digital_root(result);

	cout << "La suma digital de cada factor es:" << endl;
	cout << "   Suma digital primer factor: " << factorA << endl;
	cout << "   Suma digital segundo factor: " << factorB << endl;
	cout << "La suma digital del producto de las sumas digitales es: " << rootProduct << endl;
	cout << "La suma digital de tu resultado es: " << result << endl << endl;

	return result == rootProduct;
}

/*** request_values ***********************************************************
 * 
 * Descripcion: Pide los valores para realizar la comprobacion
 * 
 * Parametros: 
 * Nombre  Tipo         E/S Descripcion 
 * ------- ------------ --- ---------------------------------------------------
 * factorA unsigned int  S  El primer factor de la multiplicacion
 * factorB unsigned int  S  El segundo operador de la multiplicacion
 * result  unsigned int  S  El valor calculado por el usuario
 * 
 * Valor devuelto: 
 * bool
 *****************************************************************************/
bool request_data(unsigned int &factorA, unsigned int &factorB, unsigned int &result)
{
	bool ok = true;
	cout << "Dame factores de la multiplicacion:" << endl;
	cout << "   Dame primer factor: ";
	cin >> factorA;
	ok = !cin.fail();

	if (ok)
	{
		cout << "   Dame segundo factor: ";
		cin >> factorB;
		ok = !cin.fail();
	}

	if (ok)
	{
		cout << "   Dame tu resultado de la multiplicacion: ";
		cin >> result;
		ok = !cin.fail();
	}

	cout << endl;

	return ok;
}

int main()
{
	unsigned int factorA;
	unsigned int factorB;
	unsigned int result;

	cout << "Este programa determina si una multiplicacion esta bien" << endl;
	cout << "resuelta aplicando la prueba del nueve." << endl << endl;
 
	if (request_data(factorA, factorB, result))
	{
		if (cast_nines(factorA, factorB, result))
			cout << "La multiplicacion, probablemente, este bien." << endl;
		else
			cout << "La multiplicacion esta mal." << endl;
	}

	return 0;
}
