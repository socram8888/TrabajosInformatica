/*******************************************************************/
/* Asignatura: Programación                                        */
/* Curso 2013-2014                                                 */
/* Practica 7                                                      */
/* Colas                                                           */
/*                                                                 */
/* Programa principal de prueba de la clase Cola.                  */
/*                                                                 */
/*******************************************************************/

#include "alumno.h"
#include "cola.h"
#include "menu.h"
#include "sysdep.h"
#include <strings.h> // strcasecmp
#include <sstream> // ostringstream
using namespace std;

struct Contexto
{
    Cola cola;
    bool salir;    
};

void VerLista(void * voidctx)
{
    Contexto * ctx = (Contexto *) voidctx;

    gui_header(1, "Alumnos en la lista:\n");
    cout << ctx->cola;
    gui_pause(); 
}

void CitaNueva(void * voidctx)
{
    Contexto * ctx = (Contexto *) voidctx;

	string nombre, asignatura;
	int grupo;

    if (
		gui_read_string(1, "Nombre", nombre) &&
		gui_read_string(1, "Asignatura", asignatura) &&
		gui_read_int(1, "Grupo", grupo)
	) {
		Alumno alumno = Alumno(nombre, asignatura, grupo);
		ctx->cola.Encolar(alumno);
	}
}

void ExtraerCita(void * voidctx)
{
    Contexto * ctx = (Contexto *) voidctx;

    if (ctx->cola.DesEncolar()) {
		gui_error(1, "Se ha desencolado correctamente");
	} else {
		gui_error(1, "No se ha podido desencolar");
	}
}

void EliminarCita(void * voidctx)
{
    Contexto * ctx = (Contexto *) voidctx;
	string nombre, info;
	int i = 0;
	int elims = 0;
	Alumno alumno;

	if (gui_read_string(1, "Nombre", nombre))
	{
		while (ctx->cola.VerPosicion(i, alumno))
		{
			if (strcasecmp(alumno.dameNombre().c_str(), nombre.c_str()) == 0)
			{
				ctx->cola.EliminaPosicion(i);
				elims++;
			}
			i++;
		}

		ostringstream oss;
		oss << "Se han eliminado " << elims << " cita(s)";
		gui_error(1, oss.str());
	}
	else
		gui_error(1, "Nombre no valido");
}

void BorrarCitas(void * voidctx)
{
    Contexto * ctx = (Contexto *) voidctx;
    ctx->cola.Vaciar();

    gui_header(1, "Se han eliminado todas las citas pendientes");
    gui_pause();
}

void Terminar(void * voidctx)
{
    Contexto * ctx = (Contexto *) voidctx;
    ctx->salir = true;
}

MENU_MAKE(MENU_MAIN, "Menu Principal",
    _({ "Ver la lista completa de citas", VerLista }),
    _({ "Nueva cita", CitaNueva }),
    _({ "Extraer una cita", ExtraerCita }),
    _({ "Eliminar una cita (por nombre de alumno)", EliminarCita }),
    _({ "Borrar todas las citas", BorrarCitas }),
    _({ "Terminar", Terminar })
);

int main()
{
    Contexto ctx;
    ctx.salir = false;

    do {
        display_clear();
		gui_tab(1);
		cout << "Tiempo estimado de duracion de tutorias: " << ctx.cola.Elementos() * 15 << " minutos\n\n";
        gui_menu(0, MENU_MAIN, &ctx);
    } while (!ctx.salir);

    return 0;
}


