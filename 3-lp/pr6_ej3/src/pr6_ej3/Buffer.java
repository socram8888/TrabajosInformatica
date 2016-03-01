/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

package pr6_ej3;

/**
 *
 * @author alumno
 */
public interface Buffer<T> {
    public T get(int index);
    public void set(int index, T value);
    public int size();
}
