package ti.sazeith.is2.savana.ai;

import ti.sazeith.is2.savana.Animal;

/**
 * Age dying AI
 * @author alumno
 */
public class DieAI extends AI {
	private float probability;

	/**
	 * Constructor
	 * @param probability Probability of dying per day
	 */
	public DieAI(float probability) {
		this.probability = probability;
	}

	@Override
	public void tick(Animal animal) {
		if (animal.getSavanna().getRandom().nextFloat() < probability) {
			animal.kill();
		}
	}
}
