/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package ti.saxeith.sym.dat;

import java.util.List;
import java.util.Random;

/**
 *
 * @author Marcos
 */
public final class Shuffler {
    private Shuffler() { }

    public static <E> void shuffle(List<E> list) {
        shuffle(list, new Random());
    }

    public static <E> void shuffle(List<E> list, Random random) {
        int size = list.size();

        for (int i = 0; i < size; i++) {
            int j = random.nextInt(size);

            if (i != j) {
                E c1 = list.get(i);
                E c2 = list.get(j);

                list.set(i, c2);
                list.set(j, c1);
            }
        }
    }
}
