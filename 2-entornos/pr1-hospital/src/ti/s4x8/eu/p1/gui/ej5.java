/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package ti.s4x8.eu.p1.gui;

import javax.swing.JOptionPane;
import ti.s4x8.eu.p1.Hospital;
import ti.s4x8.eu.p1.Medic;
import ti.s4x8.eu.p1.Patient;
import ti.s4x8.eu.p1.Person;
import ti.s4x8.eu.p1.Sex;
import ti.s4x8.util.StringTools;

/**
 *
 * @author Marcos Vives Del Sol
 */
public class ej5 {
    /**
     * @param args the command line arguments
     */
    public static void main(String[] args) {
        Hospital hospital = new Hospital("Unknown");

        do {
            String medicName = JOptionPane.showInputDialog("Enter doctor name");
            Person medicPerson = new Person(medicName, Sex.UNSPECIFIED, -1);

            String medicSpeciality = JOptionPane.showInputDialog("Enter speciality for " + medicPerson.getName());
            Medic medic = hospital.createMedic(medicPerson, medicSpeciality);

            do {
                String patientName = JOptionPane.showInputDialog("Enter patient name");
                Sex[] sexValues = Sex.values();
                Sex sex = sexValues[JOptionPane.showOptionDialog(null, "Enter patient sex", "Sex", JOptionPane.DEFAULT_OPTION, JOptionPane.QUESTION_MESSAGE, null, sexValues, Sex.UNSPECIFIED)];
                int age = -1;
                try {
                    age = Integer.parseInt(JOptionPane.showInputDialog("Enter patient age"));
                } catch (NumberFormatException e) { };

                Person patientPerson = new Person(patientName, sex, age);
                medic.createPatient(patientPerson);
            } while (JOptionPane.showConfirmDialog(null, "Would you want to add another patient for " + medic.getName() + "?", "Select option", JOptionPane.YES_NO_OPTION) == 0);
        } while (JOptionPane.showConfirmDialog(null, "Would you want to add another doctor?", "Select option", JOptionPane.YES_NO_OPTION) == 0);

        StringBuilder sb = new StringBuilder();
        for (Medic medic : hospital.getMedics()) {
            sb.append("Medic: ").append(medic.getName()).append(" (speciality: ").append(medic.getSpeciality()).append(")\n");

            for (Patient patient : medic.getPatients()) {
                sb.append(" - Patient ").append(patient.getId()).append("\n");
                sb.append("   - Name: ").append(patient.getName()).append("\n");
                sb.append("   - Age: ").append(patient.getAge()).append(" (").append(patient.getAgeRange()).append(")\n");
                sb.append("   - Sex: ").append(patient.getSex()).append("\n");
            }
        }
        JOptionPane.showMessageDialog(null, sb);
    }
}
