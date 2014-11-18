
#ifndef HAVE_SEXO_H
#define HAVE_SEXO_H

#include <string>
using namespace std;

enum Sexo {
    DESCONOCIDO,
    MASCULINO,
    FEMENINO
};

string sexo_a_string(Sexo sexo);
bool gui_read_sex(uint depth, Sexo &sexo);

#endif
