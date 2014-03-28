// Informatica - Trabajo Final / Opción B (07/II/2014) - battleship.cpp
// Marcos Vives Del Sol (socram8888@gmail.com)
// Licencia: WTFPL
// AVISO AL CORRECTOR: ESTE PROGRAMA NO HA SIDO PROBADO SOBRE WINDOWS,
// SOLAMENTE SOBRE LINUX, YA QUE EN ESTOS MOMENTOS NO TENGO NINGUNA MAQUINA
// CON WINDOWS EN LA QUE TESTEARLO.
// DEBERIA FUNCIONAR CORRECTAMENTE, PERO NO PUEDO ASEGURARLO.

#include <cstdlib>
#include <iostream>
#include <fstream>
#include <cmath>
#include <time.h>
using namespace std;

// Cambia este valor a "true" para ver los barcos de la maquina
#define DISPLAY_ENEMY_SHIPS false

typedef unsigned int uint;

#define max(a, b) a > b ? a : b;
#define min(a, b) a < b ? a : b;

#define ARRAY_SIZE(arr) (sizeof(arr)/sizeof(arr[0]))

inline uint num_width(int num) {
    uint len;

    if (num == 0) {
        len = 1;
    } else {
        len = ceil(log10(num));
    }

    return len;
}

// http://stackoverflow.com/a/10402513
inline void display_move(uint x, uint y) {
    cout << "\033[" << x << ";" << y << "H";
}

inline void display_clear() {
    display_move(1, 1);
    cout << "\033[J";
}

bool string2uint(string str, uint &out)
{
    uint num;
    char* start;
    char* end;

    start = (char*) str.c_str();
    num = strtoul(start, &end, 10);
    out = num;

    return (start + str.length()) == end;
}

inline bool rand_bool()
{
    return rand() < RAND_MAX / 2;
}

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

/******************************************************************************/

void ostream_repeat(ostream &stream, string text, uint count)
{
    while (count-- > 0)
        stream << text;
}

const uint SCREEN_WIDTH = 80;
const uint DEPTH_MARGIN = 3;

struct Menu {
    const uint count;
    const string title;
    const string* options;
};
#define MENU_MAKE(name, title, ...) const string __menu_options_##name[] = { __VA_ARGS__ }; const Menu name = { ARRAY_SIZE(__menu_options_##name), title, __menu_options_##name };

void tab_header(uint depth, string text)
{
    uint pos = 0;

    while (pos < depth * DEPTH_MARGIN)
    {
        cout << ' ';
        pos++;
    }

    while (pos < SCREEN_WIDTH / 2 - (text.length() + 2) / 2)
    {
        cout << '#';
        pos++;
    }

    cout << ' ' << text << ' ';
    pos += text.length() + 2;

    while (pos < SCREEN_WIDTH - DEPTH_MARGIN * depth)
    {
        cout << '#';
        pos++;
    }

    cout << endl;
}

void tab_error(uint depth, string text)
{
    tab_header(depth, text);
    getch();
}

void tab_input(uint depth, string text)
{
    ostream_repeat(cout, " ", (depth + 1) * DEPTH_MARGIN);
    cout << "- " << text << ": ";
}

uint tab_menu(uint depth, const Menu menu)
{
    uint i;
    char index;

    tab_input(depth, menu.title);
    cout << "\n";

    for (i = 0; i < menu.count; i++)
    {
        ostream_repeat(cout, " ", (depth + 2) * DEPTH_MARGIN);
        index = 'A' + i;
        cout << "* " << index << ": " << menu.options[i] << "\n";
    }

    do {
        index = toupper(getch());
    } while ((index < 'A') || (index >= ('A' + (int) menu.count)));

    return index - 'A';
}

bool tab_read_string(uint depth, string name, string &value)
{
    bool ok;
    string errstr;

    cin.clear();
    tab_input(depth, name);
    getline(cin, value);

    ok = cin.good();
    if (!ok)
    {
        errstr = name + " no valido";
        tab_error(depth, errstr);
    }

    return ok;
}

