package ti.sazeith.is2.savana.ai;

import ti.sazeith.is2.savana.Animal;
import ti.sazeith.is2.savana.Sex;

/**
 * Breeding AI
 * @author alumno
 */
public class BreedAI extends AI {
	private float probability;

	/**
	 * Constructor
	 * @param probability Probability of breeding per day
	 */
	public BreedAI(float probability) {
		this.probability = probability;
	}

	@Override
	public void tick(Animal animal) {
		if (animal.getSex() != Sex.FEMALE) {
			return;
		}

		if (animal.getSavanna().getRandom().nextFloat() > probability) {
			return;
		}

		animal.breed();
	}
}
