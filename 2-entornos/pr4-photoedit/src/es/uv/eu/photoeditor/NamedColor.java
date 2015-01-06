/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package es.uv.eu.photoeditor;

import java.awt.Color;

import lombok.Data;

/**
 *
 * @author Marcos
 */
@Data
public class NamedColor {
    private final Color color;
    private final String name;

    public NamedColor(Color color, String name) {
        this.color = color;
        this.name = name;
    }
}
