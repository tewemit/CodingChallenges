/*
 * 
Given M busy-time slots of N people, You need to print all the available time slots when all the N people can schedule a meeting for a duration of K minutes.
Event time will be of form HH MM ( where 0 <= HH <= 23 and 0 <= MM <= 59 ), K will be in the form minutes.
Input Format:
M K [ M number of busy time slots , K is the duration in minutes ]
Followed by M lines with 4 numbers on each line.
Each line will be of form StartHH StartMM EndHH EndMM  [ Example 9Am-11Am time slot will be given as 9 00 11 00 ]
An event time slot is of form [Start Time, End Time ) . Which means it inclusive at start time but doesn’t include the end time. 
So an event of form 10 00  11 00 => implies that the meeting start at 10:00 and ends at 11:00, so another meeting can start at 11:00.
Sample Input:
5 120
16 00 17 00
10 30 14 30
20 45 22 15
10 00 13 15
09 00 11 00
Sample Output:
00 00 09 00
17 00 20 45
Sample Input:
8 60
08 00 10 15
22 00 23 15
17 00 19 00
07 00 09 45
09 00 13 00
16 00 17 45
12 00 13 30
11 30 12 30
Sample Output:
00 00 07 00
13 30 16 00
19 00 22 00
Constraints :
1 <= M <= 100
Note: 24 00 has to be presented as 00 00
 * 
 */

import java.util.Iterator;
import java.util.LinkedList;
import java.util.Scanner;
 
 
public class MeetingSchedule {
 
 public static boolean arr[];
 public static int M;
 public static int K;
 public static time t[];
 public static LinkedList<time> ll;
  
 public static void main(String[] args) {
   
  arr = new boolean[1440]; // total minutes in a day of 24 hrs
  t = new time[1440];
  ll = new LinkedList<time>();
   
  for(int i=0;i<1440;i++)
  {
   arr[i] = true; 
  }
   
  Scanner in = new Scanner(System.in);
  M = in.nextInt();
  K = in.nextInt();
   
  for(int i=0;i<M;i++)
  {
   int st_h = in.nextInt();
   int st_m = in.nextInt();
   int end_h = in.nextInt();
   int end_m = in.nextInt();
    
   int st = (st_h*60) + st_m;
   int end = (end_h*60) + end_m;
    
   for(int j=st;j<end;j++)
   {
    arr[j] = false;
   }
    
  }
   
  int res_st = 0;
  int res_end = 0;
  int k=0;
  int flag = 0;
  int i=0;
  int flag2 = 0;
   
  free_block block[] = new free_block[1440];
   
  for(i=0;i<1440;i++)
  {
   if(arr[i] == true)
   {
    flag = 1;
    if(res_st == 0 && flag2 == 0)
    {
     res_st = i;
     flag2 = 1;
    }
   }
   else
   {
    if(flag == 1)
    {
     res_end = i;
     flag = 0;
     block[k] = new free_block();
     block[k].t = new time();
     int tmp = (res_st) % 60;
     int tmp2 = (res_end) % 60;
     block[k].t.start_m = tmp;
     block[k].t.start_h = (res_st - tmp) / 60;
     block[k].t.end_m = tmp2;
     block[k].t.end_h = (res_end - tmp2) / 60;
     block[k].duration = (res_end - res_st);
     res_st = res_end = 0;
     flag2 = 0;
     k++;
    }
   }
  }
   
  if(flag == 1)
  {
   res_end = i;
   block[k] = new free_block();
   block[k].t = new time();
   int tmp = (res_st) % 60;
   int tmp2 = (res_end) % 60;
   block[k].t.start_m = tmp;
   block[k].t.start_h = (res_st - tmp) / 60;
   block[k].t.end_m = tmp2;
   block[k].t.end_h = (res_end - tmp2) / 60;
   block[k].duration = (res_end - res_st);
   k++;
  }
   
   
  for(int l=0;l<k;l++)
  {
   if(block[l].duration >= K)
   {
    ll.add(block[l].t);
   }
  }
   
  Iterator<time> ii = ll.iterator();
   
  while(ii.hasNext())
  {
   time t = (time) ii.next();
   String t_start_h,t_start_m,t_end_h,t_end_m;
    
   if(t.start_h == 24)
   {
    t.start_h = 0;
   }
   if(t.end_h == 24)
   {
    t.end_h = 0;
   }
    
   if(t.start_h < 10)
   {
    t_start_h = "0"+Integer.toString(t.start_h);
   }
   else
   {
    t_start_h = Integer.toString(t.start_h);
   }
    
    
   if(t.start_m < 10)
   {
    t_start_m = "0"+Integer.toString(t.start_m);
   }
   else
   {
    t_start_m = Integer.toString(t.start_m);
   }
    
    
   if(t.end_h < 10)
   {
    t_end_h = "0"+Integer.toString(t.end_h);
   }
   else
   {
    t_end_h = Integer.toString(t.end_h);
   }
    
   if(t.end_m < 10)
   {
    t_end_m = "0"+Integer.toString(t.end_m);
   }
   else
   {
    t_end_m = Integer.toString(t.end_m);
   }
    
   System.out.println(t_start_h + " " + t_start_m + " " + t_end_h + " " + t_end_m);
  }
   
 }
 
}
 
class time
{
 public int start_h;
 public int start_m;
 public int end_h;
 public int end_m;
}
 
 
class free_block
{
 public time t;
 public int duration;
}
