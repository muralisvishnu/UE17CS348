
import java.util.Random;

import sun.jvm.hotspot.runtime.Threads;

public class JoinedThread implements Runnable {
    private Random rand = new Random();
    public void run(){
        for (int i = 0; i < 1000000; i++){
            rand.nextInt();
        }
        System.out.println("Thread "+Thread.currentThread().getId()+ " is finished");
    }
    public static void main(String[] args) throws InterruptedException{
        Thread[] threads = new Thread[10];
        for (int i = 0; i < threads.length; i ++){
            threads[i] =new Thread(new JoinedThread(),"Thread "+i);
            threads[i].start();
        }

        for (int i = 0; i < threads.length; i++){
            threads[i].join();
        }
        System.out.println("All threads have completed");
    }
}