
// Informatica - Boletin 4 (12/XI/2013) - b4_2_pimachin.cpp
// Marcos Vives Del Sol
// Licencia: WTFPL

#include <iostream>
#include <cmath>
using namespace std;

const int DOUBLE_PRECISION = 16;

double taylor_atan(double num)
{
	double sum = 0, oldsum;
	int iteration = 0;
	bool finish = false;
	do
	{
		oldsum = sum;
		// De https://en.wikipedia.org/wiki/Taylor_series
		sum += pow(-1, iteration) * pow(num, 2 * iteration + 1) / (2 * iteration + 1);
		if (oldsum == sum || iteration >= 16) // Calcular hasta el maximo de precision que permitan los dobles
			finish = true;
		iteration++;
	}
	while (!finish);
	return sum;
}

double pi_machin()
{
	// De https://en.wikipedia.org/wiki/John_Machin
	return 16 * taylor_atan(1.0 / 5.0) - 4 * taylor_atan(1.0 / 239.0);
}

int main()
{
	cout.precision(DOUBLE_PRECISION);
	cout << pi_machin();
}
