/**
 * Implementacion de la clase Alumno
 * Curso 2014/2015
 */

#include "alumno.h"
#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <sstream>

using namespace std;

// Nombres de ejemplo
string Alumno::list_nombre[] = {
    "Javier",
    "Jorge",
    "Angel",
    "Raul",
    "Jose",
    "Arturo",
    "Jose Antonio",
    "Julio",
    "Beatriz",
    "Ismael",
    "Oliver",
    "Carlos",
    "Alberto",
    "Francisco Manuel",
    "Lluis Carles"
};

// Apellidos de ejemplo
string Alumno::list_apellido[] = {
    "Albaladejo" ,
    "Albiach" ,
    "Aldana" ,
    "Alonso" ,
    "Anda" ,
    "Andres" ,
    "Angel" ,
    "Aranda" ,
    "Bernal" ,
    "Bonell" ,
    "Calderon" ,
    "Chakkour" ,
    "Contreras" ,
    "Correa" ,
    "Dacasa"
};

/**
 * Constructor Alumno.
 * Genera un alumno con datos aleatorios excepto el curso, que se pasa como par?metro.
 * @param curs curso del alumno
 */
Alumno::Alumno(unsigned curs): curso(curs)
{
    unsigned num = rand() % 100000000;
    stringstream s;
    s << num;
    string letra;
    letra.push_back( rand() % (90-65+1) + 65 ); // A 65, Z 90
    dni = s.str() + letra;
    nombre = list_nombre[ rand() % NUM_NOMBRE];
    apellidos = list_apellido[ rand() % NUM_NOMBRE];
    telefono = rand() % 100000000 + 600000000;
}

/**
 * Escribe el alumno en un stream de salida
 * @param out Stream de salida
 * @param alu alumno a escribir
 */
ostream & operator<<(ostream & out, const Alumno & alu)
{
    const string tab = "    ";
    out << "==================================" << endl;
    out << tab << "DNI: " << alu.dni << endl;
    out << tab << "Nombre: " << alu.nombre << tab << alu.apellidos << endl;;
    out << tab << "Curso: " << alu.curso;
    out << tab << "Telefono: " << alu.telefono << endl;
    out << "==================================" << endl;
    return out;
}
