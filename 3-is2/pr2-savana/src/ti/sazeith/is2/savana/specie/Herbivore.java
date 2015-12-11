package ti.sazeith.is2.savana.specie;

import ti.sazeith.is2.savana.IntRange;

/**
 * Base class for herbivores
 * @author alumno
 */
public abstract class Herbivore extends Specie {
	public Herbivore(String name, IntRange speedRange, IntRange spawnRange) {
		super(name, speedRange, spawnRange);
	}
}
