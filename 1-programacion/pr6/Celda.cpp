#include <iostream>
#include "Celda.h"

using namespace std;

Celda::Celda ()
: x(0), y(0)
{
}

Celda::Celda (int x_ini, int y_ini)
{
	if (x_ini < 0 || y_ini < 0)
		cerr << "Error: Las coordenadas de la celda deben ser positivas" << endl;
	else
	{
		x = x_ini;
		y = y_ini;
	}
}

int Celda::dameX ()
{
	return x;
}

int Celda::dameY ()
{
	return y;
}

void Celda::fijar (int x_nuevo, int y_nuevo)
{
	x = x_nuevo;
	y = y_nuevo;
}
