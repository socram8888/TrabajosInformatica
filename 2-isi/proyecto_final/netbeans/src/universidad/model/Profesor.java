package universidad.model;

import java.util.ArrayList;
import java.util.List;

public class Profesor extends UsuarioRegistrado {
    private ArrayList<Subgrupo> subgrupos = new ArrayList<Subgrupo>();

    public Profesor(Universidad universidad, String nombre, String apellidos, String usuario, byte[] passHash) {
        super(universidad, nombre, apellidos, usuario, passHash);
    }

    public void addSubgrupo(Subgrupo subgrupo) {
        subgrupos.add(subgrupo);
    }
    
    public List<Subgrupo> getSubgrupos() {
        return subgrupos;
    }

    @Override
    public String getEmail() {
        String nombreCompleto = getNombre() + " " + getApellidos();
        return nombreCompleto.toLowerCase().replaceAll("á", "a").replaceAll("é", "e").replaceAll("í", "i").replaceAll("ú", "u").replaceAll("ñ", "n").replaceAll("[^a-z]+", ".") + "@uv.es";
    }
}