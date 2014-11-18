#ifndef __CELDA_H__
#define __CELDA_H__

class Celda
{
public:
	Celda ();					// Constructor por defecto

	Celda (int x_ini, int y);	// Constructor con argumentos

	int dameX ();				// Devuelve la posicion x
	int dameY ();				// Devuelve la posicion y

	void fijar (int x_nuevo, int y_nuevo);	// Establece la posicion x e y

private:
	int x;						// Posicion x de la celda
	int y;						// Posicion y de la celda
};

#endif
