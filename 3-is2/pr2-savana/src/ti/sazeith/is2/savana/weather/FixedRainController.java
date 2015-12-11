package ti.sazeith.is2.savana.weather;

import ti.sazeith.is2.savana.Savanna;

/**
 * Fixed rain controller
 * @author alumno
 */
public class FixedRainController extends RainController {
	private Rain rain;

	/**
	 * Constructor
	 * @param rain Rain value
	 */
	public FixedRainController(Rain rain) {
		this.rain = rain;
	}

	@Override
	public Rain update(Savanna savanna) {
		return rain;
	}
}
