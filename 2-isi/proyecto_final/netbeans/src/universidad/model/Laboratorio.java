package universidad.model;

public class Laboratorio extends Asignatura {

    private Teoria teoria;

    public Laboratorio(Titulacion titulacion, Teoria teoria, int codigo) {
        super(titulacion, teoria.getNombre() + " (laboratorio)", codigo);
    }

    public Teoria getTeoria() {
        return teoria;
    }
}
