public class SyncedThreads implements Runnable{
    public static int balance = 1000;
    int change;
    SyncedThreads (int arg){
        change = arg;
    }
    public void run(){
        boolean complete = false;
        while (!complete){ //cannot withdraw, try again later
            synchronized (SyncedThreads.class){
                if (balance + change >= 1000){
                    System.out.println("Thread " + Thread.currentThread().getName()+" Before "+balance);
                    balance += change;
                    complete = true;
                    System.out.println("Thread " + Thread.currentThread().getName()+" After "+balance);
                }
            }
        }
    }
    public static void main (String[] args) throws InterruptedException{
        Thread[] threads = new Thread[20];
        for (int i = 0; i < threads.length; i++){
            if (i%2 == 0){
                threads[i] = new Thread(new SyncedThreads(100),String.valueOf(i));
            }else{
                threads[i] = new Thread(new SyncedThreads(-100),String.valueOf(i));
            }
            
            threads[i].start();
        }
        for(int j = 0; j < threads.length; j++){
            threads[j].join();
        }
    }
}
