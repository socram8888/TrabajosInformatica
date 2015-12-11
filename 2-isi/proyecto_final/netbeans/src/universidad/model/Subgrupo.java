package universidad.model;

import java.util.ArrayList;

public class Subgrupo {

    private final int alumnosMaximos;
    private final int codigo;
    private final Asignatura asignatura;
    private Profesor profesor;
    private final ArrayList<Alumno> alumnos = new ArrayList<Alumno>();
    private final ArrayList<FranjaHoraria> franjasHorarias = new ArrayList<FranjaHoraria>();

    public Subgrupo(Asignatura asignatura, int codigo, int alumnosMaximos, Profesor profesor) {
        this.asignatura = asignatura;
        this.codigo = codigo;
        this.alumnosMaximos = alumnosMaximos;
        this.profesor = profesor;
    }

    public boolean registrarAlumno(Alumno alumno) {
        boolean ok = alumnos.size() < alumnosMaximos;

        if (ok) {
            ok = alumnos.add(alumno);
        }
        return ok;
    }

    public boolean desmatricularAlumno(Alumno alumno) {
        return alumnos.remove(alumno);
    }

    public void setProfesor(Profesor profesor) {
        this.profesor = profesor;
        profesor.addSubgrupo(this);
    }

    public Profesor getProfesor() {
        return this.profesor;
    }

    public ArrayList<FranjaHoraria> getFranjasHorarias() {
        return this.franjasHorarias;
    }

    public int getCodigo() {
        return this.codigo;
    }

    public Asignatura getAsignatura() {
        return this.asignatura;
    }
    
    public String toString() {
        return asignatura.toString() + " (subgrupo " + codigo + ")";
    }
}
