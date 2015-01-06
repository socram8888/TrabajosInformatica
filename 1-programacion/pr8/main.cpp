
#include "ListaAtleta.h"
#include "menu.h"
#include "sysdep.h"
#include <iostream>
using namespace std;

struct Contexto {
	ListaAtleta listaApuntados;
	ListaAtleta listaTiempos;
	bool salir;
};

void menu_inscribe(void * voidctx)
{
	Contexto* ctx = (Contexto*) voidctx;
	Atleta atleta;
	Atleta otro;

	if (gui_read_atleta(1, atleta))
	{
		int pos = ctx->listaApuntados.buscarPorNombre(atleta.devuelveNombre());
		if (pos >= 0)
		{
			gui_error(1, "Ya existe un corredor con el mismo nombre");
		} else {
			uint elem = ctx->listaApuntados.cantidad();
			ctx->listaApuntados.sacar(elem - 1, otro);
			atleta.asignaDorsal(otro.devuelveDorsal() + 1);
			ctx->listaApuntados.introducir(elem, atleta);
		}
	}
}

void menu_erase(void * voidctx)
{
	Contexto* ctx = (Contexto*) voidctx;
	string nombre;

	if (gui_read_string(1, "Nombre", nombre))
	{
		int pos = ctx->listaApuntados.buscarPorNombre(nombre);
		if (pos >= 0)
		{
			ctx->listaApuntados.borrar(pos);
			gui_error(1, "Eliminado correctamente");
		} else {
			gui_error(1, "No se ha encontrado nadie con el nombre introducido");
		}
	}
}

void menu_view(void * voidctx)
{
	Contexto* ctx = (Contexto*) voidctx;

	cout << ctx->listaApuntados;
	gui_pause();
}

void menu_exit(void * voidctx)
{
	Contexto* ctx = (Contexto*) voidctx;
	ctx->salir = true;
}

MENU_MAKE(MENU_PRINCIPAL, "CARRERA POPULAR - INSCRIPCION",
_({"Inscribir un atleta", menu_inscribe}),
_({"Borrar un atleta", menu_erase}),
_({"Ver los aletas inscritos", menu_view}),
_({"Salir", menu_exit})
);

/*
MENU_MAKE(MENU_TIEMPOS, "CARRERA POPULAR - TIEMPOS Y CLASIFICACION",
_({"Ingresar tiempo del atleta ", menu_time_enter}),
_({"Ver clasificación general ", menu_time_classification}),
_({"Mostrar ganador por categoria", menu_time_by_cat}),
_({"Salir", menu_exit})
);
*/

int main()
{
	Contexto ctx;
	ctx.salir = false;

	while (!ctx.salir)
	{
		display_clear();
		gui_menu(0, MENU_PRINCIPAL, &ctx);
	}

	while (!ctx.salir)
	{
		//gui_menu(0, MENU_TIEMPOS, ctx);
	}

	return 0;
}
