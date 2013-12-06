
// Informatica - Boletin 5 (30/XI/2013) - b5_2_cambiobase.cpp
// Marcos Vives Del Sol
// Licencia: WTFPL

#include <iostream>
using namespace std;

/*** CambioBase ***************************************************************
 * 
 * Descripcion: Cambia la base de un numero entero positivo
 * 
 * Parametros: 
 * Nombre Tipo         E/S Descripcion 
 * ------ ------------ --- ----------------------------------------------------
 * num    unsigned int  E  El numero
 * base   unsigned int  E  La base, entre dos y nueve
 * 
 * Valor devuelto: 
 * unsigned int El numero "num" en base "base"
 *****************************************************************************/
unsigned int CambioBase(unsigned int num, unsigned int base)
{
	if (num >= base)
		num = num % base + 10 * CambioBase(num / base, base);
	return num;
}

int main()
{
	int x, base;
	int res;

	cout << "Dame un numero entero: ";
	cin >> x;
	if (!cin.fail())
	{
		cout << "Dame base: ";
		cin >> base;
		if (!cin.fail() && base >= 2 && base <= 9)
		{
			res = CambioBase(x, base);
			cout << "El numero " << x;
			cout << " en base " << base;
			cout << " es: " << res << endl;
		}
		else
			cout << "Base no valida" << endl;
	}
	else
		cout << "Numero no valido" << endl;

	return 0;
}
