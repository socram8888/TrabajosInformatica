package universidad.model;

import java.util.Date;
import java.util.ArrayList;
import universidad.model.Alumno;
import universidad.model.Asignatura;
import java.util.List;

public class Titulacion {
    private final String nombre;
    private Date aperturaMatriculacion;
    private Date cierreMatriculacion;
    private final int codigo;
    private final ArrayList<Alumno> alumno = new ArrayList<Alumno>();
    private final Universidad universidad;
    private final ArrayList<Asignatura> asignaturas = new ArrayList<Asignatura>();

    public Titulacion(Universidad universidad, String nombre, int codigo, Date aperturaMatriculacion, Date cierreMatriculacion) {
        this.universidad = universidad;
        this.nombre = nombre;
        this.aperturaMatriculacion = aperturaMatriculacion;
        this.cierreMatriculacion = cierreMatriculacion;
        this.codigo = codigo;
    }

    public List<Asignatura> getAsignaturas() {
        return asignaturas;
    }

    public Date getAperturaMatriculacion() {
        return this.aperturaMatriculacion;
    }

    public Date getCierreMatriculacion() {
        return cierreMatriculacion;
    }

    public boolean comprobarPlazoMatriculacion() {
        Date now = new Date();
        return now.compareTo(aperturaMatriculacion) >= 0 && now.compareTo(cierreMatriculacion) <= 0;
    }

    public Universidad getUniversidad() {
        return this.universidad;
    }
        
    public String getNombre() {
        return nombre;
    }

    public Teoria crearTeoria(String nombre) {
        Teoria teoria = new Teoria(this, nombre, codigo * 100 + asignaturas.size() + 1);
        asignaturas.add(teoria);
        return teoria;
    }

    public Laboratorio crearLaboratorio(Teoria teoria) {
        Laboratorio laboratorio = new Laboratorio(this, teoria, codigo * 100 + asignaturas.size() + 1);
        asignaturas.add(laboratorio);
        teoria.setLaboratorio(laboratorio);
        return laboratorio;
    }
    
    public String toString() {
        return codigo + "- " + nombre;
    }
}