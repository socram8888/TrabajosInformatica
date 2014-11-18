
#include "numutils.h"

bool string2int(string str, int &out)
{
    int num;
    char* start;
    char* end;

    start = (char*) str.c_str();
    num = strtol(start, &end, 10);
    out = num;

    return (start + str.length()) == end;
}

bool string2uint(string str, unsigned int &out)
{
    unsigned int num;
    char* start;
    char* end;

    start = (char*) str.c_str();
    num = strtoul(start, &end, 10);
    out = num;

    return (start + str.length()) == end;
}
