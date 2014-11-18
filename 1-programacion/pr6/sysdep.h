
#ifndef HAVE_SYSDEP_H
#define HAVE_SYSDEP_H

#ifdef _WIN32

#include <conio.h>
#include <windows.h>

#else

#include <stdio.h>
#include <unistd.h>
#include <termios.h>
int getch();

#endif

void display_clear();
void display_move(unsigned int x, unsigned int y);
void sysdep_sleep(unsigned int millis);

#endif
