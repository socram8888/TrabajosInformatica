package universidad.model;

import java.util.ArrayList;
import java.util.List;

public class Alumno extends UsuarioRegistrado {
    private ArrayList<Subgrupo> subgrupos = new ArrayList<Subgrupo>();
    private Titulacion titulacion;

    public Alumno(Universidad universidad, String nombre, String apellidos, String usuario, byte[] passHash, Titulacion titulacion) {
        super(universidad, nombre, apellidos, usuario, passHash);
        this.titulacion = titulacion;
    }
    
    public Titulacion getTitulacion() {
        return this.titulacion;
    }

    public List<Subgrupo> getSubgrupos() {
        return this.subgrupos;
    }

    public List<Asignatura> getAsignaturasTitulacion() {
        return this.titulacion.getAsignaturas();
    }

    public boolean comprobarPlazoMatriculacion() {
        return this.titulacion.comprobarPlazoMatriculacion();
    }

    public boolean desmatricularseSubgrupo(Subgrupo subgrupo) {
        boolean eliminado = subgrupos.remove(subgrupo);

        if (eliminado) {
            eliminado = subgrupo.desmatricularAlumno(this);
        }

        return eliminado;
    }

    public boolean registrarseSubgrupo(Subgrupo subgrupo) {
        boolean registrado = subgrupos.contains(subgrupo);

        if (!registrado) {
            registrado = subgrupo.registrarAlumno(this);
            if (registrado) {
                subgrupos.add(subgrupo);
            }
        }

        return registrado;
    }
    
    @Override
    public String getEmail() {
        return getUsuario() + "@alumni.uv.es";
    }
    
    public boolean estaMatriculado(Asignatura asig) {
        for (Subgrupo subgrupo : subgrupos) {
            if (subgrupo.getAsignatura() == asig) {
                return true;
            }
        }

        return false;
    }
}