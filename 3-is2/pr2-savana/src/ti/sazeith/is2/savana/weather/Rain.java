package ti.sazeith.is2.savana.weather;

import java.io.Serializable;

/**
 * Rain values enumeration
 * @author alumno
 */
public enum Rain implements Comparable<Rain>, Serializable {
	NONE(0),
	LIGHT(4000),
	MEDIUM(8000),
	HEAVY(12000);

	private static final long serialVersionUID = 1L;
	private final int grass;

	private Rain(int grass) {
		this.grass = grass;
	}

	/**
	 * Retrieves amount of grass that grows every day
	 * @return grass growth
	 */
	public int getGrassGrowth() {
		return grass;
	}
}
