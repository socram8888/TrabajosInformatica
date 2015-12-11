package universidad.model;

import java.security.MessageDigest;

public abstract class UsuarioRegistrado {
    private String nombre;
    private String apellidos;
    private String usuario;
    private byte[] passHash;
    private Universidad universidad;

    protected UsuarioRegistrado(Universidad universidad, String nombre, String apellidos, String usuario, byte[] passHash) {
        this.nombre = nombre;
        this.apellidos = apellidos;
        this.usuario = usuario;
        this.passHash = passHash;
        this.universidad = universidad;
    }

    public boolean comprobarInicioSesion(String usuario, byte[] passHash) {
        return this.usuario.equals(usuario) && MessageDigest.isEqual(this.passHash, passHash);
    }

    public Universidad getUniversidad() {
        return universidad;
    }

    public String getNombre() {
        return nombre;
    }

    public String getApellidos() {
        return apellidos;
    }
    
    public String getUsuario() {
        return usuario;
    }
    
    public abstract String getEmail();
    
    @Override
    public String toString() {
        return nombre + " " + apellidos + " (" + getEmail() + ")";
    }
}