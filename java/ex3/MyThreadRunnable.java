
import java.lang.Thread;
public class MyThreadRunnable implements Runnable {
    public void run(){
        System.out.println("Executing Thread "+Thread.currentThread().getName());
    }
    public static void main(String[] args) throws InterruptedException{
        Thread myThread = new Thread(new MyThreadRunnable(),"Custom Runnable");
        myThread.start();
        Thread anotherthread = new Thread(new MyThreadRunnable(),"Another custom runnable");
        myThread.join();
        anotherthread.start();
        anotherthread.join();
    }
}