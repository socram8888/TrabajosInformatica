/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package ti.saxeith.sym.gui;

import java.awt.Graphics;
import java.awt.GridLayout;
import java.awt.event.ActionListener;
import java.awt.image.BufferedImage;
import java.io.File;
import java.io.IOException;
import java.util.ArrayList;
import java.util.Iterator;
import java.util.List;
import javax.imageio.ImageIO;
import javax.swing.JPanel;
import ti.saxeith.sym.dat.Game;
import ti.saxeith.sym.dat.Player;

/**
 *
 * @author Marcos
 */
public class RugPanel extends JPanel {
    private final BufferedImage rug;
    private DeckTexture deckTexture;
    
    private final BankPanel bankPanel;
    private final List<PlayerPanel> playerPanels = new ArrayList<>();
    private final JPanel playersPanel;

    public RugPanel(Game game, DeckTexture deckTexture) {
        this.deckTexture = deckTexture;

        try {
            rug = ImageIO.read(new File("res/rug.png"));
        } catch (IOException e) {
            throw new RuntimeException("Unable to load built-in rug texture", e);
        }

        setLayout(new GridLayout(3, 1));

        Iterator<Player> playerIt = game.getPlayers().iterator();
        PlayerPanel panel = new PlayerPanel(playerIt.next(), deckTexture);
        add(panel);
        playerPanels.add(panel);

        bankPanel = new BankPanel(game, deckTexture);
        add(bankPanel);

        playersPanel = new JPanel();
        playersPanel.setOpaque(false);
        playersPanel.setLayout(new GridLayout(1, game.getPlayers().size() - 1));
        while (playerIt.hasNext()) {
            panel = new PlayerPanel(playerIt.next(), deckTexture);
            playerPanels.add(panel);
            playersPanel.add(panel);
        }
        add(playersPanel);
    }

    public void setDeckTexture(DeckTexture deckTexture) {
        this.deckTexture = deckTexture;
    }

    public DeckTexture getDeckTexture() {
        return deckTexture;
    }

    @Override
    public void paintComponent(Graphics g) {
        super.paintComponent(g);

        g.drawImage(rug, 0, 0, getWidth(), getHeight(), this);
    }
    
    public void refreshRug() {
        for (PlayerPanel panel : playerPanels) {
            panel.refreshPlayer();
        }
        bankPanel.refreshBank();
    }
    
    public void addActionListener(ActionListener a) {
        //for (PlayerPanel panel : playerPanels) {
        //    panel.addActionListener();
        //}
        bankPanel.addActionListener(a);
    }
}
