/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package ti.saxeith.sym.gui;

import java.awt.BorderLayout;
import java.awt.Color;
import java.awt.Font;
import java.awt.GridLayout;
import java.util.Set;
import javax.swing.BorderFactory;
import javax.swing.JLabel;
import javax.swing.JPanel;
import javax.swing.border.Border;
import ti.saxeith.swing.JRotableLabel;
import ti.saxeith.sym.dat.Player;

/**
 *
 * @author Marcos
 */
public class PlayerPanel extends JPanel {
    private CardsPanel cardsPanel;
    private JRotableLabel namePanel;
    private JRotableLabel sumPanel;
    private Player player;

    public PlayerPanel(Player player, DeckTexture texture) {
        this.player = player;

        setOpaque(false);
        setLayout(new BorderLayout());

        cardsPanel = new CardsPanel(texture, player.getHoldingCards());
        cardsPanel.setBorder(BorderFactory.createEmptyBorder(10, 10, 10, 10));
        add(cardsPanel, BorderLayout.CENTER);

        JPanel jp = new JPanel(new GridLayout(1, 2));

        sumPanel = new JRotableLabel(Double.toString(player.getSevenHalfSum() / 10.0), JLabel.CENTER);
        sumPanel.setForeground(Color.WHITE);
        sumPanel.setBackground(Color.BLACK);
        sumPanel.setOpaque(true);
        sumPanel.setFont(new Font(Font.SANS_SERIF, Font.BOLD, 32));
        sumPanel.setRotation(JRotableLabel.ROTATE_270);
        jp.add(sumPanel);

        namePanel = new JRotableLabel(player.getName(), JLabel.CENTER);
        namePanel.setForeground(Color.WHITE);
        namePanel.setBackground(Color.BLACK);
        namePanel.setOpaque(true);
        namePanel.setFont(new Font(Font.SANS_SERIF, Font.BOLD, 32));
        namePanel.setRotation(JRotableLabel.ROTATE_270);
        jp.add(namePanel);

        add(jp, BorderLayout.EAST);
    }

    public void refreshPlayer() {
        cardsPanel.refreshCards();
        sumPanel.setText(Double.toString(player.getSevenHalfSum() / 10.0));
        if (player.hasLost()) {
            sumPanel.setBackground(Color.RED);
            namePanel.setBackground(Color.RED);
        } else if (player.getGame().getPlayingPlayer() == player) {
            sumPanel.setBackground(Color.BLUE);
            namePanel.setBackground(Color.BLUE);
        } else {
            Set<Player> winners = player.getGame().getWinners();
            if (winners != null) {
                if (winners.contains(player)) {
                    sumPanel.setBackground(Color.GREEN.darker());
                    namePanel.setBackground(Color.GREEN.darker());
                } else {
                    sumPanel.setBackground(Color.RED);
                    namePanel.setBackground(Color.RED);
                }
            } else {
                sumPanel.setBackground(Color.BLACK);
                namePanel.setBackground(Color.BLACK);
            }
        }
    }
}
