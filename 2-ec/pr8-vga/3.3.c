#include <stdlib.h>
#include <stdio.h>
#include <vga.h>

int main(void)
{
	int i, newPage, curPage;
	unsigned char *vbuf; //puntero unsigned char
	vga_init();
	vga_setmode(G1024x768x256);
	vbuf = vga_getgraphmem();

	for (i = 0; i < 256; i++)
		vga_setpalette(i, 0, 0, i % 64);

	curPage = -1;
	for (i = 0; i < 1024 * 768; i++)
	{
		newPage = i >> 16;
		if (newPage != curPage)
		{
			curPage = newPage;
			vga_setpage(curPage);
		}
		vbuf[(i % 65536)] = i % 256;
	}

	sleep(5);
	vga_setmode(TEXT);

	return EXIT_SUCCESS;
}
