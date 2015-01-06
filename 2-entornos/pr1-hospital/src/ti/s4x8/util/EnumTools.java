/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package ti.s4x8.util;

/**
 *
 * @author Marcos Vives Del Sol
 */
public class EnumTools {

    /**
     * Build a more readable version of the Enum member name
     * @param element Enum member
     * @return Readable name
     */
    public static final String readable(Enum element) {
        StringBuilder builder = new StringBuilder();
        String parts[] = element.name().split("_");

        for (int i = 0; i < parts.length; i++) {
            String part = parts[i];
            if (i == 0) {
                builder.append(part.substring(0, 1).toUpperCase());
                builder.append(part.substring(1).toLowerCase());
            } else {
                builder.append(part.toLowerCase());
            }
        }

        return builder.toString();
    }
}
