
#include "sysdep.h"

#ifdef _WIN32

// http://creatusjuegosdecero.webege.com/index.php?topic=87.msg403
void display_move(unsigned int x, unsigned int y)
{
    HANDLE hCon;
    COORD dwPos;

    dwPos.X = x;
    dwPos.Y = y;
    hCon = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(hCon, dwPos);
}

void display_clear()
{
    system("cls");
}

void sysdep_sleep(unsigned int millis)
{
	Sleep(millis);
}

#else

// http://zobayer.blogspot.com.es/2010/12/getch-getche-in-gccg.html
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

// http://creatusjuegosdecero.webege.com/index.php?topic=87.msg403
void display_move(unsigned int x, unsigned int y)
{
	printf("\033[%i;%iH", x, y);
}

void display_clear()
{
    display_move(1, 1);
	printf("\033[J");
}

void sysdep_sleep(unsigned int millis)
{
	usleep(millis * 1000);
}

#endif
