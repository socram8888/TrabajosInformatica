package ti.sazeith.is2.savana;

import java.io.Serializable;
import java.util.Calendar;
import java.util.Comparator;

import ti.sazeith.is2.savana.specie.Specie;

/**
 * Animal class
 * @author alumno
 */
public class Animal implements Serializable {
	private static final long serialVersionUID = 1L;

	private final Savanna savanna;
	private final Specie specie;
	private final Calendar born;
	private final Sex sex;
	private boolean dead;
	private int speed;

	/**
	 * Commodity constructor that chooses random values for most stuff
	 * @param savanna Savanna that animals lives in
	 * @param specie Specie for this animal
	 */
	public Animal(Savanna savanna, Specie specie) {
		this(
			savanna,
			specie,
			specie.getSpeedRange() != null ? specie.getSpeedRange().getRandom() : -1
		);
	}

	/**
	 * Commodity constructor that chooses random values for most stuff except speed
	 * @param savanna Savanna that animals lives in
	 * @param specie Specie for this animal
	 * @param speed Animal's speed
	 */
	public Animal(Savanna savanna, Specie specie, int speed) {
		this(
			savanna,
			specie,
			savanna.getDate(),
			savanna.getRandom().nextBoolean() ? Sex.MALE : Sex.FEMALE,
			speed
		);
	}

	/**
	 * Constructor
	 * @param savanna Savanna that animals lives in
	 * @param specie Specie for this animal
	 * @param born Date this animals was born in
	 * @param sex Animal's sex
	 * @param speed Animal's speed
	 */
	public Animal(Savanna savanna, Specie specie, Calendar born, Sex sex, int speed) {
		this.savanna = savanna;
		this.specie = specie;
		this.born = born;
		this.sex = sex;
		this.speed = speed;
	}

	/**
	 * Executes an iteration of the animal's AI modules
	 */
	public void doTick() {
		specie.doTick(this);
	}


	/**
	 * Spawns a new animal sharing the speed of this one. Must be caled by AI modules only.
	 */
	public void breed() {
		this.savanna.getNewbornAnimals().add(new Animal(savanna, specie, speed));
	}

	/**
	 * Kills the animal. Must be called by AI modules only.
	 */
	public void kill() {
		this.dead = true;
		savanna.getDeadAnimals().add(this);
	}

	/**
	 * @return Animal's savanna
	 */
	public Savanna getSavanna() {
		return savanna;
	}

	/**
	 * @return Animal's species
	 */
	public Specie getSpecie() {
		return specie;
	}

	/**
	 * @return Animal's born date
	 */
	public Calendar getBorn() {
		return born;
	}

	/**
	 * @return Animal's sex
	 */
	public Sex getSex() {
		return sex;
	}

	/**
	 * @return True if dead
	 */
	public boolean isDead() {
		return dead;
	}

	/**
	 * @return animal's speed
	 */
	public int getSpeed() {
		return speed;
	}

	/**
	 * Comparator that sorts by animal's speed
	 */
	public static final Comparator<Animal> SPEED_COMPARATOR = new Comparator<Animal>() {
		@Override
		public int compare(Animal a, Animal b) {
			return Integer.compare(a.getSpeed(), b.getSpeed());
		}
	};
}
