package universidad.ctrl;

import java.util.List;
import universidad.model.Alumno;
import universidad.model.Asignatura;
import universidad.model.Subgrupo;
import universidad.model.Titulacion;
import universidad.model.Universidad;
import universidad.model.UsuarioRegistrado;

public class Usuario {

    private final Universidad universidad;
    private UsuarioRegistrado usuarioRegistrado;

    public Usuario(Universidad universidad) {
        this.universidad = universidad;
    }

    public void desmatricularseSubgrupo(Object subgrupo) {
        throw new UnsupportedOperationException();
    }

    public List listarTitulaciones() {
        return universidad.getTitulaciones();
    }

    public boolean comprobarPlazoMatriculacion() {
        return ((Alumno) usuarioRegistrado).getTitulacion().comprobarPlazoMatriculacion();
    }

    public List listarAsignaturasTitulacion(Object titulacion) {
        return ((Titulacion) titulacion).getAsignaturas();
    }

    public List getSubgruposAsignatura(Object asignatura) {
        return ((Asignatura) asignatura).getSubgrupos();
    }

    public Object getProfesorSubgrupo(Object subgrupo) {
        return ((Subgrupo) subgrupo).getProfesor();
    }

    public void cancelarMatricula() {
        throw new UnsupportedOperationException();
    }

    public void cerrarSesion() {
        this.usuarioRegistrado = null;
        universidad.realizarBackup();
    }

    public boolean matricularSubgrupo(Object subgrupo) {
        return ((Alumno) usuarioRegistrado).registrarseSubgrupo((Subgrupo) subgrupo);
    }

    public List listarAsignaturasTitulacionAlumno() {
        return ((Alumno) usuarioRegistrado).getAsignaturasTitulacion();
    }

    public boolean iniciarSesion(String usuario, String pass) {
        UsuarioRegistrado ur = universidad.iniciarSesion(usuario, pass);

        if (ur != null) {
            this.usuarioRegistrado = ur;
            return true;
        }

        return false;
    }

    public List getHorarioSubgrupo(Object subgrupo) {
        return ((Subgrupo) subgrupo).getFranjasHorarias();
    }
    
    public boolean isAlumno() {
        return usuarioRegistrado instanceof Alumno;
    }
    
    public boolean estaAlumnoMatriculado(Object asig) {
        return ((Alumno) usuarioRegistrado).estaMatriculado((Asignatura) asig);
    }
    
    public UsuarioRegistrado getUsuarioActual() {
        return usuarioRegistrado;
    }
    
    public Titulacion getTitulacionAlumno() {
        return ((Alumno) usuarioRegistrado).getTitulacion();
    }
}
