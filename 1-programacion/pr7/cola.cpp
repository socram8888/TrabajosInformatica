/*******************************************************************/
/* Asignatura: Programación                                        */
/* Curso 2013-2014                                                 */
/* Practica 7: Colas                                               */
/*                                                                 */
/* Clase Cola de Alumnos.                                          */
/*                                                                 */
/*******************************************************************/

#include "alumno.h"
#include "cola.h"
#include <iostream>

using namespace std;

        /******************************************************************
         *  Descripcion: Constructor de la clase
         *  Devuelve: 
         ******************************************************************/
Cola::Cola()
{
    inicio = NULL;
    fin = NULL;
}

        /******************************************************************
         *  Descripcion: Destructor de la clase
         *  Devuelve: 
         ******************************************************************/
Cola::~Cola()
{
    Vaciar();
}

        /******************************************************************
         *  Descripcion: Inserta un elemento en la cola
         *  Devuelve: true si funciona adecuadamente o false si hay un error            
         ******************************************************************/
bool Cola::Encolar(Alumno a)
{
	Puntero p_aux;
	p_aux = new Nodo;
	p_aux->info = a;
	p_aux->sig = NULL;
	
	if (inicio == NULL)
		inicio = p_aux;
	else
		fin->sig = p_aux;
	fin = p_aux;

    return true;
}
        
        /******************************************************************
         *  Descripcion: Extrae un elemento de la cola
         *  Devuelve: true si extráe un elemento o false si la cola está vacía
         ******************************************************************/
bool Cola::DesEncolar(void)
{
    bool ok;
	Puntero p_aux;
	
	if (inicio == NULL)
		ok = false;
	else
	{
		p_aux = inicio;
		inicio = inicio->sig;
		if (inicio == NULL)
			fin = NULL;
		delete p_aux;
		ok = true;
	}
	return ok;
}
	
        /******************************************************************
         *  Descripcion: Devuelve el número de elementos encolados
         *  Devuelve: el número de elementos (0 si está vacía)
         ******************************************************************/
int Cola::Elementos(void)
{
    Puntero p_aux;
    int cont = 0;
    p_aux = inicio;
    
    while(p_aux != NULL)
    {
        cont++;
        p_aux = p_aux->sig;
    }
    return cont;
}
	
        /******************************************************************
         *  Descripcion: Muestra el contenido de todos los elementos de la
         *               cola
	 *  Devuelve: nada             
         ******************************************************************/
void Cola::Mostrar(void)
{
    Puntero p_aux;
    p_aux = inicio;
    
    while (p_aux != NULL)
    {
        cout << p_aux -> info << endl;
        p_aux = p_aux -> sig;
    }
}
	
        /******************************************************************
         *  Descripcion: Elimina todos los elementos de la cola
         *  Devuelve: Número de elementos eliminados.            
         ******************************************************************/
int Cola::Vaciar(void)
{
    while(DesEncolar());
}
        /******************************************************************
         *  Descripcion: Devuelve el elemento en la cabeza de la cola
         *  Devuelve: true si hay un elemento o false si la cola está vacía.         
         ******************************************************************/
bool Cola::VerPrimero(Alumno &a)
{
    bool ok;
	if (inicio == NULL)
		ok = false;
	else
	{
		a = inicio->info;
		ok = true;
	}
	return (ok);
}

        /******************************************************************
         *  Descripcion: Devuelve el último elemento de la cola. 
         *  Devuelve: true si hay un elemento o false si la cola está vacía
         ******************************************************************/
bool Cola::VerUltimo(Alumno &a)
{
    bool ok;
	if (fin == NULL)
		ok = false;
	else
	{
		a = fin->info;
		ok = true;
	}
	return (ok);
}

        /******************************************************************
         *  Descripcion: Devuelve el elemento en la posición pos a contar
	 *               desde el comienzo de la cola.
         *  Devuelve: true si hay un elemento o false si la cola está vacía.
         ******************************************************************/
bool Cola::VerPosicion(int pos, Alumno &a)
{
    Puntero p_aux;
    int cont = 0;
    bool ok = false;
    
    p_aux = inicio;
     while (p_aux != NULL && cont < pos)
     {
        cont++;
        p_aux = p_aux-> sig;        
    }
    
    if(p_aux != NULL)
    {
        a = p_aux-> info;
        ok = true;    
    }
    return ok;
}

        /******************************************************************
         *  Descripcion: Devuelve el elemento en la posición pos a contar
	     *               desde el comienzo de la cola.
         *  Devuelve: true si hay un elemento o false si la cola está vacía.
         ******************************************************************/
bool Cola::EliminaPosicion(int pos)
{
    Puntero p_aux, anterior;
    int cont = 0;
    bool ok = false;

	anterior = NULL;
    p_aux = inicio;
    while (p_aux != NULL && cont < pos)
    {
        cont++;
		anterior = p_aux;
        p_aux = p_aux->sig;        
    }
    
    if(p_aux != NULL)
    {
		if (anterior != NULL)
			anterior->sig = p_aux->sig;
		else
			inicio = p_aux->sig;
        delete p_aux;
        ok = true;
    }
    return ok;
}

        /******************************************************************
         *  Descripcion: Operador =
         *              
         ******************************************************************/

const Cola& Cola::operator=(const Cola &cola)
{
    Vaciar();
    Puntero pto = cola.inicio;
    while (pto != NULL)
    {
        Encolar(pto->info);
        pto = pto->sig;
    }

    return *this;
}
	
        /******************************************************************
         *  Descripcion: Operador <<
         *              
         ******************************************************************/

ostream& operator<<(ostream &out, const Cola &cola)
{
    Puntero pto = cola.inicio;
    while (pto != NULL)
    {
        out << pto->info << endl;
        pto = pto->sig;
    }
}		
