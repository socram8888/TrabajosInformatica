/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package ti.saxeith.sym.gui;

import java.util.List;
import javax.swing.BoxLayout;
import javax.swing.JPanel;
import ti.saxeith.swing.JImage;
import ti.saxeith.sym.dat.Card;

/**
 *
 * @author Marcos
 */
public class CardsPanel extends JPanel {
    private DeckTexture textures;
    private List<Card> cards;

    public CardsPanel(DeckTexture textures, List<Card> cards) {
        setOpaque(false);
        this.textures = textures;
        this.cards = cards;

        setLayout(new BoxLayout(this, BoxLayout.X_AXIS));
    }

    public void refreshCards() {
        removeAll();
        for (Card card : cards) {
            add(new JImage(textures.getTexture(card)));
        }
    }

    public DeckTexture getTextures() {
        return textures;
    }

    public void setTextures(DeckTexture textures) {
        this.textures = textures;
        refreshCards();
    }
}
