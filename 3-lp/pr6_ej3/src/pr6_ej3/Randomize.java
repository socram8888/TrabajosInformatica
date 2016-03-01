/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

package pr6_ej3;

import java.util.Random;

/**
 *
 * @author alumno
 */
public final class Randomize {
    private Randomize() { }
    
    public static int[] randomize(int[] array) {
        return randomize(array, new Random());
    }

    public static int[] randomize(int[] array, Random random) {
        // Algoritmo de Durstenfeld
        for (int i = array.length - 1; i >= 1; i--) {
            int j = random.nextInt(i + 1);
            int x = array[i];
            array[i] = array[j];
            array[j] = x;
        }
        return array;
    }

    public static <V> V[] randomize(V[] array) {
        return randomize(array, new Random());
    }

    public static <V> V[] randomize(V[] array, Random random) {
        for (int i = array.length - 1; i >= 1; i--) {
            int j = random.nextInt(i + 1);
            V x = array[i];
            array[i] = array[j];
            array[j] = x;
        }
        return array;
    }
}
