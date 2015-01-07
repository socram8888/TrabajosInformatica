/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package ti.saxeith.sym.gui;

import java.awt.Color;
import java.awt.Font;
import javax.swing.BorderFactory;
import javax.swing.BoxLayout;
import javax.swing.JLabel;
import javax.swing.JPanel;
import javax.swing.border.Border;
import ti.saxeith.sym.dat.Game;
import ti.saxeith.sym.dat.Player;

/**
 *
 * @author Marcos
 */
public class StatsPanel extends JPanel {
    private static final Font STATS_FONT = new Font(Font.SANS_SERIF, Font.BOLD, 20);
    private static final Border OUTER_BORDER = BorderFactory.createCompoundBorder(
        BorderFactory.createMatteBorder(2, 2, 2, 2, Color.BLACK),
        BorderFactory.createEmptyBorder(10, 10, 10, 10)
    );

    private final Game game;
    
    public StatsPanel(Game game) {
        this.game = game;

        setBorder(OUTER_BORDER);

        setLayout(new BoxLayout(this, BoxLayout.Y_AXIS));
    }

    private void addInfo(String info, boolean first) {
        JLabel j = new JLabel(info);
        j.setFont(STATS_FONT);
        add(j);
    }

    public void refreshStats() {
        removeAll();
        revalidate();
        
        addInfo("Partidas iniciadas: " + game.getPlayCount(), true);
        addInfo("Partidas finalizadas: " + game.getFinishedCount(), false);
        for (Player player : game.getPlayers()) {
            float wonCount = 0;
            if (game.getFinishedCount() > 0) {
                wonCount = 100.0f * player.getWonCount() / game.getFinishedCount();
            }
            addInfo(String.format(" - Ganadas por %s: %d (%.1f%%)", player.getName(), player.getWonCount(), wonCount), false);
        }
        
        System.out.println("REFRESH STATS " + game.getFinishedCount());
        repaint();
    }
}
