/*******************************************************************/
/* Asignatura: Programaci�n                                        */
/* Curso 20011-2012                                                */
/* Practica 7: Colas                                               */
/*                                                                 */
/* Clase Cola de Alumnos.                                          */
/*                                                                 */
/*******************************************************************/

#ifndef COLA_H
#define COLA_H

#include <string>
#include <iostream>

using namespace std;

struct Nodo;
typedef Nodo* Puntero;
struct Nodo
{
    Alumno info;
    Puntero sig;
};

class Cola
{
    public:
        /*************** Constructor por defecto **************************
         *  Descripcion:  inicializa todas las variables necesarioas para
         *                instanciar el objeto
         ******************************************************************/
         Cola();

        /*************** Destructor ***************************************
         *  Descripcion: Libera la memoria usada por el objeto
         ******************************************************************/
        ~Cola();                            	

        /******************************************************************
         *  Descripcion: Inserta un elemento en la cola
         *  Devuelve: true si funciona adecuadamente o false si hay un error            
         ******************************************************************/
        bool Encolar(Alumno a);
        
        /******************************************************************
         *  Descripcion: Extrae un elemento de la cola
         *  Devuelve: true si extr�e un elemento o false si la cola est� 
         *            vac�a
         ******************************************************************/
	 bool DesEncolar(void);
	
        /******************************************************************
         *  Descripcion: Devuelve el n�mero de elementos encolados
         *  Devuelve: el n�mero de elementos (0 si est� vac�a)
         ******************************************************************/
	int Elementos(void);
	
        /******************************************************************
         *  Descripcion: Muestra el contenido de todos los elementos de la
         *               cola
	 *  Devuelve: nada             
         ******************************************************************/
	void Mostrar(void);
	
        /******************************************************************
         *  Descripcion: Elimina todos los elementos de la cola
         *  Devuelve: N�mero de elementos eliminados.            
         ******************************************************************/
	int Vaciar(void);

        /******************************************************************
         *  Descripcion: Devuelve el elemento en la cabeza de la cola
         *  Devuelve: true si hay un elemento o false si la cola est� vac�a.    
         ******************************************************************/
	bool VerPrimero(Alumno &a);

        /******************************************************************
         *  Descripcion: Devuelve el �ltimo elemento de la cola. 
         *  Devuelve: true si hay un elemento o false su la cola est� vac�a
         ******************************************************************/
	bool VerUltimo(Alumno &a);

        /******************************************************************
         *  Descripcion: Devuelve el elemento en la posici�n pos a contar
	     *               desde el comienzo de la cola.
         *  Devuelve: true si hay un elemento o false si la cola est� vac�a.
         ******************************************************************/
	bool VerPosicion(int pos, Alumno &a);

        /******************************************************************
         *  Descripcion: Elimina el elemento en la posicion dada
         *  Devuelve: true si hay un elemento o false si la cola est� vac�a.
         ******************************************************************/
	bool EliminaPosicion(int pos);
	
        /******************************************************************
         *  Descripcion: Operador =
         *              
         ******************************************************************/

    const Cola& operator=(const Cola &cola);

        /******************************************************************
         *  Descripcion: Operador <<
         *              
         ******************************************************************/

    friend ostream& operator<<(ostream &, const Cola &cola);
		
    private:
    	// Incluir aqu� los atributos necesarios opara la implementaci�n
    	// de la funcionalidad
    	Puntero inicio, fin;
};

#endif // COLA_H