bool tab_read_uint(uint depth, string name, uint &value)
{
    bool ok;
    string valuestr;
    string errstr;

    ok = tab_read_string(depth, name, valuestr);

    if (ok)
    {
        ok = string2uint(valuestr, value);
        if (!ok)
        {
            errstr = name + " no valido (no es un numero)";
            tab_error(depth, errstr);
        }
    }

    return ok;
}

MENU_MAKE(MENU_ORIENTATION, "Orientacion",
"Vertical",
"Horizontal");

bool tab_read_orientation(uint depth)
{
    return tab_menu(depth, MENU_ORIENTATION) == 0;
}

/******************************************************************************/

const uint GAME_WIDTH_MIN = 3;
const uint GAME_WIDTH_MAX = 10;
const uint GAME_SHIP_BIAS = 2;
const uint GAME_SHIP_SIZE = 2;

struct Game;
struct Screen;

struct Ship {
    uint x;
    uint y;
    bool vertical;
};

const uint GAME_SHIPS_MAX = GAME_WIDTH_MAX - GAME_SHIP_BIAS;
typedef Ship ShipList[GAME_SHIPS_MAX];
typedef bool ShotList[GAME_WIDTH_MAX][GAME_WIDTH_MAX];

struct Screen {
    Game* game;
    uint shipCount;
    ShipList ships;
    ShotList shots;
};

struct Game {
    uint width;
    bool playsAI;
    Screen screenPlayer;
    Screen screenAI;
};

uint screen_ship_get(Screen &screen, uint x, uint y)
{
    uint id = -1;

    for (uint i = 0; i < screen.shipCount; i++)
    {
        if (
            (                            screen.ships[i].x == (x    ) && screen.ships[i].y == (y    )) ||
            (!screen.ships[i].vertical && screen.ships[i].x == (x - 1) && screen.ships[i].y == (y    )) ||
            ( screen.ships[i].vertical && screen.ships[i].x == (x    ) && screen.ships[i].y == (y - 1))
        ) {
            id = i;
        }
    }

    return id;
}

bool screen_contains_ship(Screen &screen, uint x, uint y)
{
    return screen_ship_get(screen, x, y) != (uint) -1;
}

bool screen_ship_sunk(Screen &screen, uint shipId)
{
    return screen.shots[screen.ships[shipId].y    ][screen.ships[shipId].x    ] &&
            ((!screen.ships[shipId].vertical && screen.shots[screen.ships[shipId].y    ][screen.ships[shipId].x + 1]) ||
                (screen.ships[shipId].vertical && screen.shots[screen.ships[shipId].y + 1][screen.ships[shipId].x    ]));
}

void screen_reset(Screen &screen)
{
    uint x, y;
    screen.shipCount = 0;

    for (y = 0; y < screen.game->width; y++)
    {
        for (x = 0; x < screen.game->width; x++)
        {
            screen.shots[y][x] = false;
        }
    }
}

bool screen_attempt_placement(Screen &screen, uint x, uint y, bool vertical)
{
    bool empty = !screen_contains_ship(screen, x, y);

    if (empty)
    {
        if (vertical)
            empty = !screen_contains_ship(screen, x, y + 1);
        else
            empty = !screen_contains_ship(screen, x + 1, y);
    }

    if (empty)
    {
        screen.ships[screen.shipCount].x = x;
        screen.ships[screen.shipCount].y = y;
        screen.ships[screen.shipCount].vertical = vertical;
        screen.shipCount++;
    }

    return empty;
}

void screen_populate(Screen &screen)
{
    uint x, y;
    bool vert;

    do {
        x = rand() % (screen.game->width - 1);
        y = rand() % (screen.game->width - 1);
        vert = rand_bool();

        screen_attempt_placement(screen, x, y, vert);
    } while (screen.shipCount < (screen.game->width - GAME_SHIP_BIAS));
}

