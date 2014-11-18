
#include "timeparser.h"
#include <stdio.h>

string segundos_a_tiempo(int seg)
{
	char buffer[32];
	sprintf(buffer, "%02i:%02i:%02i", seg / 3600, seg / 60 % 60, seg % 60);;
	return string(buffer);
}
