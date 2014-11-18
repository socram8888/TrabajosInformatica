
#include "Atleta.h"
#include "setget.h"
#include "timeparser.h"
#include "menu.h"

Atleta::Atleta() {
	inicializar("", 0, DESCONOCIDO, 0, 0);
}

void Atleta::inicializar(string nombre, int dorsal, Sexo sexo, int edad, int tiempo)
{
    asignaNombre(nombre);
    asignaDorsal(dorsal);
    asignaSexo(sexo);
    asignaEdad(edad);
    asignaTiempo(tiempo);
}

// Estas funciones son expandidas por el preprocesador de C++ a getters y setters para cada una de las variables
// Equivalente al @Getter @Setter del Project Lombok para Java
SETGET(Atleta, string, Nombre, nombre);
SETGET(Atleta, uint, Dorsal, dorsal);
SETGET(Atleta, Sexo, Sexo, sexo);
SETGET(Atleta, uint, Edad, edad);
SETGET(Atleta, uint, Tiempo, tiempo);

static const string CATEGORIAS[][2] = {
    { "Junior masculino", "Junior femenino" },
    { "Senior masculino", "Senior femenino" },
    { "Veterano", "Veterana" }
};

const string& Atleta::devuelveCategoria()
{
    int id;
    if (_edad < 20)
        id = 0;
    else if (_edad < 35)
        id = 1;
    else
        id = 2;

    return CATEGORIAS[id][_sexo == FEMENINO ? 1 : 0];
}

ostream& operator<<(ostream& salida, Atleta &atleta)
{
	salida << "Nombre: " << atleta.devuelveNombre() << endl
			<< "Dorsal: " << atleta.devuelveDorsal() << endl
			<< "Sexo: " << sexo_a_string(atleta.devuelveSexo()) << endl
			<< "Edad: " << atleta.devuelveEdad() << " anyos" << endl;

	if (atleta.devuelveTiempo() > 0)
		salida << "Tiempo: " << segundos_a_tiempo(atleta.devuelveTiempo()) << endl;

	return salida;
}

bool gui_read_atleta(uint depth, Atleta &atleta)
{
	gui_header(depth, "Introduccion del atleta");

    string nombre;
    uint dorsal;
    Sexo sexo;
    uint edad;

	bool ok =
		gui_read_string(depth + 1, "Nombre", nombre) &&
		gui_read_sex(depth + 1, sexo) &&
		gui_read_uint(depth + 1, "Edad", edad);

	if (ok)
	{
		atleta.asignaNombre(nombre);
		atleta.asignaSexo(sexo);
		atleta.asignaEdad(edad);
	}

	return ok;
}
