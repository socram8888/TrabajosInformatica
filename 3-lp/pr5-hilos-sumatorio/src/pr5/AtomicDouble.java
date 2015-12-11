/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package pr5;

import java.util.concurrent.atomic.AtomicLong;

/**
 *
 * @author Marcos
 */
public class AtomicDouble extends Number {
    private final AtomicLong atomic;

    public AtomicDouble() {
        this(0);
    }
    
    public AtomicDouble(double value) {
        atomic = new AtomicLong(Double.doubleToRawLongBits(value));
    }

    @Override
    public int intValue() {
        return (int) get();
    }

    @Override
    public long longValue() {
        return (long) get();
    }

    @Override
    public float floatValue() {
        return (float) get();
    }

    @Override
    public double doubleValue() {
        return get();
    }

    public double get() {
        return Double.longBitsToDouble(atomic.get());
    }
    
    public void set(double value) {
        atomic.set(Double.doubleToRawLongBits(value));
    }
    
    public double addAndGet(double delta) {
        long oldLong;
        long newLong;
        double newDouble;

        do {
            oldLong = atomic.get();
            newDouble = delta + Double.longBitsToDouble(oldLong);
            newLong = Double.doubleToRawLongBits(newDouble);
        } while (!atomic.compareAndSet(oldLong, newLong));

        return newDouble;
    }

    public double getAndAdd(double delta) {
        long oldLong;
        long newLong;
        double oldDouble;

        do {
            oldLong = atomic.get();
            oldDouble = Double.longBitsToDouble(oldLong);
            newLong = Double.doubleToRawLongBits(oldDouble + delta);
        } while (!atomic.compareAndSet(oldLong, newLong));

        return oldDouble;
    }
}
