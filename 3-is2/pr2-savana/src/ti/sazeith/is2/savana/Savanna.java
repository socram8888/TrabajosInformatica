package ti.sazeith.is2.savana;

import ti.sazeith.is2.savana.specie.*;
import ti.sazeith.is2.savana.weather.*;

import java.io.Serializable;
import java.util.Arrays;
import java.util.Calendar;
import java.util.Collection;
import java.util.HashSet;
import java.util.List;
import java.util.Random;

public class Savanna implements Serializable {
	private static final long serialVersionUID = 1L;

	private final Random random = new Random();

	private AnimalSpeciesMap animals = new AnimalSpeciesMap();
	private Collection<Animal> deadAnimals = new HashSet<Animal>();
	private Collection<Animal> newbornAnimals =new HashSet<Animal>();

	private Rain rain;
	private RainController rainController = new RandomRainController();

	private int grass;
	private Calendar date;

	private static final List<Specie> DEFAULT_SPECIES = Arrays.asList(
			new Gazelle(),
			new Leopard(),
			new Lion(),
			new Zebra()
	);

	private static final IntRange DEFAULT_GRASS_RANGE = new IntRange(12000, 20000);

	public Savanna() {
		this(DEFAULT_SPECIES, DEFAULT_GRASS_RANGE);
	}

	public Savanna(Collection<Specie> species, IntRange grassRange) {
		this.grass = grassRange.getRandom();
		this.date = Calendar.getInstance();

		for (Specie specie : species) {
			int num = specie.getSpawnRange().getRandom();
			while (num-- > 0) {
				animals.add(new Animal(this, specie));
			}
		}

		setRain(rainController.update(this));
	}

	public void doTick() {
		date.add(Calendar.DAY_OF_MONTH, 1);

		this.grass += rain.getGrassGrowth();
		setRain(rainController.update(this));

		for (Animal animal : animals.get(Specie.class)) {
			animal.doTick();
		}

		animals.removeAll(deadAnimals);
		deadAnimals.clear();

		animals.addAll(newbornAnimals);
		newbornAnimals.clear();
	}

	public boolean eatGrass(int amount) {
		if (amount > grass) {
			return false;
		}

		grass -= amount;
		return true;
	}

	public int getGrass() {
		return grass;
	}

	public Rain getRain() {
		return rain;
	}

	public void setRain(Rain rain) {
		this.rain = rain;
	}

	public void setRainController(RainController rainController) {
		this.rainController = rainController;
	}

	public AnimalSpeciesMap getAnimals() {
		return animals;
	}

	public Collection<Animal> getDeadAnimals() {
		return deadAnimals;
	}

	public Collection<Animal> getNewbornAnimals() {
		return newbornAnimals;
	}

	public Calendar getDate() {
		return date;
	}

	public Random getRandom() {
		return random;
	}
}
