/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package ti.s4x8.util;

import java.lang.reflect.Field;

/**
 *
 * @author Marcos Vives Del Sol
 */
public final class StringTools {
    /**
     * Sanitizes input by removing consecutive spaces and converting it to upper case
     * @param txt Original test
     * @return sanitized text
     */
    public static final String sanitize(String txt) {
        return txt.replaceAll("/[ \t]+/", " ").toUpperCase();
    }

    /**
     * Generates a debugging toString with private fields
     * @param object Object to convert to string
     * @return String representing internal object fields
     */
    public static final String toString(Object object) {
        if (object == null) {
            return "null";
        }

        try {
            Class clazz = object.getClass();
            StringBuilder sb = new StringBuilder();
            sb.append(clazz.getSimpleName());
            sb.append(" { ");

            Field[] fields = clazz.getDeclaredFields();
            for (int i = 0; i < fields.length; i++) {
                Field field = fields[i];

                if (i != 0) {
                    sb.append(", ");
                }
                sb.append(field.getName());
                sb.append(": ");

                field.setAccessible(true);
                sb.append(field.get(object).toString());
            }
            sb.append(" }");

            return sb.toString();
        } catch (Exception e) { }

        // From official Java runtime code
        return object.getClass().getName() + "@" + Integer.toHexString(object.hashCode());
    }
}
