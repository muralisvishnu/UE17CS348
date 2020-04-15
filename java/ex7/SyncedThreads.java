import java.util.Random;
class BalanceException extends Exception{

    /**
     *
     */
    BalanceException(String s){
        super(s);
    }
    private static final long serialVersionUID = 1L;
}

public class SyncedThreads implements Runnable{
    public static int balance = 1000;
    int change;
    SyncedThreads (int arg){
        change = arg;
    }
    public void run(){
       synchronized (SyncedThreads.class){
           try{
            if (balance + change < 1000){
                throw new BalanceException("You have gone below Minimum Balance");
            }else{
                //System.out.println("Thread " + Thread.currentThread().getName()+" Before "+balance);
                balance += change;
                //System.out.println("Thread " + Thread.currentThread().getName()+" After "+balance);
            }
            }catch (BalanceException b){
                //System.out.println("Thread " + Thread.currentThread().getName()+" Exception "+b);
            }   
        }
    }
    public static void main (String[] args) throws InterruptedException{
        if (args.length < 1){
            System.out.println("Please enter the number of threads as a command line arg");
            return;
        }
        Thread[] threads = new Thread[Integer.parseInt(args[0])];
        Random rand = new Random();
        for (int i = 0; i < threads.length; i++){
            if (i%2 == 0){
                threads[i] = new Thread(new SyncedThreads(rand.nextInt(1000)),String.valueOf(i));
            }else{
                threads[i] = new Thread(new SyncedThreads(-1*rand.nextInt(100000)),String.valueOf(i));
            }
            
            threads[i].start();
        }
        for(int j = 0; j < threads.length; j++){
            threads[j].join();
        }
    }
}
