/**
 * Arbol Binario de Búsqueda (ABB)
 * Curso 2014/2015
 */

#ifndef _ABB_H
#define _ABB_H

#include <iostream>
#include <string>
#include "alumno.h"
using namespace std;

class ABB
{
public:
    typedef string TipoClave;
    typedef Alumno TipoDato;

    ABB(); 
    ~ABB();
    bool buscar(const TipoClave &, TipoDato&) const; 
    bool insertar(const TipoClave &, const TipoDato&); 
    bool vacio() const;
    void inorden(ostream & sal) const;
    unsigned altura() const;
    unsigned cuentaDNI8() const;
    unsigned tam() const;

private:
    class NodoBin
    {
    public:
        TipoClave clave; 
        TipoDato dato;
        NodoBin * izq;
        NodoBin * der;

        NodoBin(): izq(NULL), der(NULL) {};
        NodoBin(TipoClave c, TipoDato d)
        : clave(c), dato(d), izq(NULL), der(NULL) {};
        ~NodoBin();
    };

    typedef NodoBin * PtrNodoBin;

    bool buscarAux(PtrNodoBin, const TipoClave &, TipoDato&) const;
    bool insertarAux(PtrNodoBin &, const TipoClave &, const TipoDato&);
    void inordenAux(ostream & sal, PtrNodoBin) const;
    unsigned alturaAux(PtrNodoBin, unsigned) const;
    unsigned cuentaDNI8Aux(PtrNodoBin) const;
    unsigned tamAux(PtrNodoBin) const;

    PtrNodoBin miRaiz;
};

#endif
