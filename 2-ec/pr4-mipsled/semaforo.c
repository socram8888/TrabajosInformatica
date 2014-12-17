// Marcos Vives Del Sol
// 2ndo EC Informatica UV.es 2014/15

#define REG8(x) *((volatile unsigned char *) x)
#define REG_LEDS REG8(0xBF900000)
#define REG_INT REG8(0xBFA00000)
#define FLAG_INT_K2_VALUE (1 << 0)
#define FLAG_INT_K1_VALUE (1 << 1)
#define FLAG_INT_TIMER_VALUE (1 << 2)
#define FLAG_INT_K2_LATCH (1 << 4)
#define FLAG_INT_K1_LATCH (1 << 5)
#define FLAG_INT_TIMER_LATCH (1 << 6)

#define ROJO 0x0C
#define AMBAR 0x02
#define VERDE 0x01
#define COCHES(x) (x << 4)
#define PEATONES(x) (x << 0)

void wait_ticks(unsigned int ticks) {
	while (ticks > 0) {
		while (!(REG_INT & FLAG_INT_TIMER_LATCH));
		while (REG_INT & FLAG_INT_TIMER_VALUE);

		REG_INT = 0;
		ticks--;
	}
}

int main() {
	while (1) {
		REG_LEDS = PEATONES(ROJO) | COCHES(VERDE);

		while (!(REG_INT & FLAG_INT_K1_LATCH));
		while (REG_INT & FLAG_INT_K1_VALUE);
		REG_INT = 0;

		REG_LEDS = PEATONES(ROJO) | COCHES(AMBAR);
		wait_ticks(10);

		REG_LEDS = PEATONES(VERDE) | COCHES(ROJO);
		wait_ticks(50);

		REG_LEDS = PEATONES(AMBAR) | COCHES(ROJO);
		wait_ticks(10);
	}

	return 0;
}

