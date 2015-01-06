
#ifndef HAVE_GETCH_H
#define HAVE_GETCH_H

#ifdef _WIN32

// Libreria para getch en Windows
#include <conio.h>

#else

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

#endif
