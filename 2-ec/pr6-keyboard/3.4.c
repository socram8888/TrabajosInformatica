#include <stdio.h>
#include <sys/io.h>
#include <stdbool.h>
#include <unistd.h>
#include <termios.h>

#define KB_PORT_DATA 0x60
#define KB_PORT_CTRL 0x64

#define KB_CMD_LED 0xED
#define KB_CMD_ENABLE 0xF4
#define KB_CMD_DISABLE 0xF5
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
	unsigned char chac[256];
	unsigned int i, resultado = 0;
	resultado = iopl(3);

	if (resultado < 0) {
		perror("error al abrir puertos");
		return 1;
	}

	//hay que declarar estas dos variables para leer y almacenar el estado actual de la
	//configuración del terminal
	struct termios attr;
	struct termios orig_attr;
	//la función tcgetattr lee los atributos de tratamiento del teclado en la terminal
	tcgetattr(STDIN_FILENO, &orig_attr);
	attr = orig_attr;
	//desactivamos el flag que produce eco
	attr.c_lflag &= ~(ECHO) ;
	//la función tcsetattr escribe los nuevos atributos
	tcsetattr(STDIN_FILENO, TCSAFLUSH, &attr);

	do
	{
		resultado = kb_read();
		printf("%02X\n", resultado);
	}
	while (resultado != 0x10);

	iopl(0);

	// estas funciones son para vaciar el buffer del teclado de posibles caracteres que
	// estén a la espera de ser leídos ya que hemos desactivado el eco anteriormente donde
	// chac es una variable de tipo: unsigned char chac[256];
	printf("\r\nPara salir introduce cualquier tecla + enter\r\n");
	scanf("%s",chac);
	//Esta función recupera los atributos originales de la terminal
	tcsetattr(STDIN_FILENO, TCIFLUSH, &orig_attr);


	return 0;
}