/******************************************************************************/

struct SaveLoadHandler {
    bool (*process)(SaveLoadHandler&, void*, uint);
    union {
        istream* input;
        ostream* output;
    };
};

bool slh_process_load(SaveLoadHandler &slh, void* data, uint len)
{
    slh.input->read((char*) data, len);
    return slh.input->good();
}

bool slh_process_save(SaveLoadHandler &slh, void* data, uint len)
{
    slh.output->write((char*) data, len);
    return slh.output->good();
}

#define slh_process(slh, what) slh.process(slh, &what, sizeof(what))

bool ship_load_save(Ship &ship, SaveLoadHandler &slh)
{
    return
        slh_process(slh, ship.x) &&
        slh_process(slh, ship.y) &&
        slh_process(slh, ship.vertical);
}

bool screen_load_save(Screen &screen, SaveLoadHandler &slh)
{
    bool ok = true;
    uint i, j;

    i = 0;
    screen.shipCount = screen.game->width - GAME_SHIP_BIAS;
    while (ok && i < screen.shipCount)
    {
        ok = ship_load_save(screen.ships[i], slh);
        i++;
    }

    i = 0;
    while (ok && i < screen.game->width)
    {
        j = 0;
        while (ok && j < screen.game->width)
        {
            ok = slh_process(slh, screen.shots[i][j]);
            j++;
        }
        i++;
    }

    return ok;
}

bool game_load_save(Game &game, SaveLoadHandler &slh)
{
    game.screenPlayer.game = &game;
    game.screenAI.game = &game;

    return
        slh_process(slh, game.width) &&
        (game.width >= GAME_WIDTH_MIN && game.width <= GAME_WIDTH_MAX) &&
        slh_process(slh, game.playsAI) &&
        screen_load_save(game.screenPlayer, slh) &&
        screen_load_save(game.screenAI, slh);
}

bool game_load(Game &game, string filename)
{
    ifstream ifs;
    SaveLoadHandler slh;
    slh.process = &slh_process_load;

    ifs.open(filename.c_str(), ios::binary);
    slh.input = &ifs;

    return game_load_save(game, slh);
}

bool game_save(Game &game, string filename)
{
    ofstream ofs;
    SaveLoadHandler slh;
    slh.process = &slh_process_save;

    ofs.open(filename.c_str(), ios::binary);
    slh.output = &ofs;

    return game_load_save(game, slh);
}

/*****************************************************************************/

void game_render_nums(Game &game)
{
    uint i;
    cout << "  ";
    for (i = 0; i < game.width; i++)
    {
        cout << i << " ";
    }
    cout << "  ";
}

void game_render_edge(Game &game)
{
    cout << " +";
    ostream_repeat(cout, "--", game.width);
    cout << "-+ ";
}

const string RENDER_WATER = " ";
const string RENDER_WATER_HIT = "\033[37m>";
const string RENDER_SHIP = "\033[36mO";
const string RENDER_SHIP_HIT = "\033[35m#";

void game_render_cells(Screen &screen, uint line, bool hideShips)
{
    uint x;

    cout << line << "|\033[44m ";
    for (x = 0; x < screen.game->width; x++)
    {
        if (screen.shots[line][x])
        {
            if (screen_contains_ship(screen, x, line))
                cout << RENDER_SHIP_HIT;
            else
                cout << RENDER_WATER_HIT;
        }
        else
        {
            if (!hideShips && screen_contains_ship(screen, x, line))
                cout << RENDER_SHIP;
            else
                cout << RENDER_WATER;
        }
        cout << " ";
    }
    cout << "\033[39m\033[49m|";
}

