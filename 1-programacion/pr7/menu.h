
#ifndef HAVE_MENU_H
#define HAVE_MENU_H

#include <string>
using namespace std;

struct MenuOption {
       const string name;
       void (*function)(void * ctx);
};

struct Menu {
       const string title;
       unsigned int optionCount;
       const MenuOption* options;
};

void gui_tab(unsigned int depth);
void gui_header(unsigned int depth, const string title);
void gui_error(unsigned int depth, const string text);
void gui_input(unsigned int depth, const string text);
bool gui_read_string(unsigned int depth, const string name, string &value);
bool gui_read_int(unsigned int depth, const string name, int &value);
void gui_menu(unsigned int depth, const Menu menu, void * ctx);
void gui_pause();

#define _(...) __VA_ARGS__
#define ARRAY_SIZE(x) sizeof(x) / sizeof(x[0])
#define MENU_MAKE(id, title, ...) \
        static const MenuOption __menu_options_##id[] = { __VA_ARGS__ }; \
        static const Menu id = { title, ARRAY_SIZE(__menu_options_##id), __menu_options_##id };

#endif // ifndef HAVE_MENU_H
