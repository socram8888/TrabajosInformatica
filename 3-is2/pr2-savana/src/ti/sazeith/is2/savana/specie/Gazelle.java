package ti.sazeith.is2.savana.specie;

import ti.sazeith.is2.savana.IntRange;
import ti.sazeith.is2.savana.ai.*;
import ti.sazeith.is2.savana.weather.Rain;

/**
 * Gazelle
 * @author alumno
 */
public class Gazelle extends Herbivore {
	public Gazelle() {
		super(
				"Gacela",
				new IntRange(50, 100),
				new IntRange(360, 460)
		);

		add(new DieAI(50f / 1000f));
		add(new DrownAI(Rain.HEAVY, 0.2f));
		add(new EatGrassAI(new IntRange(6, 14)));
		add(new BreedAI(140f / 1000f));
	}
}
