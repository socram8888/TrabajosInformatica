/*******************************************************************/
/* Asignatura: Programación                                        */
/* Curso 2013-2014                                                 */
/* Practica 7: Colas                                               */
/*                                                                 */
/* Clase Alumno.                                                   */
/*                                                                 */
/*******************************************************************/

#ifndef ALUMNO_H
#define ALUMNO_H

#include <string>
#include <iostream>

using namespace std;

class Alumno
{
    public:
    Alumno ();
    /*************** Constructor con parametros ****************
     *  Descripcion:  inicializa código y nombre con los 
     *                valores proporcionados
     ***********************************************************/
    Alumno(string, string, int);
        
    /*************** dameNombre() ******************************
     *  Descripcion:  Devuelve el atributo nombre
     *  Valor devuelto:
     *  string, nombre del alumno
     ***********************************************************/
    string dameNombre(void);
       
     /*************** dameAsignatura() ******************************
     *  Descripcion:  Devuelve el atributo asignatura
     *  Valor devuelto:
     *  string, nombre de la asignatura
     ***********************************************************/
    string dameAsignatura(void);

    /*************** dameGrupo() ******************************
     *  Descripcion:  Devuelve el atributo grupo
     *  Valor devuelto:
     *  int, grupo al que pertenece el alumno
     ***********************************************************/
    int dameGrupo(void);

    /***********************************************************
     *  Descripcion:  Sobrecarga del operador << para mostrar
     *  la información del objeto
     ***********************************************************/
    friend ostream& operator << (ostream &o, const Alumno &a);

private:
    string nombre;     // Nombre del alumno
    string asignatura; // Asignatura
    int grupo;         // Grupo al que pertenece el alumno

};

#endif // ALUMNO_H

