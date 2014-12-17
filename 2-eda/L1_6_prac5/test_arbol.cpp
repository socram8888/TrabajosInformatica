
#include <iostream>
#include "abb.h"
#include "alumno.h"
using namespace std;

int main()
{
    ABB arbol;
    string searchdnis[3];

    for (unsigned i = 0; i < 1000; i++)
    {
        Alumno alumno = Alumno(5);

        // Guardar dos DNIs cualquiera para buscarlos despues
        if (i % 500 == 0) {
            searchdnis[i / 500] = alumno.getDNI();
        }

        arbol.insertar(alumno.getDNI(), alumno);
    }
    searchdnis[2] = "999999999NX";

    cout << "******* Mostrando en orden: *******" << endl;
    arbol.inorden(cout);

    cout << endl << "******* Mostrando DNIs cualesquiera: *******" << endl;
    for (unsigned i = 0; i < 3; i++)
    {
        Alumno alumno;
        cout << "Persona con DNI " << searchdnis[i] << endl;
        if (arbol.buscar(searchdnis[i], alumno))
            cout << alumno << endl;
        else
            cout << "*** NO ENCONTRADO" << endl << endl;
    }

    cout << endl << "******* Mostrando DNIs que empiezan con ocho: *******" << endl;
    cout << "DNIs que empiezan con ocho: " << arbol.cuentaDNI8() << endl;
}
