package ti.sazeith.is2.savana.weather;

import ti.sazeith.is2.savana.Savanna;

/**
 * Random rain. Chooses a random rain value every day.
 * @author alumno
 */
public class RandomRainController extends RainController {
	@Override
	public Rain update(Savanna savanna) {
		Rain[] rains = Rain.values();
		int pos = savanna.getRandom().nextInt(rains.length);
		return rains[pos];
	}
}
