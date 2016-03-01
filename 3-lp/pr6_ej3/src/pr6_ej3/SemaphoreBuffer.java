/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

package pr6_ej3;

import java.util.concurrent.Semaphore;

/**
 *
 * @author alumno
 */
public class SemaphoreBuffer<T> implements Buffer<T> {
    private final T[] values;
    private final Semaphore sem = new Semaphore(1);

    public SemaphoreBuffer(int size) {
        this.values = (T[]) new Object[size];
    }

    @Override
    public T get(int index) {
        sem.acquireUninterruptibly();
        T value = values[index];
        sem.release();
        return value;
    }

    @Override
    public void set(int index, T value) {
        sem.acquireUninterruptibly();
        values[index] = value;
        sem.release();
    }

    @Override
    public int size() {
        return values.length;
    }
}
