package P3;
/**
 * Clase Contenedor definiendo los atributos y los constructores.
 */
public class Contenedor {
	private int ancho;	// ancho del contenedor
	private int alto;	// alto del contenedor
	private int paquetesAncho;	// ancho de los paquetes que contiene
	private int paquetesAlto;	// alto de los paquetes que contiene
	private int sobranteAncho;
	private int sobranteAlto;
	
	/**
	 * Costructor sin parametros
	 */
	public Contenedor(){
		this.setAncho(0);
		this.setAlto(0);
	}
	
	/**
	 * Constructor con parametros
	 * 
	 * @param an, anchura del contenedor
	 * @param al, altura del contenedor
	 */
	public Contenedor(int an, int al){
		this.setAncho(an);
		this.setAlto(al);
	}

	/**
	 * @return la anchura del contenedor
	 */
	public int getAncho() {
		return ancho;
	}

	/**
	 * @param an, anchura del contenedor
	 */
	public void setAncho(int an) {
		this.ancho = an;
	}

	/**
	 * @return la altura del contenedor
	 */
	public int getAlto() {
		return alto;
	}

	/**
	 * @param al, altura del contenedor
	 */
	public void setAlto(int al) {
		this.alto = al;
	}
	
	/**
	 * Metodo para calcular y devolver el area del conteneror
	 * @return area del contenedor
	 */
	public int calcularArea(){
		return(this.ancho*this.alto);
	}
	
	/**
	 * Metodo para calcular y devolver el perimetro del contenedor
	 * @return perimetro del contenedor
	 */
	public int calcularPerimetro(){
		return((this.ancho+this.alto)*2);
	}
	
	/**
	 * Metodo que muestra por pantalla el area del contenedor
	 */
	public void mostrarArea(){
		System.out.println("Area: "+this.calcularArea()+" m^2");
	}
	
	/**
	 * Metodo que muestra por pantalla el perimetro del contenedor
	 */
	public void mostrarPerimetro(){
		System.out.println("Perimetro: "+this.calcularPerimetro()+" m");
	}
	
	/**
	 * Metodo que muestra por pantalla el ancho y el alto del contenedor
	 */
	public void mostrarContenedor(){
		System.out.println("Ancho: "+this.getAncho()+" m");
		System.out.println("Alto: "+this.getAlto()+" m");
	}
	
	/**
	 * Metodo para calcular el numero de paquetes que puede contener el contenedor
	 * @param p2, es un objeto de tipo Paquete
	 * @param paquetesAncho, es el numero de paquetes que caben a lo ancho del contenedor
	 * @param paquetesAlto, es el numero de paquetes que caben a lo alto del contenedor
	 * @return numero de paquetes totales que caben en el contenedor
	 */
	public int calculaNumPaquete(Paquete p2){
		
		paquetesAncho = this.ancho/p2.getAncho();
		paquetesAlto = this.alto/p2.getAlto();
		
		return(paquetesAncho*paquetesAlto);
	}
	
	/**
	 * Metodo para calcular el espacio sobrante en el contenedor, introduciento el n�mero m�ximo de paquetes del tama�o del paquete introducir como par�metro
	 * @param p2, es un objeto de tipo Paquete
	 * @param sobranteAncho, metros que sobran de ancho en el contenedor
	 * @param sobranteAlto, metros que sobran de alto en el contenedor
	 * @return Area del espacio sobrante que hay a lo alto del contenedor + Area del espacio sobrante a lo ancho + Area del hueco sobrante
	 */
	public int sobrantePaquete(Paquete p2){
		
		sobranteAncho = this.ancho - (this.paquetesAncho*p2.getAncho());
		sobranteAlto = this.alto - (this.paquetesAlto*p2.getAlto());
		
		return((paquetesAncho*p2.getAncho()*sobranteAlto)+(paquetesAlto*p2.getAlto()*sobranteAncho)+(sobranteAncho*sobranteAlto));
	}
}
