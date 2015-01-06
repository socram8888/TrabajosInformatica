/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package ti.s4x8.eu.p1;

import ti.s4x8.util.StringTools;

/**
 *
 * @author Marcos Vives Del Sol
 */
public class DelegatingPerson extends AbstractPerson {
    private final AbstractPerson person;

    public DelegatingPerson(AbstractPerson person) {
        this.person = person;
    }

    @Override
    public String getName() {
        return person.getName();
    }

    @Override
    public Sex getSex() {
        return person.getSex();
    }

    @Override
    public int getAge() {
        return person.getAge();
    }

    /**
     * @return Original (parent) person
     */
    public AbstractPerson getParent() {
        return person;
    }

    @Override
    public String toString() {
        return StringTools.toString(this);
    }
}
