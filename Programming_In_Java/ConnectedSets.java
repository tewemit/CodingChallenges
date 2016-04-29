/*
 * 
Interview Street (Amazon Coding Challenge) : Connected Sets

Given a 2–d matrix , which has only 1’s and 0’s in it. Find the total number of connected sets in that matrix.
 
 
Explanation:
Connected set can be defined as group of cell(s) which has 1 mentioned on it and have at least one other cell in that set with which they share the neighbor relationship. 
A cell with 1 in it and no surrounding neighbor having 1 in it can be considered as a set with one cell in it. 
Neighbors can be defined as all the cells adjacent to the given cell in 8 possible directions ( i.e N , W , E , S , NE , NW , SE , SW direction ). 
A cell is not a neighbor of itself.
 
 
Input format :
 
First line of the input contains T , number of test-cases.
Then follow T testcases. Each testcase has given format.
N [ representing the dimension of the matrix N X N ].
Followed by N lines , with N numbers on each line.
 
 
 
Ouput format :
 
For each test case print one line ,  number of connected component it has.
 
Sample Input :
 
4
4
0 0 1 0
1 0 1 0
0 1 0 0
1 1 1 1
4
1 0 0 1
0 0 0 0
0 1 1 0
1 0 0 1
5
1 0 0 1 1
0 0 1 0 0
0 0 0 0 0
1 1 1 1 1
0 0 0 0 0
8
0 0 1 0 0 1 0 0
1 0 0 0 0 0 0 1
0 0 1 0 0 1 0 1
0 1 0 0 0 1 0 0
1 0 0 0 0 0 0 0
0 0 1 1 0 1 1 0
1 0 1 1 0 1 1 0
0 0 0 0 0 0 0 0
 
Sample output :
 
1
3
3
9
 
Constraint :
 
0 < T < 6 
0 < N < 1009 

Basics are must, this one truly teaches it....
a simple recursive code can compute it with max 1.6 sec...
than non-recursive code taking more than 5 sec to compute the same....
but, finally cleared all 10/10 test cases.

 * 
 */


import java.util.*;

public class ConnectedSets {
 
 public static int T;
 public static int n;
 public static int arr[][];
 public static int cs[];
 public static Stack<arr_point> s;
 public static Hashtable<String,Integer> ht;
  
 public static void main(String[] args) {
   
  Scanner in = new Scanner(System.in);
  T = in.nextInt();
  cs = new int[T];
  s = new Stack<arr_point>();
  ht = new Hashtable<String,Integer>();
   
  for(int i=0;i<T;i++)
  {
   n = in.nextInt();
   arr = new int[n][n];
    
   for(int j=0;j<n;j++)
   {
    for(int k=0;k<n;k++)
    {
     arr[j][k] = in.nextInt();
    }
   }
    
   for(int j=0;j<n;j++)
   {
    for(int k=0;k<n;k++)
    {
     if(arr[j][k] == 1)
     {
      cs[i] += solve(j,k);
     }
    }
   }
  }
   
  for(int i=0;i<T;i++)
  {
   System.out.println(cs[i]);
  } 
 }
  
  
 public static int solve(int i,int j)
 {
  arr[i][j] = 0;
  
   
  if(i+1<n && arr[i+1][j] == 1)
  {
   solve(i+1,j);
  }
  if(i-1>=0 && arr[i-1][j] == 1)
  {
   solve(i-1,j);
  }
  if(j+1<n && arr[i][j+1] == 1)
  {
   solve(i,j+1);
  }
  if(j-1>=0 && arr[i][j-1] == 1)
  {
   solve(i,j-1);
  }
   
  if(i+1<n && j+1<n && arr[i+1][j+1] == 1)
  {
   solve(i+1,j+1);
  }
   
  if(i+1<n && j-1>=0 && arr[i+1][j-1] == 1)
  {
   solve(i+1,j-1);
  }
   
  if(i-1>=0 && j+1<n && arr[i-1][j+1] == 1)
  {
   solve(i-1,j+1);
  }
   
  if(i-1>=0 && j-1>=0 && arr[i-1][j-1] == 1)
  {
   solve(i-1,j-1);
  }
   
  return 1;
 }
  
  
 
}
 
class arr_point
{
 public int j;
 public int k;
  
 arr_point()
 {
  j = k = 0;
 }
}
