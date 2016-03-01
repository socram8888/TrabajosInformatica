/**
 * Copyright (C) 2009-2012 Typesafe Inc. <http://www.typesafe.com>
 */

import akka.actor.ActorRef;
import akka.actor.ActorSystem;
import akka.actor.Props;
import akka.actor.UntypedActor;
import akka.actor.UntypedActorFactory;
import akka.routing.RoundRobinRouter;

/*
class ManejadorTiempos{
    static volatile long tiempo;
    static int veces;
    static Object o=new Object();
    static Semaphore s=new Semaphore(1);
    public static void addTiempo(long x){
        synchronized (o)
        {
            tiempo+=x;
            veces++;
            o.notify();
        }
    }
    public static long getTiempo() {
        synchronized (o)
        {
          try {
            while (veces<500)
                o.wait();
            
          } catch (InterruptedException ex) {}
            
        }
        return tiempo;
    }
    
}
*/
public class Pi {
	public static void main(String[] args) throws InterruptedException {
		Pi pi = new Pi();
                for (int i = 0; i < 500; i++) {
                    PiApproximation result = new PiApproximation();
                    pi.calculate(4, 20, 100, result);
                    result.waitSet();
                }

                for (int i = 1; i <= 1024; i *= 2) {
                    System.out.print("=>>>> " + i + ": ");
                    long timeAccu = 0;
                    for (int j = 0; j < 500; j++) {
                       //ManejadorTiempos.s.acquireUninterruptibly();
                       PiApproximation result = new PiApproximation();
                       pi.calculate(i, 10000000, i, result);
                       timeAccu += result.getDuration();
                    }
                    System.out.println(timeAccu + " (avg " + (timeAccu / 500) + ")");
                   
                    
                    //System.out.println(ManejadorTiempos.getTiempo());
                    
                }
	}

	static class Calculate {
	}

	static class Work {
		private final int start;
		private final int nrOfElements;

		public Work(int start, int nrOfElements) {
			this.start = start;
			this.nrOfElements = nrOfElements;
		}

		public int getStart() {
			return start;
		}

		public int getNrOfElements() {
			return nrOfElements;
		}
	}

	static class Result {
		private final double value;

		public Result(double value) {
			this.value = value;
		}

		public double getValue() {
			return value;
		}
	}

	static class PiApproximation {
		private double pi;
		private long duration;
                private boolean set;

                public void waitSet() {
                    if (!set) {
                        synchronized (this) {
                            while (!set) {
                                try {
                                    wait();
                                } catch (InterruptedException ex) {
                                    throw new RuntimeException(ex);
                                }
                            }
                        }
                    }
                }

		public double getPi() {
                    waitSet();
                    return pi;
		}

		public long getDuration() {
                    waitSet();
                    return duration;
		}
                
                public void set(double pi, long duration) {
                    if (set) {
                        throw new IllegalStateException("Already set");
                    }

                    synchronized (this) {
                        if (set) {
                            throw new IllegalStateException("Already set");
                        }

                        this.pi = pi;
                        this.duration = duration;
                        set = true;

                        notifyAll();
                    }
                }
	}

	public static class Worker extends UntypedActor {
		private double calculateSum(int start, int nrOfElements) {
			double acc = 0.0;
			for (int i = start; i < nrOfElements; i++) {
				acc += Math.sqrt(i);
			}
			return acc;
		}

		public void onReceive(Object message) {
			if (message instanceof Work) {
				Work work = (Work) message;
				double result = calculateSum(work.getStart(), work
						.getNrOfElements());
				getSender().tell(new Result(result), getSelf());
			} else {
				unhandled(message);
			}
		}
	}

	public static class Master extends UntypedActor {
		private final int nrOfMessages;
		private final int nrOfElements;
		private double pi;
		private int nrOfResults;
		private final PiApproximation result;
		private final ActorRef workerRouter;
		private final long start = System.nanoTime();

		public Master(final int nrOfWorkers, int nrOfMessages, int nrOfElements, PiApproximation result) {
			this.nrOfMessages = nrOfMessages;
			this.nrOfElements = nrOfElements;
			this.result = result;
			workerRouter = this.getContext().
			               actorOf(
			                  new Props(Worker.class).withRouter(new RoundRobinRouter(nrOfWorkers)),
			                  "workerRouter"
			                );
		}

		public void onReceive(Object message) {
			if (message instanceof Calculate) {
                                int end = 1;
				for (int id = 0; id < nrOfMessages; id++) {
                                        int start = end;
                                        end = (id + 1) * nrOfElements / nrOfMessages + 1;
                                        if (end > nrOfElements) {
                                            end = nrOfElements + 1;
                                        }

					workerRouter.tell(new Work(start, end), getSelf());
				}
			} else if (message instanceof Result) {
				Result result = (Result) message;
				pi += result.getValue();
				nrOfResults += 1;
				if (nrOfResults == nrOfMessages) {
					// Send the result to the listener
                                        this.result.set(pi, System.nanoTime() - start);
					// Stops this actor and all its supervised children
					getContext().system().shutdown();
				}
			} else {
				unhandled(message);
			}
		}
	}

	public void calculate(final int nrOfWorkers, final int nrOfElements,
			final int nrOfMessages, final PiApproximation pi) {
		// Create an Akka system
		ActorSystem system = ActorSystem.create("PiSystem");
		// create the master
		ActorRef master = system.actorOf(new Props(new UntypedActorFactory() {
			public UntypedActor create() {
				return new Master(nrOfWorkers, nrOfMessages, nrOfElements,
						pi);
			}
		}), "master");
		// start the calculation
		master.tell(new Calculate());
                
	}
}