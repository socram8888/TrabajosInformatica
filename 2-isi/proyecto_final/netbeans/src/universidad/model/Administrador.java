package universidad.model;

public class Administrador extends UsuarioRegistrado {

    public Administrador(Universidad universidad, String nombre, String apellidos, String usuario, byte[] passHash) {
        super(universidad, nombre, apellidos, usuario, passHash);
    }

    @Override
    public String getEmail() {
        String nombreCompleto = getNombre() + getApellidos();
        return nombreCompleto.toLowerCase().replaceAll("[^A-Z]+", "_") + "@sec.uv.es";
    }
}