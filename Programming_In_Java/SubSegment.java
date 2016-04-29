

/***************************************************************/
/* author: Tewelle                                                                                                          */
/***************************************************************/
import java.util.*;

class record{
    String s;
    int v;
}

class recordComparator implements Comparator <record> {
    public int compare(record e1, record e2) {

        int result = 0;
        if(e1.v > e2.v)
        {
             result = 1;
        }
        else if(e1.v < e2.v){
             result = -1;
        }
        return result;
    }
}


public class SubSegment {

public static HashSet<String> S1;
public static HashSet<String> S2;
public static HashMap<String,Integer> M1;
public static String First;
public static String[] Arr;
public static String[] Arr_p;
public static String[] Arr_k;
public static record[] K1;
public static int[] K2;
public static int k=0;
public static int min=Integer.MAX_VALUE;
public static int max=Integer.MIN_VALUE;
public static int f_len=Integer.MAX_VALUE;
public static int len=0,end=0,f_end=0;
public static boolean found=false;


 public static void main(String[] args)
 {
  Scanner sc = new Scanner(System.in);
  First = sc.nextLine();

  First = First.replaceAll("[^a-zA-Z| |]", " ");
  First = First.replaceAll("  ", " ");
  Arr=First.split(" ");
  Arr_p=First.split(" ");
  for(int i=0;i<Arr.length;i++)
      Arr[i]=Arr[i].toLowerCase();
  k = sc.nextInt();
  sc.nextLine();

  String tmp;

  /* Initializing the basic data structure */
  M1=new HashMap<String,Integer> ();
  S1=new HashSet<String> ();
  S2=new HashSet<String> ();
  Arr_k=new String[k];
  K1=new record[k];
  int fix=0;
  /* reading the k words putting in S1,M1 and array Arr_k*/
    for(int i=0;i<k;i++){
      tmp= sc.nextLine().toLowerCase().trim();
    
      if(!S1.contains(tmp))
      {
        M1.put(tmp,fix);
        S1.add(tmp);
        Arr_k[fix++]=new String(tmp);
      }
    
  }//end of for

  K1=new record[M1.size()];
  for(int i=0;i<fix;i++)
  {
      K1[i]=new record();
      if(M1.containsKey(Arr_k[i]))
      K1[i].s=Arr_k[i];
      K1[i].v=-1;
  }
  /* copy s1 to s2 */
  S2.addAll(S1);

   int i;
  for(i=0;i<Arr.length;i++)
  {
      if(S2.contains(Arr[i]))
      {
          S2.remove(Arr[i]);
          if(M1.containsKey(Arr[i]))
          {
              int t_int = M1.get(Arr[i]);
              K1[t_int].v=i;
              if(min > i)
                min = i;
              if(max < i)
               max = i;
          }

      }
       else if(M1.containsKey(Arr[i]))
      {
          int t_int=M1.get(Arr[i]);
          K1[t_int].s=Arr[i];
          K1[t_int].v=i;
          if(min > i)
              min = i;
          if(max < i)
              max = i;
       }

      if(S2.isEmpty())
      {
          end=i;
          len=max-min;
          if(f_len > len)
          {
              f_len=len;
              f_end=max;
              if(len == k-1)
                 found=true;
              break;

          }
      }
  }//end of for
  if(found==true)
  {   for(int j=f_end-f_len;j<=f_end;j++)
      {
          System.out.print(Arr_p[j]+" ");
      }
  }
 else if(i==Arr.length && !S2.isEmpty())
  {
     System.out.println("NO SUBSEGMENT FOUND");
 }
 else // now handling the rest of the array
  {   int m_flag=0;
      Arrays.sort(K1,new recordComparator());
      int counter=max+1;
      K2=new int[K1.length];
      for(int p=0;p<K2.length;p++)
      {
          K2[p]=-1;
      }
      record temp_record=new record();
      temp_record.s=K1[0].s;
      temp_record.v=K1[0].v;
      if(f_len > K1[K1.length-1].v- K1[0].v)
      {
              f_len=K1[K1.length-1].v- K1[0].v;
              f_end=K1[K1.length-1].v;
              if(f_len == k-1)
              {
                    m_flag=1;
              }


      }
      while(counter < Arr.length && m_flag==0)
      {

          if(Arr[counter].equalsIgnoreCase(temp_record.s) )//&& M1.containsKey(Arr[counter]))
          {
               K2[M1.get(K1[0].s)]=counter;

               for(int t=0;t<K1.length;t++)
               {
                   if(K2[M1.get(K1[t].s)]!=-1)
                   {
                        K1[t].v=K2[M1.get(K1[t].s)];
                   }
               }
               for(int t=0;t<K2.length;t++)
               {
                    K2[t]=-1;
               }
              Arrays.sort(K1,new recordComparator());

              temp_record.s=new String(K1[0].s);
              temp_record.v=K1[0].v;
              if(f_len > K1[K1.length-1].v- K1[0].v)
              {
                    f_len=K1[K1.length-1].v- K1[0].v;
                    f_end=K1[K1.length-1].v;
                    if(f_len == k-1)
                    {
                        break;
                  }


              }
          }
          else if(M1.containsKey(Arr[counter]))
          {
              K2[M1.get(Arr[counter])]=counter;
          }
          counter++;
      }
      for(int j=f_end-f_len;j<=f_end;j++)
      {
          System.out.print(Arr_p[j]+" ");
      }
 }
 }
}
