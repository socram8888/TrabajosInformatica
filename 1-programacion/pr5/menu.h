
#ifndef HAVE_MENU_H
#define HAVE_MENU_H

#include <string>
using namespace std;

typedef unsigned int uint;

struct MenuOption {
       const string name;
       void (*function)(void * ctx);
};

struct Menu {
       const string title;
       uint optionCount;
       const MenuOption* options;
};

#define _(...) __VA_ARGS__
#define ARRAY_SIZE(x) sizeof(x) / sizeof(x[0])
#define MENU_MAKE(id, title, ...) \
        static const MenuOption __menu_options_##id[] = { __VA_ARGS__ }; \
        static const Menu id = { title, ARRAY_SIZE(__menu_options_##id), __menu_options_##id };

void display_move(uint x, uint y);
void display_clear();
void gui_tab(uint depth);
void gui_header(uint depth, string title);
void gui_menu(uint depth, const Menu menu, void * ctx);
void pause();

#ifdef _WIN32

// Libreria para getch en Windows
#include <conio.h>

#else

// Equivalente para el getch en *nix
// http://zobayer.blogspot.com.es/2010/12/getch-getche-in-gccg.html
#include <unistd.h>
#include <termios.h>
int getch();

#endif // ifdef _WIN32
#endif // ifndef HAVE_MENU_H
