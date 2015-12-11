/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

package pr5;

/**
 *
 * @author alumno
 */
public class Pr5 {

    private static final SummatoryFunction SQRT_CALCULATOR = new SummatoryFunction() {
        @Override
        public double calculate(long i) {
            return Math.sqrt(i);
        }
    };

    private static void waitWarmup(ThreadingSummatoryCalculator tsc) {
        System.out.print("Please wait, warming up VM... ");
        for (int i = 0; i < EXECS_PER_TEST; i++) {
            tsc.calculate(SQRT_CALCULATOR, 0, ENDVAL);
        }
        System.out.println("done");
    }

    private static final int EXECS_PER_TEST = 500;
    private static final int ENDVAL = 1000;

    private static long timedTest(ThreadingSummatoryCalculator tsc, int end) {
        long accumTime = 0;
        for (int run = 0; run < EXECS_PER_TEST; run++) {
            long now = System.nanoTime();
            tsc.calculate(SQRT_CALCULATOR, 1, end);
            accumTime += System.nanoTime() - now;
        }
        return accumTime / EXECS_PER_TEST;
    }
    
    private static void runThreadTest(ThreadingSummatoryCalculator tsc) {
        System.out.println("Executing thread test, with 1 <= threads <= 1024");

        for (int threads = 1024; threads >= 1; threads /= 2) {
            long time = timedTest(tsc, ENDVAL);
            System.out.println(threads + "threads: " + time + "ns");
        }
    }
    
    private static void runLengthTest(ThreadingSummatoryCalculator tsc) {
        System.out.println("Executing length test, with 1 <= i <= " + ENDVAL);

        for (int end = 1; end < 100000000; end *= 10) {
            long time = timedTest(tsc, end);
            System.out.println("1 <= i <= " + end + ": " + time + "ns total, " + ((double) time / end) + " scaled");
        }
    }

    /**
     * @param args the command line arguments
     */
    public static void main(String[] args) {
        ThreadingSummatoryCalculator tsc = new ThreadingSummatoryCalculator(4);
        waitWarmup(tsc);

        System.out.println(timedTest(tsc, ENDVAL));

        /*int cores = Runtime.getRuntime().availableProcessors();
        System.out.println("Further tests will be done using " + cores + " threads");
        tsc.resizeWorkers(cores);
        waitWarmup(tsc);

        runLengthTest(tsc);*/
    }
    
}
