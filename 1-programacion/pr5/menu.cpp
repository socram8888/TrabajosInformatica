
#include "menu.h"
#include "getch.h"
#include <iostream>
using namespace std;

static const uint DEPTH_SPACES = 3;

// http://stackoverflow.com/a/10402513
void display_move(uint x, uint y)
{
    cout << "\033[" << x << ";" << y << "H";
}

void display_clear()
{
    display_move(1, 1);
    cout << "\033[J";
}

void gui_tab(uint depth)
{
     while (depth-- > 0) {
           for (uint i = 0; i < DEPTH_SPACES; i++) {
               cout << ' ';
           }
     }
}

void gui_header(uint depth, string title)
{
     gui_tab(depth);
     cout << "*** " << title << "\n";
}

void gui_menu(uint depth, const Menu menu, void * ctx)
{
     cout << "* " << menu.title << " *\n";
     for (uint i = 0; i < menu.optionCount; i++) {
         cout << "    * " << (char) ('A' + i) << ": " << menu.options[i].name << "\n";
     }

     int ch;
     do {
         ch = toupper(getch());
     } while (ch < 'A' || ch > ('A' + menu.optionCount - 1));

     menu.options[ch - 'A'].function(ctx);
}

#ifndef _WIN32
// Equivalente para el getch en *nix
// http://zobayer.blogspot.com.es/2010/12/getch-getche-in-gccg.html

#include <unistd.h>
#include <termios.h>
int getch() {
    struct termios oldattr, newattr;
    int ch;
    tcgetattr(STDIN_FILENO, &oldattr);
    newattr = oldattr;
    newattr.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newattr);
    ch = getchar();
    tcsetattr(STDIN_FILENO, TCSANOW, &oldattr);
    return ch;
}

#endif

void pause()
{
    cout << "*** Pulsa una tecla para continuar ***\n";
    getch();
}
