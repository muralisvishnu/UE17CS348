

import java.lang.Thread;
public class InterruptedRunnable implements Runnable {
    public void run(){
        try{
            Thread.sleep(400000);
        }catch (InterruptedException e){
            System.out.println("Thread "+Thread.currentThread().getId()+" Interrupted By Exception");
        }
        while (!Thread.interrupted()){
            //do nothing
        }
        System.out.println("Thread " +Thread.currentThread().getId()+" woken up again");
    }
    public static void main(String[] args) throws InterruptedException{
        Thread t1 = new Thread(new InterruptedRunnable(),"Custom 1");
        t1.start();
        Thread.sleep(1000);
        t1.interrupt();

        Thread.sleep(1000);
        t1.interrupt();

        Thread.sleep(1000);
        t1.interrupt();

    }
}