void game_render(Game &game)
{
    uint i;
    display_clear();

    game_render_nums(game);
    game_render_nums(game);
    cout << "\n";

    game_render_edge(game);
    game_render_edge(game);
    cout << "\n";

    for (i = 0; i < game.width; i++) {
        game_render_cells(game.screenPlayer, i, false);
        cout << " ";
        game_render_cells(game.screenAI, i, !DISPLAY_ENEMY_SHIPS);
        cout << "\n";
    }

    game_render_edge(game);
    game_render_edge(game);
    cout << "\n\n";

    tab_header(0, "Registro de abordo");
}

bool tab_read_coord(uint depth, Screen &screen, uint &x, uint &y)
{
    bool ok = tab_read_uint(depth, "Coordenada X", x);
    if (ok)
    {
        ok = x < (*screen.game).width - 1;
        if (!ok)
            tab_error(depth, "Coordenada X no valida");
    }

    if (ok)
    {
        ok = tab_read_uint(depth, "Coordenada Y", y);
        if (ok)
        {
            ok = y < (*screen.game).width - 1;
            if (!ok)
                tab_error(depth, "Coordenada Y no valida");
        }
    }
    return ok;
}

bool tab_read_ship(uint depth, Screen &screen) {
    uint x, y;
    bool ok, vert;
    string shipname;
    char numbuff[8];

    sprintf(numbuff, "%d", screen.shipCount + 1);
    shipname = "Barco ";
    shipname += numbuff;

    game_render(*screen.game);
    tab_header(depth, shipname);

    ok = tab_read_coord(depth, screen, x, y);

    if (ok)
    {
        vert = tab_read_orientation(depth);
        ok = screen_attempt_placement(screen, x, y, vert);
        if (!ok)
            tab_error(depth, "La posicion seleccionada ya estaba ocupada");
    }

    return ok;
}

void tab_read_screen(uint depth, Screen &screen)
{
    while (screen.shipCount < screen.game->width - GAME_SHIP_BIAS) {
        tab_read_ship(depth + 1, screen);
    }
}

bool tab_read_gamewidth(uint depth, Game &game)
{
    return
        tab_read_uint(depth, "Ancho del mapa", game.width) &&
        game.width >= GAME_WIDTH_MIN &&
        game.width <= GAME_WIDTH_MAX;
}

typedef uint AttackResult;
const AttackResult ATTACKRESULT_INVALID = 0;
const AttackResult ATTACKRESULT_WATER = 1;
const AttackResult ATTACKRESULT_HIT = 2;
const AttackResult ATTACKRESULT_SUNK = 3;
const AttackResult ATTACKRESULT_WIN = 4;

AttackResult game_play_attack(Screen &screen, uint x, uint y)
{
    AttackResult result = ATTACKRESULT_INVALID;
    uint ship;

    if (!screen.shots[y][x])
    {
        result = ATTACKRESULT_WATER;
        screen.shots[y][x] = true;

        ship = screen_ship_get(screen, x, y);
        if (ship != (uint) -1)
        {
            result = ATTACKRESULT_HIT;
            if (screen_ship_sunk(screen, ship))
            {
                result = ATTACKRESULT_WIN;
                for (ship = 0; ship < screen.shipCount; ship++)
                {
                    if (!screen_ship_sunk(screen, ship))
                        result = ATTACKRESULT_SUNK;
                }
            }
        }
    }

    return result;
}

AttackResult game_play_attack_random(Screen &screen)
{
    AttackResult result;
    uint x, y;

    do
    {
        x = rand() % screen.game->width;
        y = rand() % screen.game->width;
        result = game_play_attack(screen, x, y);
    }
    while (result == ATTACKRESULT_INVALID);

    return result;
}

void game_play_log(Game game, AttackResult result, bool isAI)
{
    game_render(game);
    if (isAI)
        cout << "El ordenador";
    else
        cout << "El jugador";

    cout << " apunta, dispara y... ";

    switch (result)
    {
        case ATTACKRESULT_WATER:
            cout << "falla";
            break;
        case ATTACKRESULT_HIT:
            cout << "diana";
            break;
        case ATTACKRESULT_SUNK:
            cout << "BOOM! Uno menos";
            break;
        case ATTACKRESULT_WIN:
            cout << "GANA LA PARTIDA";
            break;
    }

    cout << "!\n";

    tab_error(0, "Pulsa una tecla para continuar");
}

