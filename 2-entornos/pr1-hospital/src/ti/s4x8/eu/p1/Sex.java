/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package ti.s4x8.eu.p1;

import ti.s4x8.util.EnumTools;

/**
 *
 * @author Marcos Vives Del Sol
 */
public enum Sex {
    UNSPECIFIED,
    MALE,
    FEMALE,
    ;

    @Override
    public String toString() {
        return EnumTools.readable(this);
    }
}
