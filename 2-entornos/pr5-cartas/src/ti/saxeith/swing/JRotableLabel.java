/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package ti.saxeith.swing;

import java.awt.Dimension;
import java.awt.Graphics;
import java.awt.Graphics2D;
import java.awt.geom.AffineTransform;
import javax.swing.JLabel;

/**
 *
 * @author Marcos
 */
public class JRotableLabel extends JLabel {

    public static final int ROTATE_0 = 0;
    public static final int ROTATE_90 = 1;
    public static final int ROTATE_180 = 2;
    public static final int ROTATE_270 = 3;

    private int rotation = ROTATE_90;
    private boolean wantRotatedSize;
    private AffineTransform transform = new AffineTransform();

    public JRotableLabel() {
        super();
    }

    public JRotableLabel(String text) {
        super(text);
    }

    public JRotableLabel(String text, int alignment) {
        super(text, alignment);
    }

    public void setRotation(int rotation) {
        this.rotation = rotation % 4;
    }

    public int getRotation() {
        return rotation;
    }

    private boolean isVertical() {
        return (rotation & 1) != 0;
    }

    @Override
    public Dimension getPreferredSize() {
        Dimension dim = super.getPreferredSize();
        if (isVertical()) {
            dim = new Dimension(dim.height, dim.width);
        }
        return dim;
    }

    @Override
    public void paintComponent(Graphics g) {
        if (rotation == ROTATE_0) {
            super.paintComponent(g);
            return;
        }

        boolean vertical = isVertical();
        Graphics2D g2 = (Graphics2D) g;
        
        transform.setToIdentity();
        transform.rotate(-rotation * Math.PI / 2, super.getWidth() / 2.0, super.getHeight() / 2.0);
        if (vertical) {
            //transform.translate(-super.getHeight() / 2.0 + super.getWidth() / 2.0, 0);
        }
        transform.translate(-super.getHeight() / 2 + super.getWidth() / 2, super.getHeight() / 2 - super.getWidth() / 2);
        g2.transform(transform);

        wantRotatedSize = vertical;
        super.paintComponent(g2);
        wantRotatedSize = false;
    }

    @Override
    public Dimension getSize() {
        Dimension dim = super.getSize();
        if (wantRotatedSize) {
            dim = new Dimension(dim.height, dim.width);
        }
        return dim;
    }
    
    
    @Override
    public int getWidth() {
        if (wantRotatedSize) {
            return super.getHeight();
        }
        return super.getWidth();
    }
    
    @Override
    public int getHeight() {
        if (wantRotatedSize) {
            return super.getWidth();
        }
        return super.getHeight();
    }
}
