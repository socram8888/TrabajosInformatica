package ti.sazeith.is2.savana.ai;

import ti.sazeith.is2.savana.Animal;

/**
 * Base species-independent artificial intelligency
 * @author alumno
 */
public abstract class AI {
	/**
	 * Executes an iteration of the animal's artificial intelligency
	 * @param animal The animal to process
	 */
	public abstract void tick(Animal animal);
}
