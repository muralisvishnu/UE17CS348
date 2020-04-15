import java.util.Queue;
import java.util.Random;
import java.util.LinkedList;

public class ConcurrentQ {
    private static final Queue<Integer> queue = new LinkedList<>();
    private static final Random randint = new Random();
    public static class Consumer implements Runnable{
        public void run(){
            boolean read = false;
            while (!read){
                synchronized (queue){
                    if (!queue.isEmpty()){
                        Integer integer = queue.poll();
                        System.out.println("Thread "+Thread.currentThread().getName() + " Consumed " + integer);
                        read = true;
                    }
                    queue.notify();
                }
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
        int num_threads = Integer.parseInt(s[0]);
        Thread[] threads = new Thread[num_threads*2];
        for (int i = 0; i < num_threads; i++){
            threads[i] = new Thread(new Producer(),String.valueOf(i));
        }
        for (int i = num_threads; i < num_threads*2; i++){
            threads[i] = new Thread(new Consumer(),String.valueOf(i));
        }
        for (int i = 0 ; i < num_threads*2; i++){
            threads[i].start();
        }
        for (int i = 0; i < num_threads*2;i++){
            threads[i].join();
        }
    }
}