
#include "sexo.h"
#include "menu.h"

string sexo_a_string(Sexo sexo) {
	if (sexo == MASCULINO)
		return "masculino";
	if (sexo == FEMENINO)
		return "femenino";
	return "indeterminado";
}

void gui_read_sex_male(void * sexovoid)
{
	*((Sexo *) sexovoid) = MASCULINO;
}

void gui_read_sex_female(void * sexovoid)
{
	*((Sexo *) sexovoid) = FEMENINO;
}

MENU_MAKE(MENU_SEXO, "Sexo",
_({"Masculino", gui_read_sex_male}),
_({"Femenino", gui_read_sex_female})
);

bool gui_read_sex(uint depth, Sexo &sexo)
{
	gui_menu(depth, MENU_SEXO, &sexo);
	return true;
}

