/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package ti.s4x8.eu.p1;

import java.util.HashSet;
import java.util.Set;

/**
 *
 * @author Marcos Vives Del Sol
 */
public class Hospital {
    private String name;
    private Set<Medic> medics;
    int ticket = 0;

    public Hospital(String name) {
        this(name, new HashSet<Medic>());
    }

    public Hospital(String name, Set<Medic> medics) {
        this.name = name;
        this.medics = medics;
    }

    /**
     * Returns next patient ticket or ID.
     * @return new id.
     */
    public int getNextTicket() {
        return ++ticket;
    }

    /**
     * Creates a new registered medic for this hospital
     * @param person Person
     * @param speciality Medic's speciality
     * @return New medic
     */
    public Medic createMedic(AbstractPerson person, String speciality) {
        Medic medic = new Medic(person, this, speciality);
        medics.add(medic);
        return medic;
    }

    /**
     * @return List of registered medics
     */
    public Set<Medic> getMedics() {
        return medics;
    }
}
