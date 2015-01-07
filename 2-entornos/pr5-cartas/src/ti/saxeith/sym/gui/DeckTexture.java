/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package ti.saxeith.sym.gui;

import java.awt.image.BufferedImage;
import java.io.File;
import java.io.IOException;
import javax.imageio.ImageIO;
import ti.saxeith.sym.dat.Card;
import ti.saxeith.sym.dat.StackFactory;

/**
 *
 * @author Marcos
 */
public class DeckTexture {
    public static final File DEFAULT_TEXTURE_FILE = new File("res/deck.png");
    private static final DeckTexture DEFAULT_TEXTURE = new DeckTexture();

    private BufferedImage[][] textures;
    private BufferedImage backTexture;
    private BufferedImage nextTexture;

    public DeckTexture() {
        try {
            loadTexture(DEFAULT_TEXTURE_FILE);
        } catch (IOException e) {
            throw new RuntimeException("Unable to load default texture. We're screwed.", e);
        }
    }

    public DeckTexture(File textureFile) throws IOException {
        loadTexture(textureFile);
    }

    private BufferedImage sliceImage(BufferedImage texture, int suit, int value) {
        int cardWidth = texture.getWidth() / (StackFactory.CARD_VALUES + 1);
        int cardHeight = texture.getHeight() / StackFactory.CARD_SUITS;
        return texture.getSubimage(texture.getWidth() * value / (StackFactory.CARD_VALUES + 1), texture.getHeight() * suit / StackFactory.CARD_SUITS, cardWidth, cardHeight);
    }

    public void loadTexture(File textureFile) throws IOException {
        BufferedImage texture = ImageIO.read(textureFile);

        textures = new BufferedImage[StackFactory.CARD_SUITS][];
        for (int suit = 0; suit < StackFactory.CARD_SUITS; suit++) {
            textures[suit] = new BufferedImage[StackFactory.CARD_VALUES];
            for (int value = 0; value < StackFactory.CARD_VALUES; value++) {
                textures[suit][value] = sliceImage(texture, suit, value);
            }
        }
        
        backTexture = sliceImage(texture, 0, StackFactory.CARD_VALUES);
        nextTexture = sliceImage(texture, 1, StackFactory.CARD_VALUES);
    }

    public BufferedImage getTexture(Card card) {
        return textures[card.getSuit()][card.getValue()];
    }
    
    public BufferedImage getBackTexture() {
        return backTexture;
    }
    
    public BufferedImage getNextTexture() {
        return nextTexture;
    }
    
    public void setDefault() {
        this.textures = DEFAULT_TEXTURE.textures;
        this.backTexture = DEFAULT_TEXTURE.backTexture;
        this.nextTexture = DEFAULT_TEXTURE.nextTexture;
    }
}
