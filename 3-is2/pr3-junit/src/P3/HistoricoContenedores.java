package P3;
/**
 * Clase HistoricoContenedores que 
 * permite gestionar los contenedores mediante un vector.
 * 
 */
import java.util.Vector;

public class HistoricoContenedores {
	private Vector<Contenedor2> vecContenedores;
	private int contador;
	
	/**
	 * Constructor sin parametros
	 * @param vecContenedores, vector de maximo 100 objetos tipo Contenedor2
	 * @param contador, un entero para llevar la cuenta del numero de contenedores activos
	 */
	public HistoricoContenedores(){
		vecContenedores = new Vector<Contenedor2>(100);
		this.contador = 0;
	}
	
	/**
	 * Metodo para a�adir un Contenedor2 al vector
	 * @param c4, objeto tipo Contenedor2
	 */
	public void sumarContenedor(Contenedor2 c4)
	{
		if (vecContenedores.size() >= 100) {
			throw new HistoricFullException();
		}
		vecContenedores.add(c4);
		contador++;
	}
	
	/**
	 * Metodo para eliminar el �ltimo Contenedor2 a�adido al vector
	 */
	public void eliminarContenedor()
	{
		vecContenedores.remove(contador);
		contador--;
	}

	/**
	 * Metodo para a�adir un paquete al ultimo contenedor introducido
	 * @param p2, un objeto de tipo Paquete
	 */
	public void sumarPaquete(Paquete p2)
	{
		vecContenedores.elementAt(contador).sumarPaquete(p2);
	}
	
	/**
	 * @return el numero de contenedores activos actualmente
	 */
	public int numeroContenedores()
	{
		return contador;
	}
	
	/**
	 * M�todo que devuelve el �ltimo contenedor introducido
	 * @return el �ltimo contenedor introducido
	 */
	public Contenedor2 ultimoContenedor()
	{
		return vecContenedores.elementAt(vecContenedores.size() - 1);
	}
	
	/**
	 * Metodo para calcular el contenedor mas grande
	 * @return el contenedor mas grande
	 */
	public Contenedor2 contenedorMasGrande()
	{
		int areaMax = 0;
		int posicion = 0;
		for(int i=0; i<vecContenedores.size(); i++)
		{
			if(areaMax < vecContenedores.elementAt(i).calcularArea())
			{
				areaMax = vecContenedores.elementAt(i).calcularArea();
				posicion = i;
			}
		}
		
		return vecContenedores.elementAt(posicion);
	}
	
	/**
	 * Metodo para calcular el contenedor mas peque�o
	 * @return el contenedor mas peque�o
	 */
	public Contenedor2 contenedorMasPequeno()
	{
		int areaMin = vecContenedores.elementAt(0).calcularArea();
		int posicion = 0;
		for(int i=0; i<vecContenedores.size(); i++)
		{
			if(areaMin > vecContenedores.elementAt(i).calcularArea())
			{
				areaMin = vecContenedores.elementAt(i).calcularArea();
				posicion = i;
			}
		}
		
		return vecContenedores.elementAt(posicion);
	}
}
