/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package ti.saxeith.sym.dat;

import java.util.ArrayList;
import java.util.List;

/**
 *
 * @author Marcos
 */
public class Player {
    private final Game game;
    private final int id;
    private String name;
    private final boolean ai;
    private final List<Card> holdingCards = new ArrayList<Card>();

    private int sevenHalfSum = 0;
    private int wonCount;

    public Player(Game game, int id, String name, boolean ai) {
        this.game = game;
        this.id = id;
        this.name = name;
        this.ai = ai;
        
        requestCard();
    }

    public void requestCard() {
        Card card = game.getStack().pop();
        holdingCards.add(card);
        sevenHalfSum += card.getSevenAndHalfValue();
    }

    public List<Card> getHoldingCards() {
        return holdingCards;
    }

    public int getSevenHalfSum() {
        return sevenHalfSum;
    }

    public boolean hasLost() {
        return sevenHalfSum > 75;
    }

    public int getId() {
        return id;
    }
    
    public void setName(String name) {
        this.name = name;
    }
    
    public String getName() {
        return name;
    }

    public Game getGame() {
        return game;
    }
    
    public void playAgain() {
        sevenHalfSum = 0;
        holdingCards.clear();
        requestCard();
    }

    public int getWonCount() {
        return wonCount;
    }

    public void setWonCount(int wonCount) {
        this.wonCount = wonCount;
    }

    public boolean isAI() {
        return ai;
    }
}
