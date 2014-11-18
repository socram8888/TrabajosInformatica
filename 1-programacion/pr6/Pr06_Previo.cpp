/*******************************************************************/
/* Asignatura: Programacion                                        */
/* Curso 2013-2014                                                 */
/* Practica 6                                                      */
/* Programación Orientada a Objetos                                */
/*                                                                 */
/* AUTOR: Miguel Angel Gamón Giménez                               */
/* FECHA: 25 de Abril de 2014                                 	   */
/*                                                                 */
/* PROPOSITO: Practicar la utilización del TAD Pila                */
/*                                                                 */
/*******************************************************************/

#include <iostream>
#include <stdlib.h>
#include "ResuelveLaberinto.h"
#include "sysdep.h"

using namespace std;
/*
int main()
{
	// Valores de prueba 
	GeneraLaberintos laberinto;

	
    if (!laberinto.fijarTamanyo(20, 50))
        cerr << "Error: El tamanyo establecido no es correcto" << endl;
    else
    {
        laberinto.generar();

        laberinto.dibujar();

        if (!laberinto.guardarFichero ("laberinto_test.txt"))
            cerr << "Error al guardar el fichero del laberinto" << endl;
        else
            cout << "Fichero guardado correctamente." << endl;
    }

    system ("pause");

    return 0;
}
*/

int main()
{
    int x, y;
	ResuelveLaberinto laberinto;

    if (!laberinto.leerFichero("laberinto_test.txt"))
    {
        cerr << "Imposible leer del fichero de entrada" << endl;
        return 1;
    }

    display_clear();
    laberinto.dibujar();

    cout << "Introduce coordenadas iniciales (el punto superior izquierdo es 0,0): ";
    cin >> x >> y;

    if (laberinto.resolver(x, y)) {
       display_clear();
       laberinto.dibujar();
       system("pause");
    }

    return 0;
}
