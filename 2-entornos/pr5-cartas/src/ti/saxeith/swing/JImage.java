/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package ti.saxeith.swing;

import java.awt.Dimension;
import java.awt.Graphics;
import java.awt.Image;
import javax.swing.JComponent;

/**
 *
 * @author Marcos
 */
public class JImage extends JComponent {
    public static final int FIT = 0;
    public static final int FILL = 1;

    private Image image;
    private Dimension imageSize;
    private int mode = FIT;

    public JImage() {
        setImage(null);
    }

    public JImage(Image image) {
        setImage(image);
    }
    
    public JImage(Image image, int mode) {
        setImage(image);
        setMode(mode);
    }

    public void setImage(Image image) {
        this.image = image;

        if (image != null) {
            imageSize = new Dimension(image.getWidth(this), image.getHeight(this));
        } else {
            imageSize = new Dimension(0, 0);
        }

        invalidate();
    }

    @Override
    public Dimension getPreferredSize() {
        if (isPreferredSizeSet()) {
            return super.getPreferredSize();
        }

        return imageSize;
    }

    @Override
    public void paintComponent(Graphics g) {
        super.paintComponent(g);
        
        if (image != null) {
            double imageRatio = (double) imageSize.width / imageSize.height;

            int cntWidth = getWidth();
            int cntHeight = getHeight();

            double cntRatio = (double) cntWidth / cntHeight;

            boolean isContainerWider = imageRatio < cntRatio; 
            if (mode == FILL) {
                isContainerWider = !isContainerWider;
            }

            int scaledWidth = cntWidth;
            int scaledHeight = cntHeight;
            if (isContainerWider) {
                scaledWidth = (int) (cntHeight * imageRatio);
            } else {
                scaledHeight = (int) (cntWidth / imageRatio);
            }

            g.drawImage(image, cntWidth / 2 - scaledWidth / 2, cntHeight / 2 - scaledHeight / 2, scaledWidth, scaledHeight, this);
        }
    }

    public int getMode() {
        return mode;
    }

    public void setMode(int mode) {
        this.mode = mode;
    }
}
