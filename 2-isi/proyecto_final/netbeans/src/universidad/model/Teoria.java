package universidad.model;

public class Teoria extends Asignatura {

    private Laboratorio laboratorio;

    public Teoria(Titulacion titulacion, String nombre, int codigo) {
        super(titulacion, nombre, codigo);
    }

    public Laboratorio getLaboratorio() {
        return this.laboratorio;
    }
    
    public void setLaboratorio(Laboratorio laboratorio) {
        this.laboratorio = laboratorio;
    }
}
