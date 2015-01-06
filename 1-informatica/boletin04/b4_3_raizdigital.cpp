
// Informatica - Boletin 4 (11/XI/2013) - b4_3_raizdigital.cpp
// Marcos Vives Del Sol
// Licencia: WTFPL

#include <iostream>
using namespace std;

unsigned int digital_root(unsigned int num)
{
	unsigned int sum;

	while (num > 10)
	{
		sum = 0;
		while (num != 0)
		{
			sum += num % 10;
			num /= 10;
		}
		num = sum;
	}

	return num;
}

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
