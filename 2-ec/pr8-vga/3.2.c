#include <stdlib.h>
#include <stdio.h>
#include <vga.h>

int main(void)
{
	int i, j, k;
	unsigned char *vbuf; //puntero unsigned char
	vga_init();
	vga_setmode(G320x200x256);
	vbuf = vga_getgraphmem();

	vga_setpalette(0, 0, 0, 0); //defino color negro en la paleta
	vga_setpalette(1, 63, 63, 63); //defino color blanco
	for (k = 0; k < 5; k++)
	{
		for (j = 0; j < 14; j++)
			for (i = 0; i < 9; i++)
				vbuf[j * 320 + i] = (k%2);
		sleep(1);
	}

	vga_setmode(TEXT);
	return EXIT_SUCCESS;
}
