#include <stdio.h>
#include <sys/io.h>

int main(int argc, char **argv)
{
	unsigned int i, resultado = 0;
	resultado = iopl(3);

	if (resultado < 0) {
		perror("error al abrir puertos");
		return 1;
	}

	for(i=0; i<5; i++)
	{
		while (inb(0x64) & 0x02); // Comprueba si se puede mandar un comando
		outb(0xFF, 0x60);

		// Envía el commando 0xFF al Puerto de
		// escritura 0x60
		while (!(inb(0x64) & 0x01));

		// Comprueba si hay algo en el buffer de
		// recepción
		printf("%X \r\n", inb(0x60));

		// Imprime lo que haya en el buffer de
		// recepción
		sleep(1);
		// Espera 1 segundo
	}

	iopl(0);
	return 0;
}

