/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

package pr6_ej3;

import java.util.logging.Level;
import java.util.logging.Logger;

/**
 *
 * @author alumno
 */
public class Pr6_ej3 {
    public static void main(String[] args) {
        Buffer<Object> buffer;

        //buffer = new SynchronizedBuffer<Object>(10000);
        buffer = new SemaphoreBuffer<Object>(10000);
        
        Thread[] threads = new Thread[10000 * 2];
        for (int i = 0; i < 10000; i++) {
            threads[i * 2 + 0] = new ReadThread(buffer, i);
            threads[i * 2 + 1] = new WriteThread(buffer, i);
        }
        
        Randomize.randomize(threads);

        for (Thread thread : threads) {
            thread.start();
        }

        for (Thread thread : threads) {
            try {
                thread.join();
            }catch (InterruptedException ex) {
                Logger.getLogger(Pr6_ej3.class.getName()).log(Level.SEVERE, null, ex);
            }
        }
    }

    public static class ReadThread extends Thread {
        private final Buffer<Object> buffer;
        private final int pos;

        public ReadThread(Buffer<Object> buffer, int pos) {
            this.buffer = buffer;
            this.pos = pos;
        }
        
        @Override
        public void run() {
            buffer.get(pos);
        }
    }
    
    public static class WriteThread extends Thread {
        private final Buffer<Object> buffer;
        private final int pos;

        public WriteThread(Buffer<Object> buffer, int pos) {
            this.buffer = buffer;
            this.pos = pos;
        }
        
        @Override
        public void run() {
            buffer.set(pos, new Object());
        }
    }
}
