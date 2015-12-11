package ti.sazeith.is2.savana.specie;

import ti.sazeith.is2.savana.IntRange;

/**
 * Base class for predators
 * @author alumno
 */
public abstract class Predator extends Specie {
	public Predator(String name, IntRange speedRange, IntRange spawnRange) {
		super(name, speedRange, spawnRange);
	}
}
