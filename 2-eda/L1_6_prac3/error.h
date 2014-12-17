
/**
 * Excepciones
 * @author Marcos Vives Del Sol
 */

#ifndef HAVE_EDA_ERROR_H
#define HAVE_EDA_ERROR_H

#include <stdexcept>
using namespace std;

class ErrorPilaVacia : public out_of_range
{
    public:
        ErrorPilaVacia() : out_of_range("La pila esta vacia") {}
};

class ErrorPilaLlena : public out_of_range
{
    public:
        ErrorPilaLlena() : out_of_range("La pila esta llena") {}
};

#endif
