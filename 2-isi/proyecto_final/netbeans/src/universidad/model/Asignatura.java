package universidad.model;

import java.util.ArrayList;
import java.util.List;

public abstract class Asignatura {

    private int codigo;
    private String nombre;
    private final Titulacion titulacion;
    private ArrayList<Subgrupo> subgrupos = new ArrayList<Subgrupo>();

    public Asignatura(Titulacion titulacion, String nombre, int codigo) {
        this.titulacion = titulacion;
        this.nombre = nombre;
        this.codigo = codigo;
    }

    public List<Subgrupo> getSubgrupos() {
        return subgrupos;
    }

    public int getCodigo() {
        return codigo;
    }

    public String getNombre() {
        return nombre;
    }

    public Subgrupo crearSubgrupo(int alumnosMaximos, Profesor profesor) {
        Subgrupo subgrupo = new Subgrupo(this, subgrupos.size() + 1, alumnosMaximos, profesor);
        subgrupos.add(subgrupo);
        return subgrupo;
    }
    
    public String toString() {
        return codigo + "- " + nombre;
    }
}
