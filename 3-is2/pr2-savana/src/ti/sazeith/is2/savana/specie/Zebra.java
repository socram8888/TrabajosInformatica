package ti.sazeith.is2.savana.specie;

import ti.sazeith.is2.savana.IntRange;
import ti.sazeith.is2.savana.ai.*;

/**
 * Zebra
 * @author alumno
 */
public class Zebra extends Herbivore {
	public Zebra() {
		super(
				"Zebra",
				new IntRange(50, 100),
				new IntRange(100, 180)
		);

		add(new DieAI(20f / 1000f));
		add(new EatGrassAI(new IntRange(10, 20)));
		add(new BreedAI(120f / 1000f));
	}
}
