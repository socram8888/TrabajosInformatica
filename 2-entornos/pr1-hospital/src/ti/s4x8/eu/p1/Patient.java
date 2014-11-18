/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package ti.s4x8.eu.p1;

/**
 *
 * @author Marcos Vives Del Sol
 */
public class Patient extends DelegatingPerson {
    private Medic medic;
    private int id;

    public Patient(AbstractPerson person, Medic medic) {
        super(person);
        this.medic = medic;
    }

    /**
     * @return Medic
     */
    public Medic getMedic() {
        return medic;
    }

    /**
     * Sets patient ID
     * @param id 
     */
    public void setId(int id) {
        this.id = id;
    }

    /**
     * @return Patient ID
     */
    public int getId() {
        return id;
    }
}
