
/**
 * Prueba general de la pila
 * @author Marcos Vives Del Sol
 */

#include "pila.h"
#include <iostream>
using namespace std;

int main()
{
    int i;
    Pila pila = Pila(10);

    try {
        cout << "Desapilar elemento... ";
        pila.desapilar();
        cout << "Exito" << endl;
    }
    catch (exception &err)
    {
        cout << "Cazado error: " << err.what() << endl;
    }

    for (i = 1; i <= 11; i++)
    {
        try {
            cout << "Insertar numero " << i << "... ";
            pila.apilar(i);
            cout << "Exito" << endl;
        }
        catch (exception &err)
        {
            cout << "Cazado error: " << err.what() << endl;
        }
    }

    cout << "Mostrando la pila:" << endl;
    pila.mostrar();

    cout << "Accesos realizados: " << pila.getAccesos() << endl;

    return 0;
}
