/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package pr5;

/**
 *
 * @author Marcos Del Sol Vives <socram@protonmail.ch>
 */
public final class Divide {
    private Divide() { }

    public static int roundHalfUp(int dividend, int divisor) {
        int value = dividend / divisor;
        int mod = dividend % divisor;

        if (mod * 2 >= divisor) {
            value++;
        }

        return value;
    }

    public static long roundHalfUp(long dividend, long divisor) {
        long value = dividend / divisor;
        long mod = dividend % divisor;

        if (mod * 2 >= divisor) {
            value++;
        }

        return value;
    }

    public static int roundHalfDown(int dividend, int divisor) {
        int value = dividend / divisor;
        int mod = dividend % divisor;

        if (mod * 2 > divisor) {
            value++;
        }

        return value;
    }

    public static long roundHalfDown(long dividend, long divisor) {
        long value = dividend / divisor;
        long mod = dividend % divisor;

        if (mod * 2 > divisor) {
            value++;
        }

        return value;
    }
}
