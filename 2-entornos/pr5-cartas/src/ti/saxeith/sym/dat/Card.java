/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package ti.saxeith.sym.dat;

/**
 *
 * @author Marcos
 */
public class Card {
    private final int suit;
    private final int value;

    public Card(int suit, int value) {
        this.suit = suit;
        this.value = value;
    }

    public int getSuit() {
        return suit;
    }

    public int getValue() {
        return value;
    }

    public int getSevenAndHalfValue() {
        if (value < 7) {
            return (value + 1) * 10;
        }
        return 5;
    }
}
