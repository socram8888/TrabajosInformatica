package ti.sazeith.is2.savana;

import java.io.Serializable;
import java.util.Random;

/**
 * Utility immutable class for integer ranges
 * @author alumno
 */
public class IntRange implements Serializable {
	private static final long serialVersionUID = 1L;
	private static final Random RANDOM = new Random();

	/**
	 * Min value
	 */
	public final int min;

	/**
	 * Max value
	 */
	public final int max;

	/**
	 * Constructor
	 * @param a First value
	 * @param b Second value
	 */
	public IntRange(int a, int b) {
		if (a > b) {
			int x = a;
			a = b;
			b = x;
		}

		this.min = a;
		this.max = b;
	}

	/**
	 * Calculates a random integer ranging from min to max, inclusive.
	 * @return random integer
	 */
	public int getRandom() {
		return RANDOM.nextInt(max - min + 1) + min;
	}
}
