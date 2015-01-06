
#include "menu.h"
#include "sysdep.h"
#include "numutils.h"
#include <iostream>
using namespace std;

static const unsigned int DEPTH_SPACES = 3;

void ostream_repeat(ostream &stream, const string text, unsigned int count)
{
    while (count-- > 0)
        stream << text;
}

void gui_tab(unsigned int depth)
{
	ostream_repeat(cout, " ", depth * DEPTH_SPACES);
}

void gui_header(unsigned int depth, const string title)
{
     gui_tab(depth);
     cout << "*** " << title << "\n";
}

void gui_error(unsigned int depth, const string text)
{
    gui_header(depth, text);
    gui_pause();
}

void gui_input(unsigned int depth, const string text)
{
	gui_tab(depth);
    cout << "- " << text << ": ";
}

bool gui_read_string(unsigned int depth, const string name, string &value)
{
    bool ok;
    string errstr;

    cin.clear();
    gui_input(depth, name);
    getline(cin, value);

    ok = cin.good();
    if (!ok)
    {
        errstr = name + " no valido";
        gui_error(depth, errstr);
    }

    return ok;
}

bool gui_read_int(unsigned int depth, const string name, int &value)
{
    bool ok;
    string valuestr;
    string errstr;

    ok = gui_read_string(depth, name, valuestr);

    if (ok)
    {
        ok = string2int(valuestr, value);
        if (!ok)
        {
            errstr = name + " no valido (no es un numero)";
            gui_error(depth, errstr);
        }
    }

    return ok;
}

bool gui_read_uint(unsigned int depth, const string name, unsigned int &value)
{
    bool ok;
    string valuestr;
    string errstr;

    ok = gui_read_string(depth, name, valuestr);

    if (ok)
    {
        ok = string2uint(valuestr, value);
        if (!ok)
        {
            errstr = name + " no valido (no es un numero)";
            gui_error(depth, errstr);
        }
    }

    return ok;
}

void gui_menu(unsigned int depth, const Menu menu, void * ctx)
{
	string optionstring;
	gui_input(depth, menu.title);
	cout << '\n';

    for (unsigned int i = 0; i < menu.optionCount; i++) {
		gui_tab(depth + 1);
		cout << "* " << (char) ('A' + i) << ": " << menu.options[i].name + '\n';
    }

    int ch;
    do {
        ch = toupper(getch());
    } while (ch < 'A' || ch > ('A' + menu.optionCount - 1));
	cout << "\n";

    menu.options[ch - 'A'].function(ctx);
}

void gui_pause()
{
    cout << "*** Pulsa una tecla para continuar ***\n";
    getch();
}
