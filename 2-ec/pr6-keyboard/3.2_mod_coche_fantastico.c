#include <stdio.h>
#include <sys/io.h>
#include <stdbool.h>

#define KB_PORT_DATA 0x60
#define KB_PORT_CTRL 0x64

#define KB_CMD_LED 0xED
#define KB_CMD_RESET 0xFF

#define KB_LED_SCROLLLOCK (1 << 0)
#define KB_LED_NUMLOCK (1 << 1)
#define KB_LED_CAPSLOCK (1 << 2)

void kb_send(unsigned char val)
{
	while (inb(KB_PORT_CTRL) & 0x02); // Esperar si el buffer de salida esta lleno
	outb(val, KB_PORT_DATA);
}

unsigned char kb_read()
{
	while (!(inb(KB_PORT_CTRL) & 0x01)); // Esperar si el buffer de salida esta lleno
	return inb(KB_PORT_DATA);
}

int main(int argc, char **argv)
{
	unsigned int i, resultado = 0;
	resultado = iopl(3);

	if (resultado < 0) {
		perror("error al abrir puertos");
		return 1;
	}

	i = 0;
	while (true)
	{
		switch (i)
		{
			case 0:
				resultado = KB_LED_NUMLOCK;
				break;
			case 1:
			case 3:
				resultado = KB_LED_CAPSLOCK;
				break;
			case 2:
				resultado = KB_LED_SCROLLLOCK;
		}
		kb_send(KB_CMD_LED);
		kb_send(resultado);
		sleep(1);
		i = (i + 1) % 4;
	}

	iopl(0);
	return 0;
}

