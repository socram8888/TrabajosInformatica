package ti.sazeith.is2.savana.ai;

import ti.sazeith.is2.savana.Animal;
import ti.sazeith.is2.savana.Savanna;
import ti.sazeith.is2.savana.weather.Rain;

/**
 * Drowning AI for small animals
 * @author alumno
 */
public class DrownAI extends AI {
	private Rain waterLevel;
	private float probability;

	/**
	 * Constructor
	 * @param waterLevel Level of rain at which the animal may drown
	 * @param probability Probability of drowning per day
	 */
	public DrownAI(Rain waterLevel, float probability) {
		this.waterLevel = waterLevel;
		this.probability = probability;
	}

	@Override
	public void tick(Animal animal) {
		Savanna savanna = animal.getSavanna();
		if (savanna.getRain().compareTo(waterLevel) > 0) {
			if (savanna.getRandom().nextFloat() < probability) {
				animal.kill();
			}
		}
	}
}
