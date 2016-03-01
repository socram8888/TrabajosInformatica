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
public class SynchronizedBuffer<T> implements Buffer<T> {
    private final T[] values;

    public SynchronizedBuffer(int size) {
        this.values = (T[]) new Object[size];
    }
    
    @Override
    public synchronized T get(int index) {
        return values[index];
    }

    @Override
    public synchronized void set(int index, T value) {
        values[index] = value;
    }

    @Override
    public int size() {
        return values.length;
    }
}
