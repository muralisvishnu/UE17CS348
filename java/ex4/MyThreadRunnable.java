

import java.lang.Thread;
public class MyThreadRunnable implements Runnable{
    public void run(){
        while (true){
            System.out.println("Executing Thread "+Thread.currentThread().getName());
            try{
                Thread.sleep(1000);
            }catch (InterruptedException e){
                e.printStackTrace();
            }
        }
    }
    public static void main(String[] args) throws InterruptedException{
        Thread t1 = new Thread(new MyThreadRunnable(),"custom 1");
        t1.start();
        t1.join();
    }
}