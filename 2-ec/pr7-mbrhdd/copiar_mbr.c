#include <stdio.h>
#include <stdlib.h>
#include <sys/io.h>

#define IDE_REG_DATA 0x0
#define IDE_REG_SECTORS 0x2
#define IDE_REG_LBA0 0x3
#define IDE_REG_LBA1 0x4
#define IDE_REG_LBA2 0x5
#define IDE_REG_LBA3 0x6
#define IDE_REG_CMDSTATUS 0x7

#define IDE_CMD_READSECTOR 0x20
#define IDE_CMD_WRITESECTOR 0x30

#define IDE_HOST_PRIMARY 0x1F0
#define IDE_HOST_SECONDARY 0x170

#define IDE_DRIVE_MASTER 0
#define IDE_DRIVE_SLAVE 1

void buffer_dump(unsigned char * v, unsigned int len) {
	unsigned int pos, i;

	printf("-ADDRESS-|  0  1  2  3  4  5  6  7  8  9  A  B  C  D  E  F\n");

	for (pos = 0; pos < len; pos += 16, v += 16) {
		printf("%08X | ", pos);

		for (i = 0; i < 16; i++) {
			if (i != 0)
				printf(" ");

			if (i < (len - pos))
				printf("%02X", v[i]);
			else
				printf("  ");
		}

		printf(" | ");

		for (i = 0; i < 16; i++) {
			if (i < (len - pos))
				if (v[i] < ' ')
					printf(".");
				else
					printf("%c", v[i]);
			else
				printf(" ");
		}

		printf("\n");
	}
}

void ide_sector_select(unsigned int idebase, unsigned int drive, unsigned int sector) {
	while ((inb(idebase + IDE_REG_CMDSTATUS) & 0x80));

	outb(1, idebase + IDE_REG_SECTORS);
	outb(sector, idebase + IDE_REG_LBA0);
	outb(sector >> 8, idebase + IDE_REG_LBA1);
	outb(sector >> 16, idebase + IDE_REG_LBA2);
	outb(0xE0 | drive << 4 | sector >> 24, idebase + IDE_REG_LBA3);
}

void ide_command(unsigned int idebase, unsigned char cmd) {
	while (!(inb(idebase + IDE_REG_CMDSTATUS) & 0x40));

	outb(cmd, idebase + IDE_REG_CMDSTATUS);
}

void ide_read(unsigned int idebase, unsigned char * buf, unsigned int len) {
	unsigned int i;
	unsigned short val;

	for(i = 0; i < len; i += 2, buf += 2) {
		while (!(inb(idebase + IDE_REG_CMDSTATUS) & 0x08));

		*((unsigned short *) buf) = inw(idebase + IDE_REG_DATA);
	}
}

void ide_write(unsigned int idebase, unsigned char * buf, unsigned int len) {
	unsigned int i;
	unsigned short val;

	for(i = 0; i < len; i += 2, buf += 2) {
		while (!(inb(idebase + IDE_REG_CMDSTATUS) & 0x08));

		outw(*((unsigned short *) buf), idebase + IDE_REG_DATA);
	}
}

void ide_sector_read(unsigned int idebase, unsigned int drive, unsigned int sector, unsigned char * buf) {
	ide_sector_select(idebase, drive, sector);
	ide_command(idebase, IDE_CMD_READSECTOR);
	ide_read(idebase, buf, 512);
}

void ide_sector_write(unsigned int idebase, unsigned int drive, unsigned int sector, unsigned char * buf) {
	ide_sector_select(idebase, drive, sector);
	ide_command(idebase, IDE_CMD_WRITESECTOR);
	ide_write(idebase, buf, 512);
}

int main(int argc, char **argv) {
	int i, result;
	unsigned char valores[512];

	result = iopl(3);
	if (result != 0) printf("Error en la reserva de puerto");

	ide_sector_read(IDE_HOST_PRIMARY, IDE_DRIVE_SLAVE, 0x00000000, valores);
	ide_sector_write(IDE_HOST_PRIMARY, IDE_DRIVE_MASTER, 0x00000000, valores);
	buffer_dump(valores, 512);

	iopl(0);
	exit(0);
}

