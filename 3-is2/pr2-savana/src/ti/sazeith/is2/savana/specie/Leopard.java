package ti.sazeith.is2.savana.specie;

import ti.sazeith.is2.savana.IntRange;
import ti.sazeith.is2.savana.ai.*;
import ti.sazeith.is2.savana.weather.Rain;

/**
 * Leopards
 * @author alumno
 */
public class Leopard extends Predator {
	public Leopard() {
		super(
				"Leopard",
				null,
				new IntRange(8, 12)
		);

		add(new DieAI(35f / 1000f));
		add(new DrownAI(Rain.HEAVY, 0.2f));
		add(new EatHerbivoreAI(new IntRange(0, 1)));
		add(new BreedAI(40f / 1000f));
	}
}
