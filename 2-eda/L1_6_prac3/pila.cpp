
/**
 * Implementación de pila
 * @author Marcos Vives Del Sol
 */

#include "pila.h"
#include "error.h"
#include <string.h>
#include <iostream>
using namespace std;

Pila::Pila(unsigned int newSize)
{
    count = 0;
    size = newSize;
    accesses = 0;
    buffer = new int[newSize];
}

Pila::Pila(const Pila &pila)
{
    count = pila.count;
    size = pila.size;
    accesses = pila.accesses;
    buffer = new int[size];

    memcpy(buffer, pila.buffer, pila.count * sizeof(int));
}

Pila::~Pila()
{
    delete [] buffer;
}

const Pila& Pila::operator=(const Pila &pila)
{
    this->count = pila.count;
    this->size = pila.size;
    this->accesses = pila.accesses;

    if (size != pila.size) {
        delete buffer;
        buffer = new int[size];
    }
    memcpy(buffer, pila.buffer, pila.count * sizeof(int));

    return *this;
}

void Pila::apilar(int dato)
{
    accesses++;

    if (count == size) {
        throw ErrorPilaLlena();
    }

    buffer[count++] = dato;
}

int Pila::desapilar()
{
    accesses++;

    if (count == 0) {
        throw ErrorPilaVacia();
    }

    return buffer[--count];
}

int Pila::cima()
{
    accesses++;

    if (count == 0) {
        throw ErrorPilaVacia();
    }

    return buffer[count - 1];
}

bool Pila::vacia()
{
    return count == 0;
}

unsigned int Pila::getAccesos()
{
    return accesses;
}

void Pila::resetAccesos()
{
    accesses = 0;
}

void Pila::mostrar()
{
    unsigned int i;

    cout << "Pila: [ ";
    for (i = 0; i < count; i++) {
        if (i != 0)
            cout << ", ";
        cout << buffer[i];
    }
    cout << " ]" << endl;
}
