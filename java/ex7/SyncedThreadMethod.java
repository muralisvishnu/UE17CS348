import java.util.Random;
// class BalanceException extends Exception{

//     /**
//      *
//      */
//     BalanceException(String s){
//         super(s);
//     }
//     private static final long serialVersionUID = 1L;
// }
public class SyncedThreadMethod implements Runnable{
    public static int balance = 1000;
    int change;
    SyncedThreadMethod(int arg){
        change = arg;
    }
    public synchronized void run(){
        try{
            if (balance + change < 1000){
                throw new BalanceException("You have gone below Minimum Balance");
            }else{
                System.out.println("Thread " + Thread.currentThread().getName()+" Before "+balance);
                balance += change;
                System.out.println("Thread " + Thread.currentThread().getName()+" After "+balance);
            }
        }catch (BalanceException b){
            System.out.println("Thread " + Thread.currentThread().getName()+" Exception "+b);
        }
    }

    public static void main(String[] s) throws InterruptedException{
        Random rand = new Random();
        if (s.length < 1){
            System.out.println("Please enter the number of threads as a command line arg");
            return;
        }
        Thread[] threads = new Thread[Integer.parseInt(s[0])];
        for (int i = 0; i < threads.length ; i++){
            if (i%2 == 0){
                threads[i] = new Thread(new SyncedThreads(rand.nextInt(1000)),String.valueOf(i));
            }else{
                threads[i] = new Thread(new SyncedThreads(-1*rand.nextInt(10000)),String.valueOf(i));
            }
            threads[i].start();
        }
        for (int i = 0; i < threads.length; i++){
            threads[i].join();
        }
    }
}