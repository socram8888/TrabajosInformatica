/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package ti.s4x8.eu.p1;

import java.util.HashSet;
import java.util.Set;
import ti.s4x8.util.StringTools;

/**
 *
 * @author Marcos Vives Del Sol
 */
public class Medic extends DelegatingPerson {
    private String speciality;
    private Hospital hospital;
    private Set<Patient> patients = new HashSet<>();

    public Medic(AbstractPerson person, Hospital hospital, String speciality) {
        super(person);
        this.hospital = hospital;
        this.speciality = StringTools.sanitize(speciality);
    }

    /**
     * @return Medic's speciality
     */
    public String getSpeciality() {
        return speciality;
    }

    /**
     * @return Medic's hospital
     */
    public Hospital getHospital() {
        return hospital;
    }

    /**
     * @return Set with patients
     */
    public Set<Patient> getPatients() {
        return patients;
    }

    /**
     * Creates and registers a new patient for this doctor.
     * @param person Person
     * @return New patient
     */
    public Patient createPatient(AbstractPerson person) {
        Patient patient = new Patient(person, this);
        patient.setId(hospital.getNextTicket());
        patients.add(patient);
        return patient;
    }
}
