/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package es.uv.eu.photoeditor;

import java.awt.Color;

/**
 *
 * @author Marcos
 */
public class ColorTools {

    // https://stackoverflow.com/a/2241471
    public static int calculatePerceivedBrightness(Color color) {
        int r = color.getRed();
        int g = color.getGreen();
        int b = color.getBlue();

        return (int) Math.sqrt(r * r * 0.299 + g * g * 0.587 + b * b * 0.114);
    }

    public static Color getReadableColor(Color color) {
        if (calculatePerceivedBrightness(color) > 130) {
            return Color.BLACK;
        }

        return Color.WHITE;
    }
}
