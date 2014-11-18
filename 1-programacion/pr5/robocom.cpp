
#include "catalogo.h"
#include "pelicula.h"
#include "articulo.h"
#include "libro.h"
#include "cd.h"
#include "menu.h"
#include <iostream>
using namespace std;

static const string ARCHIVO_CATALOGO = "todoacien.txt";
static const int ARTICULOS_PAGINA = 10;

struct MainContext {
    Catalogo catalogo;
    Cesta cesta;
    bool leave;
};

void robocom_buy(void * p, char tipo)
{
    MainContext *ctx = (MainContext *) p;
    int offset = 0;
    int i;
    int pageArticles;
    int boton;
    
    do
    {
        display_clear();
        pageArticles = min(ARTICULOS_PAGINA, ctx->catalogo.numeroArticulos(tipo) - offset);
        
        for (i = 0; i < pageArticles; i++)
        {
            cout << " * " << ctx->catalogo.dameArticulo(i + offset, tipo);
            i++;
        }
        
        boton = getch();
        if (boton >= '0' && boton <= '0' + pageArticles)
        {
            ctx->cesta.meter(ctx->catalogo.dameArticulo(offset + boton - '0', tipo));
        }
        else
        {
            switch (boton)
            {
                case '+':
                    if (offset + ARTICULOS_PAGINA < ctx->catalogo.numeroArticulos(tipo))
                        offset += ARTICULOS_PAGINA;
                    break;
                case '-':
                    if (offset - ARTICULOS_PAGINA >= 0)
                        offset -= ARTICULOS_PAGINA;
                    break;
            }
        }
    } while (boton != '\x1B');
}

void robocom_peliculas(void * p)
{
    robocom_buy(p, 'p');
}

void robocom_libros(void * p)
{
    robocom_buy(p, 'l');
}

void robocom_cds(void * p)
{
    robocom_buy(p, 'c');
}

MENU_MAKE(MENU_CATALOGO, "Tipo de articulos",
    _({"Peliculas", &robocom_peliculas}),
    _({"Libros", &robocom_libros}),
    _({"CDs", &robocom_cds}),
);

void robocom_catalog(void * p) {
    gui_menu(1, MENU_CATALOGO, p);
}

void robocom_delete(void * p) {
    cout << "Delete!\n";
}

void robocom_leave(void * p) {
    MainContext *ctx = (MainContext *) p;

    ctx->leave = true;
}

MENU_MAKE(MENU_MAIN, "Menu principal",
    _({ "Ver catalogo", &robocom_catalog }),
    _({ "Ver lista de la compra", &robocom_chosed }),
    _({ "Salir", &robocom_leave }),
);

int main() {
    MainContext ctx;
    ctx.leave = false;

    ifstream ifs;
    ifs.open(ARCHIVO_CATALOGO.c_str());
    ctx.catalogo.cargarArticulos(ifs);

    while (ctx.leave == false) {
        display_clear();
        gui_menu(0, MENU_MAIN, &ctx);
    }

    system("pause");
    return 0;
}
