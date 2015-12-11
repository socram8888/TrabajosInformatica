package ti.sazeith.is2.savana.weather;

import ti.sazeith.is2.savana.Savanna;

/**
 * Abstract base class for rain controllers
 * @author alumno
 */
public abstract class RainController {
	/**
	 * Calculates the new rain value for the given savanna
	 * @param savanna Savanna to update rain for
	 * @return new rain value
	 */
	public abstract Rain update(Savanna savanna);
}
