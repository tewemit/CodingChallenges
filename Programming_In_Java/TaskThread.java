import java.util.Date;
import java.util.concurrent.Executors;
import java.util.concurrent.ThreadPoolExecutor;
import java.util.concurrent.TimeUnit;


public class Task implements Runnable {
   private Date date;
   private String name;

   public Task(String name) {
      date = new Date();
      this.name = name;
   }

   @Override
   public void run() {
   System.out.printf("Thread: %s Task: %s created on %s\n", Thread
      .currentThread().getName(), name, date);
   System.out.printf("Thread: %s Task: %s started on %s\n", Thread
      .currentThread().getName(), name, new Date());
   try {
      Long timeout = ((long) Math.random() * 10);
      System.out.println(Thread.currentThread().getName()
         + " with Task name: " + name
         + " is asleep for " + timeout+ " msec.");
         TimeUnit.SECONDS.sleep(timeout);
   } catch (InterruptedException intex) {
      intex.printStackTrace();
   }
   System.out.printf("Thread: %s Task: %s finished on %s\n", Thread
      .currentThread().getName(), name, new Date());
   }
}


class TaskServer 
{
   private ThreadPoolExecutor threadPoolExecutor;

   public TaskServer() {
      threadPoolExecutor = (ThreadPoolExecutor) Executors
          .newCachedThreadPool();
   }
   public void execute(Task task)
   {
      threadPoolExecutor.execute(task);
      System.out.println("Pool size of the Server: "
      +threadPoolExecutor.getPoolSize());
      System.out.println("Active Task count: "
      +threadPoolExecutor.getActiveCount());
      System.out.println("Task Completed count: "
      +threadPoolExecutor.getCompletedTaskCount());
      
   }

   public void close(){
      threadPoolExecutor.shutdown();
   }
}

class AppMain
{

   public static void main(String[] args) {
      TaskServer server = new TaskServer();
      for (int i = 0; i < 50; i++) {
         Task task = new Task("Task " + i);
         server.execute(task);
      }
      server.close();
   }
}
