package test;

import static org.junit.Assert.*;

import org.junit.Test;
import P3.*;

public class Contenedor2Test {

	@Test
	public void testSumarPaqueteOK() {
		Contenedor2 c = new Contenedor2(10, 10);
		c.sumarPaquete(new Paquete(1, 1));
		c.sumarPaquete(new Paquete(2, 2));
		assertEquals(c.contarPaquetes(), 2);
	}

	@Test(expected=IllegalArgumentException.class)
	public void testSumarPaqueteExcesivo() {
		Contenedor2 c = new Contenedor2(10, 10);
		c.sumarPaquete(new Paquete(11, 11));
	}

	@Test(expected=IllegalArgumentException.class)
	public void testSumarPaqueteNull() {
		Contenedor2 c = new Contenedor2(10, 10);
		c.sumarPaquete(null);
	}

	@Test
	public void testContarPaquetesZero() {
		Contenedor2 c = new Contenedor2(10, 10);
		assertEquals(c.contarPaquetes(), 0);
	}

	@Test
	public void testContarPaquetesTwo() {
		Contenedor2 c = new Contenedor2(10, 10);
		c.sumarPaquete(new Paquete(1, 1));
		c.sumarPaquete(new Paquete(2, 2));
		assertEquals(c.contarPaquetes(), 2);
	}

	@Test
	public void testCalculaAreaPaquete() {
		Contenedor2 c = new Contenedor2(10, 10);
		Paquete p = new Paquete(2, 2);
		assertEquals(c.calculaAreaPaquete(p), 4);
	}

	@Test
	public void testAreaTotalPaquetes() {
		Contenedor2 c = new Contenedor2(10, 10);
		c.sumarPaquete(new Paquete(1, 1));
		c.sumarPaquete(new Paquete(2, 2));
		assertEquals(c.areaTotalPaquetes(), 1 * 1 + 2 * 2);
	}

	@Test
	public void testEspacioSobranteVacio() {
		Contenedor2 c = new Contenedor2(3, 3);
		assertEquals(c.calcularArea(), c.espacioSobrante());
	}

	@Test
	public void testEspacioSobranteMedio() {
		Contenedor2 c = new Contenedor2(3, 3);
		c.sumarPaquete(new Paquete(1, 1));
		c.sumarPaquete(new Paquete(2, 2));
		assertEquals(4, c.espacioSobrante());
	}
	
	@Test
	public void testEspacioSobranteLleno() {
		Contenedor2 c = new Contenedor2(3, 3);
		c.sumarPaquete(new Paquete(3, 3));
		assertEquals(0, c.espacioSobrante());
	}

}
