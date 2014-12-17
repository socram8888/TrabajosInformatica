
/**
 * Implementacion de la tabla
 * @author Marcos Vives
 */

#include "tabla.h"

/**
 * Crea una tabla con un numero dado de slots
 * @param size Numero de slots
 */
Tabla::Tabla(unsigned size)
{
	t = vector<ListaDatos>(size);
}

/**
 * Busca un elemento dado un DNI
 * @param dni DNI del alumno
 * @param salida Alumno, si se encuentra
 * @return true si ha sido encontrado
 */
bool Tabla::buscar(TipoClave dni, TipoDato& salida) const
{
	const ListaDatos& datos = t[hash(dni)];

	for (unsigned i = 0; i < datos.size(); i++)
	{
		const Alumno& alumno = datos[i];
		if (alumno.getDNI() == dni)
		{
			salida = alumno;
			return true;
		}
	}

	return false;
}

/**
 * Inserta un elemento dado un DNI
 * @param dni DNI del alumno
 * @param alumno Alumno
 */
void Tabla::insertar(TipoClave dni, const TipoDato& alumno)
{
	unsigned hashDni = hash(dni);
	t[hashDni].push_back(alumno);
}

/**
 * Calcula el hashcode de una clave
 * @param str Clave
 * @return Hashcode
 */
unsigned Tabla::hash(TipoClave str) const
{
    unsigned h = 0;
    unsigned len = str.size();

    for (size_t pos = 0; pos < len; pos++)
        h = h * 31 + (int) str[pos];

    return h % t.size();
}

/**
 * Muestra el contenido de cada slot
 * @param sal Stream de salida
 */
void Tabla::mostrar(ostream & sal) const
{
	for (unsigned slot = 0; slot < t.size(); slot++)
	{
		ListaDatos datos = t[slot];
		sal << "-=-=- Datos en slot " << slot << ": " << datos.size() << " elementos -=-=-" << endl;
		for (unsigned elem = 0; elem < datos.size(); elem++)
			sal << datos[elem];
	}
}

/**
 * Calcula el factor de carga de esta tabla
 * @return Factor de carga
 */
float Tabla::factorCarga() const
{
	unsigned elems = 0;
	unsigned slots = t.size();

	for (unsigned i = 0; i < slots; i++)
		elems += t[i].size();

	return (float) elems / (float) slots;
}

/**
 * Calcula el número de slots vacíos
 * @return Slots vacíos
 */
unsigned Tabla::posLibres() const
{
	unsigned libres = 0;

	for (unsigned i = 0; i < t.size(); i++)
		if (t[i].empty())
			libres++;

	return libres;
}
