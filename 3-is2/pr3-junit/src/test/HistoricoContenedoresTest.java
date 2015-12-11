package test;

import static org.junit.Assert.*;

import org.junit.Test;
import P3.*;

public class HistoricoContenedoresTest {

	// Task A
	@Test(expected = IllegalArgumentException.class)
	public void testSumarPaqueteNull() {
		HistoricoContenedores hc = new HistoricoContenedores();
		hc.sumarContenedor(new Contenedor2(1, 1));
		hc.sumarPaquete(null);
	}

	@Test(expected = IllegalStateException.class)
	public void testSumarPaqueteVacio() {
		HistoricoContenedores hc = new HistoricoContenedores();
		hc.sumarPaquete(new Paquete(1, 1));
	}

	@Test
	public void testSumarPaqueteOK() {
		Contenedor2 c = new Contenedor2(4, 4);
		c.sumarPaquete(new Paquete(1, 1));

		HistoricoContenedores hc = new HistoricoContenedores();
		hc.sumarContenedor(c);
		hc.sumarPaquete(new Paquete(1, 1));

		assertEquals(2, c.contarPaquetes());
	}

	// Task B
	@Test
	public void testContenedorMasGrande() {
		Contenedor2 mayor = new Contenedor2(4, 3);

		HistoricoContenedores hc = new HistoricoContenedores();
		hc.sumarContenedor(new Contenedor2(1, 1));
		hc.sumarContenedor(mayor);
		hc.sumarContenedor(new Contenedor2(2, 1));
		hc.sumarContenedor(new Contenedor2(3, 3));
	
		assertEquals(mayor, hc.contenedorMasGrande());
	}

	@Test
	public void testContenedorMasGrande2() {
		Contenedor2 mayor = new Contenedor2(1, 1);

		HistoricoContenedores hc = new HistoricoContenedores();
		hc.sumarContenedor(new Contenedor2(1, 2));
		hc.sumarContenedor(mayor);
		hc.sumarContenedor(new Contenedor2(2, 1));
		hc.sumarContenedor(new Contenedor2(3, 3));

		assertNotEquals(mayor, hc.contenedorMasGrande());
	}

	// Task C
	/*
	public void testSumarContenedor1000() {
		HistoricoContenedores hc = new HistoricoContenedores();

		// No falla porque no hay ninguna comprobación implementada en el código y se está empleando un vector dinámico
		for (int i = 0; i < 1000; i++) {
			hc.sumarContenedor(new Contenedor2());
		}
	}
	*/
	
	// Task E
	@Test(expected = HistoricFullException.class)
	public void testSumarContenedor1000() {
		HistoricoContenedores hc = new HistoricoContenedores();
		for (int i = 0; i < 1000; i++) {
			hc.sumarContenedor(new Contenedor2());
		}
	}
}
