package ti.sazeith.is2.savana.ai;

import java.util.Arrays;

import ti.sazeith.is2.savana.Animal;
import ti.sazeith.is2.savana.IntRange;
import ti.sazeith.is2.savana.specie.Herbivore;

/**
 * Carnivore herbivore-eating AI
 * @author alumno
 */
public class EatHerbivoreAI extends AI {
	private IntRange range;

	/**
	 * Constructor
	 * @param range Range of herbivores required to eat every day
	 */
	public EatHerbivoreAI(IntRange range) {
		this.range = range;
	}

	@Override
	public void tick(Animal predator) {
		int target = range.getRandom();
		if (target == 0) {
			return;
		}

		Animal[] herbivores = new Animal[target + 1];
		int count = 0;
		for (Animal other : predator.getSavanna().getAnimals().get(Herbivore.class)) {
			if (other.isDead()) {
				continue;
			}

			herbivores[count] = other;
			if (count < target) {
				count++;
			} else {
				Arrays.sort(herbivores, Animal.SPEED_COMPARATOR);
			}
		}

		if (count < target) {
			predator.kill();
			return;
		}

		for (int i = 0; i < target; i++) {
			herbivores[i].kill();
		}
	}
}
