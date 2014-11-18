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
public class Person extends AbstractPerson {
    private final String name;
    private Sex sex;
    private int age;

    public Person(String name, Sex sex, int age) {
        this.name = StringTools.sanitize(name);
        this.sex = sex;
        this.age = age;
    }

    @Override
    public String getName() {
        return name;
    }

    @Override
    public Sex getSex() {
        return sex;
    }

    @Override
    public int getAge() {
        return age;
    }

    @Override
    public String toString() {
        return StringTools.toString(this);
    }
}
