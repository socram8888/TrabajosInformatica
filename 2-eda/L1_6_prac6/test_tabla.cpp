
/**
 * Prueba de la implementacion de una tabla
 * @author Marcos Vives
 */

#include <iostream>
#include "tabla.h"
#include "alumno.h"
using namespace std;

#define SLOTS 50
#define ELEMS 1000

int main()
{
    Tabla tabla = Tabla(SLOTS);
    string searchdnis[3];

    for (unsigned i = 0; i < ELEMS; i++)
    {
        Alumno alumno = Alumno(5);

        // Guardar dos DNIs cualquiera para buscarlos despues
        if (i < 2)
			searchdnis[i] = alumno.getDNI();

        tabla.insertar(alumno.getDNI(), alumno);
    }

	// DNI no existente
    searchdnis[2] = "999999999NX";

    cout << "******* Mostrando contenido: *******" << endl;
    tabla.mostrar(cout);

    cout << endl << "******* Mostrando DNIs cualesquiera: *******" << endl;
    for (unsigned i = 0; i < 3; i++)
    {
        Alumno alumno;
        cout << "Persona con DNI " << searchdnis[i] << endl;
        if (tabla.buscar(searchdnis[i], alumno))
            cout << alumno << endl;
        else
            cout << "*** NO ENCONTRADO" << endl << endl;
    }

    cout << endl << "******* Factor de carga: " << tabla.factorCarga() << " *******" << endl;

	return 0;
}

/*
 ¿Están los elementos correctamente distribuidos en la tabla?

 Sí, los slots contienen entre 17 y 23 elementos para 1000 elementos en 50 slots,
 con lo cual podemos decir al aproximarse al factor de carga, que están correctamente
 distribuidos.
*/