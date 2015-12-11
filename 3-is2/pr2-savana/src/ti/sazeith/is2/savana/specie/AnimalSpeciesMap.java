package ti.sazeith.is2.savana.specie;

import java.util.HashMap;
import java.util.HashSet;
import java.util.Map;
import java.util.Set;

import ti.sazeith.is2.savana.Animal;

public class AnimalSpeciesMap {
	private final Map<Class<? extends Specie>, Set<Animal>> animalsBySpecie = new HashMap<>();

	public Set<Animal> get(Class<? extends Specie> specie) {
		Set<Animal> set = animalsBySpecie.get(specie);
		if (set == null) {
			set = new HashSet<>();
			animalsBySpecie.put(specie, set);
		}
		return set;
	}

	public boolean add(Animal animal) {
		Class<? extends Specie> specie = animal.getSpecie().getClass();

		if (!get(specie).add(animal)) {
			return false;
		}

		while (specie != Specie.class) {
			specie = (Class<? extends Specie>) specie.getSuperclass();
			get(specie).add(animal);
		}

		return true;
	}

	public void addAll(Iterable<Animal> iterable) {
		for (Animal animal : iterable) {
			add(animal);
		}
	}

	public boolean remove(Animal animal) {
		Class<? extends Specie> specie = animal.getSpecie().getClass();

		Set<Animal> set = animalsBySpecie.get(specie);
		if (set == null || !set.remove(animal)) {
			return false;
		}

		while (specie != Specie.class) {
			specie = (Class<? extends Specie>) specie.getSuperclass();
			animalsBySpecie.get(specie).remove(animal);
		}

		return true;
	}

	public void removeAll(Iterable<Animal> iterable) {
		for (Animal animal : iterable) {
			remove(animal);
		}
	}
}
