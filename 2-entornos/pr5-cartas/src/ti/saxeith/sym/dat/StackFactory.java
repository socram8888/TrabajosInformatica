/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package ti.saxeith.sym.dat;

import java.util.Stack;

/**
 *
 * @author Marcos
 */
public final class StackFactory {
    public static final int CARD_VALUES = 10;
    public static final int CARD_SUITS = 4;

    private StackFactory() { }

    public static Stack<Card> create() {
        Stack<Card> list = new Stack<Card>();

        for (int suit = 0; suit < StackFactory.CARD_SUITS; suit++) {
            for (int value = 0; value < StackFactory.CARD_VALUES; value++) {
                list.add(new Card(suit, value));
            }
        }

        Shuffler.shuffle(list);

        return list;
    }
}
