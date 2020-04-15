
import java.lang.Thread;

public class thread_info_1{
    public static void main (String[] args){
        long id = Thread.currentThread().getId();
        String name = Thread.currentThread().getName();
        int priority = Thread.currentThread().getPriority();
        Thread.State state = Thread.currentThread().getState();
        String threadgroupname = Thread.currentThread().getThreadGroup().getName();
        System.out.println("id="+ id);
        System.out.println("name="+ name);
        System.out.println("priority="+ priority);
        System.out.println("state="+ state);
        System.out.println("threadgroupname="+threadgroupname);
    }
}