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

int main() {
	int ledPos = 1;
	int dir = -1;
	unsigned char ints;

	while (1) {
		while (!(REG_INT & FLAG_INT_K1_LATCH));
		while (REG_INT & FLAG_INT_K1_VALUE);
		REG_INT = 0;

		while (1) {
			ints = REG_INT;

			if (ints & FLAG_INT_K2_LATCH) {
				if (ledPos == 0) {
					while (REG_INT & FLAG_INT_K2_VALUE);
					REG_INT = 0;
					break;
				}

				REG_INT = 0;
			}

			if (ints & FLAG_INT_TIMER_LATCH) {
				ledPos += dir;
				REG_LEDS = 1 << ledPos;

				if (ledPos == 7 && dir == +1 || ledPos == 0 && dir == -1) {
					dir = -dir;
				}

				while (REG_INT & FLAG_INT_TIMER_VALUE);
				REG_INT = 0;
			}
		}
	}

	return 0;
}
