package universidad.model;

import java.util.Date;
import java.util.ArrayList;
import universidad.model.Subgrupo;

public class FranjaHoraria {
	private Date inicio;
	private int duracion;
	private ArrayList<Subgrupo> subgrupos = new ArrayList<Subgrupo>();
}