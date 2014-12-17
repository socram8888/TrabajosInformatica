
/**
 * Prueba con funciones de recursividad
 * @author Marcos Vives Del Sol
 */

#include "pila.h"
#include "error.h"
#include <iostream>
using namespace std;

/**
 * Calcula la altura de la pila dada.
 * @param pila La pila
 * @return La altura
 */
int altura(Pila pila)
{
    if (pila.vacia())
        return 0;

    pila.desapilar();
    return altura(pila) + 1;
}

/**
 * Calcula la altura de la pila dada.
 * @param pila La pila
 * @return La altura
 */
int altura2(Pila &pila)
{
    if (pila.vacia())
        return 0;

    pila.desapilar();
    return altura(pila) + 1;
}

/**
 * Suma el valor de los enteros de la pila.
 * @param pila La pila
 * @return La suma de los enteros.
*/
int suma(Pila &pila)
{
    if (pila.vacia())
        return 0;

    return pila.desapilar() + suma(pila);
}

/**
 * Suma el valor de los enteros de la pila en posición par.
 * @param pila La pila
 * @return La suma de los enteros.
*/
int sumaPares(Pila &pila)
{
    try
    {
        pila.desapilar();
        return pila.desapilar() + sumaPares(pila);
    }
    catch (ErrorPilaVacia& err) { }

    return 0;
}

/**
 * Borra todas las apariciones de un elemento en la pila.
 * @param pila La pila original
 * @param dato El elemento a borrar
 * @return La pila modificada
 */
Pila borrar(Pila pila, int dato)
{
    int extraido;

    if (!pila.vacia())
    {
        extraido = pila.desapilar();
        pila = borrar(pila, dato);
        if (extraido != dato)
            pila.apilar(extraido);
    }

    return pila;
}

int main()
{
    int i, j;
    Pila pila = Pila(64);
    Pila clon = Pila(pila);

    // Llena la pila con 10 números: 1, 2, 2, 3, 3, 3, 4, 4, 4, 4 (i veces i)
    for (i = 1; i <= 4; i++)
    {
        for (j = 0; j < i; j++)
        {
            pila.apilar(i);
        }
    }
    cout << "Pila de prueba: " << endl;
    pila.mostrar();
    cout << endl;

    cout << "altura(pila): " << altura(pila) << endl;

    clon = pila;
    cout << "altura2(pila): " << altura2(clon) << endl;

    clon = pila;
    cout << "suma(pila): " << suma(clon) << endl;

    clon = pila;
    cout << "sumaPares(pila): " << sumaPares(clon) << endl;

    cout << "Pila sin 3s: " << endl;
    clon = borrar(pila, 3);
    clon.mostrar();

    return 0;
}
