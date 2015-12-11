package P3;
/**
 * Clase Contenedor2 (similar a Contenedor) con la diferencia que
 * permite almacenar paquetes de distinto tama�o en cada contenedor
 * 
 */
import java.util.Vector;

public class Contenedor2 {
	private int ancho;	// ancho del contenedor
	private int alto;	// alto del contenedor
	public Vector<Paquete> vecPaquetes;
	private int totalAreaPaquetes;
	private int espacioSobranteContenedor;
	private int contador;
	
	/**
	 * Costructor sin parametros
	 */
	public Contenedor2(){
		this.setAncho(0);
		this.setAlto(0);
		vecPaquetes = new Vector<Paquete>(100);
	}
	
	/**
	 * Constructor con parametros
	 * 
	 * @param an, anchura del contenedor
	 * @param al, altura del contenedor
	 * @param vecPaquetes, vector con un maximo de 100 objetos tipo Paquete
	 */
	public Contenedor2(int an, int al){
		this.setAncho(an);
		this.setAlto(al);
		vecPaquetes = new Vector<Paquete>(100);
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
	 * Metodo para a�adir un paquete al vector
	 * @param p2, un objeto de tipo Paquete
	 * @param contador, un entero para llevar la cuenta del numero de paquetes introducidos
	 */
	public void sumarPaquete(Paquete p2){
		vecPaquetes.add(p2);
		contador++;
	}
	
	/**
	 * @return el tama�o del vector de paquetes
	 */
	public int contarPaquetes(){
		return contador;
	}
	
	/**
	 * @return area del contenedor
	 */
	public int calcularArea(){
		return(this.ancho*this.alto);
	}
	
	/**
	 * @return perimetor del contenedor
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
	 * Metodo que calcula el area del paquete introducido
	 * @param p2, un objeto de tipo Paquete
	 * @return el area del paquete calculada
	 */
	public int calculaAreaPaquete(Paquete p2){
		return p2.getAlto()*p2.getAncho();
	}
	
	/**
	 * Metodo que calcula el area total ocupada por los paquetes
	 * @return area total ocupada en el contenedor
	 */
	public int areaTotalPaquetes(){
		this.totalAreaPaquetes = 0;
		for(int i=0; i < vecPaquetes.size(); i++){
			this.totalAreaPaquetes = this.totalAreaPaquetes + calculaAreaPaquete(vecPaquetes.elementAt(i));
		}
		return totalAreaPaquetes;
	}
	
	/**
	 * Metodo que calcula el espacio sobrante en el contenedor
	 * @return espacio sobrante en el contenedor
	 */
	public int espacioSobrante(){
		this.espacioSobranteContenedor = this.calcularArea() - this.areaTotalPaquetes();
		
		return espacioSobranteContenedor;
	
	}
}
