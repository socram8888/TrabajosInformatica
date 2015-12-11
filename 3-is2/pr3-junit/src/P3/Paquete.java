package P3;
/**
 * Clase Paquete definiendo los atributos, los constructores y los metodos
 * 
 */
public class Paquete {
	private int ancho;
	private int alto;
	
	/**
	 * Constructor sin parametros
	 */
	public Paquete(){
		this.setAncho(0);
		this.setAlto(0);
	}
	
	/**
	 * Constructor con parametros
	 * @param an, ancho del paquete
	 * @param al, alto del paquete
	 */
	public Paquete(int an, int al){
		this.setAncho(an);
		this.setAlto(al);
	}

	/**
	 * @return la anchura del paquete
	 */
	public int getAncho() {
		return ancho;
	}

	/**
	 * @param an, anchura del paquete
	 */
	public void setAncho(int an) {
		this.ancho = an;
	}

	/**
	 * @return la altura del paquete
	 */
	public int getAlto() {
		return alto;
	}

	/**
	 * @param al, altura del paquete
	 */
	public void setAlto(int al) {
		this.alto = al;
	}
	
	/**
	 * Metodo para calcular el area del paquete
	 * @return area del paquete
	 */
	public int calcularArea(){
		return(this.ancho*this.alto);
	}
	
	/**
	 * Metodo para mostrar por pantalla el area del paquete
	 */
	public void mostrarArea(){
		System.out.println("Area: "+this.calcularArea()+" m^2");
	}
	
	/**
	 * Metodo para mostrar por pantalla el ancho y el alto del paquete
	 */
	public void mostrarPaquete(){
		System.out.println("Ancho: "+this.getAncho()+" m");
		System.out.println("Alto: "+this.getAlto()+" m");
	}
}
