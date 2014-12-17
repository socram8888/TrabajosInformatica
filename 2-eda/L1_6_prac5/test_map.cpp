
#include <iostream>
#include <map>
#include "alumno.h"
using namespace std;

int main()
{
    map<string, Alumno> mapa;
    string searchdnis[3];

    for (unsigned i = 0; i < 1000; i++)
    {
        Alumno alumno = Alumno(5);

        // Guardar dos DNIs cualquiera para buscarlos despues
        if (i % 500 == 0) {
            searchdnis[i / 500] = alumno.getDNI();
        }

        mapa[alumno.getDNI()] = alumno;
    }
    searchdnis[2] = "999999999NX";

    cout << "******* Mostrando en orden: *******" << endl;
    for (map<string, Alumno>::iterator it = mapa.begin(); it != mapa.end(); ++it)
        cout << it->second;

    cout << endl << "******* Mostrando DNIs cualesquiera: *******" << endl;
    for (unsigned i = 0; i < 3; i++)
    {
        Alumno alumno;
        cout << "Persona con DNI " << searchdnis[i] << endl;
        map<string, Alumno>::iterator it = mapa.find(searchdnis[i]);
        if (it != mapa.end())
            cout << it->second << endl;
        else
            cout << "*** NO ENCONTRADO" << endl << endl;
    }

    cout << endl << "******* Mostrando DNIs que empiezan con ocho: *******" << endl;
    for (map<string, Alumno>::iterator it = mapa.begin(); it != mapa.end(); ++it)
        if (it->second.getDNI()[0] == '8')
            cout << it->second;
}
