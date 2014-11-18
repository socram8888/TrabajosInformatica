/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package ti.s4x8.eu.p1;

/**
 *
 * @author Marcos Vives Del Sol
 */
public abstract class AbstractPerson {
    /**
     * @return Person name
     */
    public abstract String getName();

    /**
     * @return Person sex
     */
    public abstract Sex getSex();

    /**
     * @return Person age. May be less than 0 if not known or not specified.
     */
    public abstract int getAge();

    /**
     * Utility method for getting age range
     * @return age range
     */
    public AgeRange getAgeRange() {
        return AgeRange.fromAge(getAge());
    }
}
