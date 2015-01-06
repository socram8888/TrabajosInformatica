/*******************************************************************/
/* Asignatura: Programación                                        */
/* Curso 2013-2014                                                 */
/* Práctica 7: Colas                                               */
/*                                                                 */
/* Clase Alumno.                                                   */
/*                                                                 */
/*******************************************************************/

#include "alumno.h"
#include <cstring>

using namespace std;
Alumno::Alumno()
{    
}

Alumno::Alumno(string nombre, string asignatura, int grupo)
{
    this->nombre = nombre;
    this->asignatura = asignatura;
    this->grupo = grupo;
}

string Alumno::dameNombre(void)
{
    return nombre;
}

string Alumno::dameAsignatura(void)
{
    return asignatura;
}

int Alumno::dameGrupo(void)
{
    return grupo;
}

ostream& operator << (ostream &out, const Alumno &a)
{
    out << a.nombre << " " << a.asignatura << " " << a.grupo;
    return out;
}


