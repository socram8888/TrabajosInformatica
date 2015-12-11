package ti.sazeith.is2.savana.disaster;

import ti.sazeith.is2.savana.Savanna;

public abstract class Disaster {
	protected final Savanna savanna;
	protected final String name;

	public Disaster(Savanna savanna, String name) {
		this.savanna = savanna;
		this.name = name;
	}

	public void prepare() { }

	public abstract void update();

	public String getName() {
		return name;
	}
}
