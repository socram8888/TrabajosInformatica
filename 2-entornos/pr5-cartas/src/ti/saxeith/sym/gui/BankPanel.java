/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package ti.saxeith.sym.gui;

import java.awt.GridLayout;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.MouseAdapter;
import java.awt.event.MouseEvent;
import java.util.LinkedList;
import java.util.List;
import javax.swing.BorderFactory;
import javax.swing.JPanel;
import ti.saxeith.swing.JImage;
import ti.saxeith.sym.dat.Game;

/**
 *
 * @author Marcos
 */
public class BankPanel extends JPanel {
    private final StatsPanel statsPanel;
    private final DeckTexture texture;
    private final JImage stack;
    private final JImage next;
    private final List<ActionListener> listeners = new LinkedList<>();
    
    public BankPanel(Game game, DeckTexture texture) {
        this.texture = texture;
        
        setOpaque(false);
        setLayout(new GridLayout(1, 2));
        setBorder(BorderFactory.createEmptyBorder(10, 10, 10, 10));
        
        statsPanel = new StatsPanel(game);
        add(statsPanel);
        
        JPanel jp = new JPanel();
        jp.setOpaque(false);
        jp.setLayout(new GridLayout(1, 2));
        
        stack = new JImage(texture.getBackTexture());
        stack.addMouseListener(new MouseAdapter() {
            @Override
            public void mousePressed(MouseEvent me) {
                if (me.getButton() == MouseEvent.BUTTON1) {
                    ActionEvent ae = new ActionEvent(stack, 0, "stack.click");
                    for (ActionListener l : listeners) {
                        l.actionPerformed(ae);
                    }
                }
            }
        });
        jp.add(stack);
        
        next = new JImage(texture.getNextTexture());
        next.addMouseListener(new MouseAdapter() {
            @Override
            public void mousePressed(MouseEvent me) {
                if (me.getButton() == MouseEvent.BUTTON1) {
                    ActionEvent ae = new ActionEvent(stack, 0, "stack.skip");
                    for (ActionListener l : listeners) {
                        l.actionPerformed(ae);
                    }
                }
            }
        });
        jp.add(next);
        
        add(jp);
    }
    
    public void refreshBank() {
        stack.setImage(texture.getBackTexture());
        next.setImage(texture.getNextTexture());
        statsPanel.refreshStats();
    }
    
    public void addActionListener(ActionListener a) {
        listeners.add(a);
    }
}
