
#include "abb.h"

#define min(a, b) (a < b ? a : b)
#define max(a, b) (a > b ? a : b)

/**
 * Implementacion del arbol binario de busqueda
 * @author Marcos Vives Del Sol
 */

/**
 * Construye un ABB vacio
 */
ABB::ABB()
{
    miRaiz = NULL;
}

/**
 * Destructor del ABB. Borra los nodos y su contenido.
 */
ABB::~ABB()
{
    if (miRaiz != NULL)
        delete miRaiz;
}

/**
 * Busca un elemento asociado a una clave.
 * @param clave Clave
 * @param dato Salida
 * @return Verdadero si se ha encontrado el elemento
 */
bool ABB::buscar(const TipoClave& clave, TipoDato& dato) const
{
    return buscarAux(miRaiz, clave, dato);
}

/**
 * Busca un elemento asociado a una clave.
 * @param nodo Nodo actual
 * @param clave Clave
 * @param dato Salida
 * @return Verdadero si se ha encontrado el elemento
 */
bool ABB::buscarAux(PtrNodoBin nodo, const TipoClave& clave, TipoDato& dato) const
{
    if (nodo == NULL)
        return false;

    if (clave < nodo->clave)
        return buscarAux(nodo->izq, clave, dato);

    if (clave > nodo->clave)
        return buscarAux(nodo->der, clave, dato);

    dato = nodo->dato;
    return true;
}

/**
 * Inserta un elemento dada una clave.
 * @param clave Clave
 * @param dato Dato a almacenar
 * @return Verdadero si el dato no se encontraba ya en el ABB
 */
bool ABB::insertar(const TipoClave& clave, const TipoDato& dato)
{
    return insertarAux(miRaiz, clave, dato);
}

/**
 * Inserta un elemento dada una clave.
 * @param nodo Nodo actual
 * @param clave Clave
 * @param dato Dato a almacenar
 * @return Verdadero si el dato no se encontraba ya en el ABB
 */
bool ABB::insertarAux(PtrNodoBin& nodo, const TipoClave& clave, const TipoDato& dato)
{
    if (nodo == NULL)
    {
        nodo = new NodoBin(clave, dato);
        return true;
    }

    if (clave < nodo->clave)
        return insertarAux(nodo->izq, clave, dato);

    if (clave > nodo->clave)
        return insertarAux(nodo->der, clave, dato);

    return false;
}

/**
 * Escribe los elementos en orden natural al flujo de salida.
 * @param sal Flujo de salida
 */
void ABB::inorden(ostream& sal) const
{
    inordenAux(sal, miRaiz);
}

/**
 * Escribe los elementos en orden natural al flujo de salida.
 * @param sal Flujo de salida
 * @param nodo Nodo actual
 */
void ABB::inordenAux(ostream& sal, PtrNodoBin nodo) const
{
    if (nodo != NULL)
    {
        inordenAux(sal, nodo->izq);
        sal << nodo->dato;
        inordenAux(sal, nodo->der);
    }
}

/**
 * @return Altura del ABB
 */
unsigned ABB::altura() const
{
    return alturaAux(miRaiz, 0);
}

/**
 * @param nodo Nodo actual
 * @param altura Altura del nodo actual
 * @return Altura desde el nodo actual hasta el mas alejado
 */
unsigned ABB::alturaAux(PtrNodoBin nodo, unsigned altura) const
{
    if (nodo == NULL)
        return altura;

    altura++;
    int altIzq = alturaAux(nodo->izq, altura);
    int altDer = alturaAux(nodo->der, altura);

    return max(altIzq, altDer);
}

/**
 * @return Verdadero si el ABB no contiene nada
 */
bool ABB::vacio() const
{
    return miRaiz == NULL;
}

/**
 * @return Numero de datos cuyo DNI empieza por ocho.
 */
unsigned ABB::cuentaDNI8() const
{
    return cuentaDNI8Aux(miRaiz);
}

/**
 * @param nodo Nodo actual
 * @return Numero de datos cuyo DNI empieza por ocho en el nodo actual e hijos
 */
unsigned ABB::cuentaDNI8Aux(PtrNodoBin nodo) const
{
    unsigned found = 0;

    if (nodo != NULL)
    {
        char firstChar = nodo->clave[0];

        if (firstChar == '8') {
            found++;
        }

        if (firstChar >= '8') {
            found += cuentaDNI8Aux(nodo->izq);
        }

        if (firstChar <= '8') {
            found += cuentaDNI8Aux(nodo->der);
        }
    }

    return found;
}

/**
 * @return Tamano del arbol
 */
unsigned int ABB::tam() const
{
    return tamAux(miRaiz);
}

/**
 * @param nodo Nodo actual
 * @return Tamano del nodo e hijos
 */
unsigned int ABB::tamAux(PtrNodoBin nodo) const
{
    if (nodo == NULL)
        return 0;

    return 1 + tamAux(nodo->izq) + tamAux(nodo->der);
}

/**
 * Destructor de un nodo
 */
ABB::NodoBin::~NodoBin()
{
    if (this->izq != NULL)
        delete this->izq;
    if (this->der != NULL)
        delete this->der;
}
