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
public enum AgeRange {
    CHILD(0, 13),
    TEEN(13, 18),
    ADULT(18, 65),
    ELDER(65),
    ;

    private int min;
    private int max;
    
    private AgeRange(int min) {
        this(min, -1);
    }
    
    private AgeRange(int min, int max) {
        this.min = min;
        this.max = max;
    }

    /**
     * @return Lower bound of this age range (inclusive)
     */
    public int getMinimum() {
        return min;
    }

    /**
     * @return Upper bound of this age range (exclusive)
     */
    public int getMaximum() {
        return max;
    }

    /**
     * @param age Age
     * @return age range for given age
     */
    public static AgeRange fromAge(int age) {
        if (age < 0) {
            throw new IllegalArgumentException("Age must be positive");
        }
 
        for (AgeRange range : values()) {
            if (age >= range.min && (range.max < 0 || age < range.max)) {
                return range;
            }
        }

        return null;
    }

    @Override
    public String toString() {
        return EnumTools.readable(this);
    }
}
