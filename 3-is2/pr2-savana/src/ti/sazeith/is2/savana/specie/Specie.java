package ti.sazeith.is2.savana.specie;

import java.util.LinkedList;
import java.util.List;

import ti.sazeith.is2.savana.Animal;
import ti.sazeith.is2.savana.IntRange;
import ti.sazeith.is2.savana.ai.AI;

/**
 * Base class which groups common traits for a given species.
 * @author alumno
 */
public abstract class Specie {
	private final String name;
	private IntRange speedRange;
	private IntRange spawnRange;
	private List<AI> ais = new LinkedList<AI>();

	/**
	 * Constructor
	 * @param name Species name
	 * @param speedRange Animal speed range
	 * @param spawnRange Amount of animals to spawn on new savanna
	 */
	public Specie(String name, IntRange speedRange, IntRange spawnRange) {
		this.name = name;
		this.speedRange = speedRange;
		this.spawnRange = spawnRange;
	}

	/**
	 * @return Species name
	 */
	public String getName() {
		return name;
	}

	/**
	 * @return Speed range in Km/h
	 */
	public IntRange getSpeedRange() {
		return speedRange;
	}

	/**
	 * @return Range of animals to spawn on new savanna
	 */
	public IntRange getSpawnRange() {
		return spawnRange;
	}

	/**
	 * Adds a new artificial intelligency module
	 * @param ai AI module
	 */
	public void add(AI ai) {
		ais.add(ai);
	}

	/**
	 * Executes an iteration of all AI modules for a given animal
	 * @param animal Animal
	 */
	public void doTick(Animal animal) {
		for (AI ai : ais) {
			ai.tick(animal);
			if (animal.isDead()) {
				return;
			}
		}
	}
}
