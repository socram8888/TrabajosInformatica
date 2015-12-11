package ti.sazeith.is2.savana.ai;

import ti.sazeith.is2.savana.Animal;
import ti.sazeith.is2.savana.IntRange;

/**
 * Grass eating AI for hervibores
 * @author alumno
 */
public class EatGrassAI extends AI {
	private IntRange range;

	/**
	 * Constructor
	 * @param range Amount of grass required to survive per day
	 */
	public EatGrassAI(IntRange range) {
		this.range = range;
	}

	@Override
	public void tick(Animal animal) {
		int amount = range.getRandom();
		if (!animal.getSavanna().eatGrass(amount)) {
			animal.kill();
		}
	}
}
