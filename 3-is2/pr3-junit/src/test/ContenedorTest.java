package test;

import static org.junit.Assert.*;

import org.junit.Test;
import P3.*;

public class ContenedorTest {

	@Test
	public void testContenedorIntInt() {
		// Voy a testear el funcionamiento de la creación
		// de un contenedor usando el constructor con parámetros,
		// siendo el primer argumento el ancho y el segundo el alto
		Contenedor c = new Contenedor(10,20);
		int ancho = c.getAncho();
		int alto = c.getAlto();
		// Comprobación:
		assertTrue(ancho == 10);
		assertTrue(alto == 20);

		// Falla el test porque los asserts no se cumplen
	}

	@Test
	public void testContenedorZero() {
		Contenedor c = new Contenedor(0,0);
		assertTrue(c.getAncho() == 0);
		assertTrue(c.getAlto() == 0);
	}

	@Test
	public void testContenedorV2() {
		Contenedor c = new Contenedor(12, 34);
		assertEquals(c.getAncho(), 12);
		assertEquals(c.getAlto(), 34);
	}
	
	@Test
	public void testContenedorV3() {
		Contenedor c = new Contenedor(12, 34);
		if (c.getAncho() != 12)
			fail("Width not allow");
		if(c.getAlto() != 34)
			fail("Ilegal Height");
	}
	
	// Task 4
	@Test
	public void testCalcularPerimetro() {
		Contenedor c = new Contenedor(20,40);
		assertEquals(c.getAncho()*2 + c.getAlto()*2, c.calcularPerimetro());
	}

	@Test
	public void testCalcularPerimetro2() {
		Contenedor c = new Contenedor(0,0);
		assertEquals(c.getAncho()*2 + c.getAlto()*2, c.calcularPerimetro());
	}
	
	
	// Task 5
	@Test
	public void testCalculaNumPaquete() {
		Contenedor c = new Contenedor(4, 9);
		Paquete p = new Paquete(2, 3);
		assertEquals(2 * 3, c.calculaNumPaquete(p));
	}

	@Test(expected=IllegalArgumentException.class)
	public void testCalculaNumPaqueteNull() {
		Contenedor c = new Contenedor(4, 9);
		c.calculaNumPaquete(null);
	}

	@Test
	public void testCalculaNumPaquete0() {
		Contenedor c = new Contenedor(0, 2);
		Paquete p = new Paquete(2, 3);
		assertEquals(0, c.calculaNumPaquete(p));
	}

	@Test
	public void testCalculaNumPaquete3x8() {
		Contenedor c = new Contenedor(3, 8);
		Paquete p = new Paquete(2, 3);
		assertEquals(3, c.calculaNumPaquete(p)); // dos horizontal, uno vertical
	}
	
	
	// Task 6

	@Test
	public void testSobrantePaquete() {
		Contenedor c = new Contenedor(3, 8);
		Paquete p = new Paquete(2, 3);
		assertEquals(c.sobrantePaquete(p), 12);
	}

	@Test
	public void testSobrantePaqueteEx() {
		Contenedor c = new Contenedor(4, 9);
		Paquete p = new Paquete(2, 3);
		assertEquals(0, c.sobrantePaquete(p));
	}

	@Test(expected=IllegalArgumentException.class)
	public void testSobrantePaqueteNull() {
		Contenedor c = new Contenedor(4, 9);
		c.sobrantePaquete(null);
	}

}
