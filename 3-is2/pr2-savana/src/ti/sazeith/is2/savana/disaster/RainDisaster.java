package ti.sazeith.is2.savana.disaster;

import ti.sazeith.is2.savana.Savanna;
import ti.sazeith.is2.savana.weather.FixedRainController;
import ti.sazeith.is2.savana.weather.Rain;

public class RainDisaster extends Disaster {
	private final Rain rain;

	public RainDisaster(Savanna savanna, String name, Rain rain) {
		super(savanna, name);
		this.rain = rain;
	}

	@Override
	public void prepare() {
		savanna.setRainController(new FixedRainController(rain));
	}

	@Override
	public void update() {
		// TODO Auto-generated method stub
		
	}
}
