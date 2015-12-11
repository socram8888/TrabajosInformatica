package ti.sazeith.is2.savana.specie;

import ti.sazeith.is2.savana.IntRange;
import ti.sazeith.is2.savana.ai.*;

/**
 * Lion
 * @author alumno
 */
public class Lion extends Predator {
	public Lion() {
		super(
				"Lion",
				null,
				new IntRange(10, 20)
		);

		add(new DieAI(0.015f));
		add(new EatHerbivoreAI(new IntRange(1, 2)));
		add(new BreedAI(0.02f));
	}
}
