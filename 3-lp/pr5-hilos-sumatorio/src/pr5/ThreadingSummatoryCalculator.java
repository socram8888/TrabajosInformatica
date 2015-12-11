/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

package pr5;

import java.util.Arrays;
import java.util.concurrent.CountDownLatch;

/**
 *
 * @author alumno
 */
public class ThreadingSummatoryCalculator extends SummatoryCalculator {
    private SummatoryThread[] workers;

    private SummatoryFunction function;
    private long start;
    private long end;
    private final AtomicDouble value = new AtomicDouble();

    private boolean barrier;
    private final Object sleepLock = new Object();
    private CountDownLatch finishedCountdown;

    public ThreadingSummatoryCalculator(int threads) {
        this.workers = new SummatoryThread[threads];
        for (int i = 0; i < threads; i++) {
            this.workers[i] = new SummatoryThread(this, i, false);
            this.workers[i].start();
        }
    }

    @Override
    public double calculate(SummatoryFunction function, long start, long end) {
        this.function = function;
        this.start = start;
        this.end = end;

        value.set(0);
        finishedCountdown = new CountDownLatch(workers.length);

        barrier = !barrier;
        synchronized (sleepLock) {
            sleepLock.notifyAll();
        }

        try {
            finishedCountdown.await();
        } catch (InterruptedException ex) {
            throw new RuntimeException("Error waiting for thread finish synchronization", ex);
        }

        return value.get();
    }

    public void resizeWorkers(int newCount) {
        if (newCount < 1) {
            throw new IllegalArgumentException("Worker count must one or larger");
        }

        int oldCount = workers.length;
        if (newCount > oldCount) {
            workers = Arrays.copyOf(workers, newCount);
            for (int i = oldCount; i < newCount; i++) {
                this.workers[i] = new SummatoryThread(this, i, barrier);
                this.workers[i].start();
            }
        } else if (newCount < oldCount) {
            for (int i = newCount; i < oldCount; i++) {
                this.workers[i].interrupt();
            }
            workers = Arrays.copyOf(workers, newCount);
        }
    }

    private static class SummatoryThread extends Thread {
        private final ThreadingSummatoryCalculator calculator;
        private final int id;
        private boolean barrier;
        private boolean dead;

        public SummatoryThread(ThreadingSummatoryCalculator calculator, int id, boolean barrier) {
            this.calculator = calculator;
            this.id = id;
            this.barrier = barrier;
            setDaemon(true);
        }

        @Override
        public void run() {
            while (true) {
                if (calculator.barrier == barrier) {
                    synchronized (calculator.sleepLock) {
                        while (calculator.barrier == barrier) {
                            try {
                                calculator.sleepLock.wait();
                            } catch (InterruptedException e) {
                                return;
                            }
                        }
                    }
                }

                SummatoryThread[] workers = calculator.workers;
                if (id >= workers.length || workers[id] != this) {
                    return;
                }

                SummatoryFunction function = calculator.function;
                long len = calculator.end - calculator.start + 1;
                long start = Divide.roundHalfDown(id * len, workers.length) + calculator.start;
                long end = Divide.roundHalfDown((id + 1) * len, workers.length) + calculator.start;
                if (end > calculator.end) {
                    end = calculator.end + 1;
                }

                //System.out.println("Worker " + id + " computing " + start + " <= i < " + end);

                double value = 0;
                for (long i = start; i < end; i++) {
                    value += function.calculate(i);
                }

                calculator.value.addAndGet(value);
                calculator.finishedCountdown.countDown();

                barrier = !barrier;
            }
        }
    }
}