bool game_play_ai(Game &game)
{
    AttackResult result = game_play_attack_random(game.screenPlayer);
    game_play_log(game, result, true);

    return result != ATTACKRESULT_WIN;
}

bool game_play_player_random(Game &game)
{
    AttackResult result = game_play_attack_random(game.screenAI);
    game_play_log(game, result, false);

    return result != ATTACKRESULT_WIN;
}

bool game_play_player_shoot(Game &game)
{
    uint x, y;
    AttackResult result;

    do {
        while (!tab_read_coord(1, game.screenAI, x, y));

        result = game_play_attack(game.screenAI, x, y);
        if (result == ATTACKRESULT_INVALID)
            tab_error(1, "Esa casilla ya ha sido atacada");
    }
    while (result == ATTACKRESULT_INVALID);

    game_play_log(game, result, false);
    return result != ATTACKRESULT_WIN;
}

MENU_MAKE(MENU_INGAME_SAVE, "Deseas guardar antes de salir?",
"Si",
"No")

void game_play_leave(Game &game)
{
    string filename;
    if (tab_menu(1, MENU_INGAME_SAVE) == 0)
    {
        tab_read_string(1, "Nombre del archivo", filename);
        if (!game_save(game, filename))
            tab_error(1, "No se ha podido guardar la partida");
    }
}

MENU_MAKE(MENU_INGAME_ACTION, "Acciones",
"Disparar",
"Disparar a boleo",
"Salir");

bool game_play_player(Game &game)
{
    bool play = true;

    game_render(game);
    switch (tab_menu(0, MENU_INGAME_ACTION))
    {
        case 0:
            play = game_play_player_shoot(game);
            break;
        case 1:
            play = game_play_player_random(game);
            break;
        case 2:
            game_play_leave(game);
            play = false;
            break;
    }

    return play;
}

void game_play(Game &game)
{
    bool play = true;

    do
    {
        if (game.playsAI)
            play = game_play_ai(game);
        else
            play = game_play_player(game);
        game.playsAI = !game.playsAI;
    }
    while (play);
}

MENU_MAKE(MENU_AUTO_POPULATE, "Deseas que se coloquen los barcos automaticamente?",
"Si",
"No")

void game_menu_create(Game &game)
{
    game.screenPlayer.game = &game;
    game.screenAI.game = &game;
    game.playsAI = rand_bool();

    tab_header(1, "Crear partida");
    if (tab_read_gamewidth(1, game))
    {
        screen_reset(game.screenPlayer);
        screen_reset(game.screenAI);
        screen_populate(game.screenAI);

        if (tab_menu(1, MENU_AUTO_POPULATE) == 0)
            screen_populate(game.screenPlayer);
        else
            tab_read_screen(1, game.screenPlayer);

        game_play(game);
    }
    else
        tab_error(1, "Ancho no valido (debe estar entre 3 y 10)");
}

void game_menu_load(Game &game)
{
    string filename;

    tab_header(1, "Cargar partida");
    tab_read_string(1, "Nombre del fichero", filename);

    if (game_load(game, filename))
        game_play(game);
    else
        tab_error(1, "No se ha podido cargar la partida");
}

MENU_MAKE(MENU_MAIN, "¿Que deseas hacer?",
    "Partida nueva",
    "Cargar partida",
    "Salir"
);

int main() {
    Game game;
    bool play = true;
    srand(time(NULL));

    do {
        display_clear();
        tab_header(0, "Menu principal");
        switch (tab_menu(0, MENU_MAIN)) {
            case 0:
                game_menu_create(game);
                break;
            case 1:
                game_menu_load(game);
                break;
            case 2:
                play = false;
        }
    } while (play);

    return 0;
}
