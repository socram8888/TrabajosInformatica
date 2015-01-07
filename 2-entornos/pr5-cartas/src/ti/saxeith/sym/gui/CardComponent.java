/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package ti.saxeith.sym.gui;

import javax.swing.ImageIcon;
import javax.swing.JPanel;
import javax.swing.JLabel;
import ti.saxeith.sym.dat.Card;

/**
 *
 * @author Marcos
 */
public class CardComponent extends JPanel {
    private final JLabel label;

    public CardComponent(DeckTexture texture, Card card) {
        label = new JLabel(new ImageIcon(texture.getTexture(card)));
        add(label);
    }
}
