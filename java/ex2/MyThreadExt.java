
import java.lang.Thread;
public class MyThreadExt extends Thread {
    public MyThreadExt(String name){
        super(name);
    }
    @Override
    public void run(){
        System.out.println("Executing thread "+Thread.currentThread().getName());

    }
    public static void main (String[] args) throws InterruptedException {
        MyThreadExt mythread = new MyThreadExt("Custom Thread 1");
        mythread.start();
        MyThreadExt anotherthread = new MyThreadExt("Custom Thread 2");
        anotherthread.start();
        mythread.join();
        anotherthread.join();
    }
}