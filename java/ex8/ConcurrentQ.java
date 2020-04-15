import java.util.Queue;
import java.util.Random;
import java.util.LinkedList;

public class ConcurrentQ {
    private static final Queue<Integer> queue = new LinkedList<>();
    private static final Random randint = new Random();
    public static class Consumer implements Runnable{
        public void run(){
            synchronized (queue){
                while (queue.isEmpty()){
                    try{
                        queue.wait();
                    }catch (InterruptedException e){
                        e.printStackTrace();
                    }
                }
                Integer integer = queue.poll();
                System.out.println("Thread "+Thread.currentThread().getName() + " Consumed " + integer);
                queue.notify();
            }
        }
    }
    public static class Producer implements Runnable{
        public void run(){
            synchronized (queue){
                    Integer i = randint.nextInt(1000);
                    queue.add(i);
                    System.out.println("Thread "+Thread.currentThread().getName()+" Produced "+i);
                    queue.notify();
            }
        }
    }
    public static void main (String[] s) throws InterruptedException{
        Thread t1 = new Thread(new Producer(),"P1");
        Thread t2 = new Thread(new Consumer(),"C1");
        t1.start();
        t2.start();
        t1.join();
        t2.join();
    }
}