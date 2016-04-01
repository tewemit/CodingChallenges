/**
Instruction/Question
********************

Write a function that takes a matrix and examines each item in a spiral order, printing each item as it comes to it.

For example, given a matrix like this as input:
[[11, 12, 13, 14, 15],
[21, 22, 23, 24, 25],
[31, 32, 33, 34, 35],
[41, 42, 43, 44, 45]]

Your program must print:
11 12 13 14 15 25 35 45 44 43 42 41 31 21 22 23 24 34 33 32
**/
// A working solution
/*
 * @author Tewelle Welemariam
 * 
 * I will use four indices: upper, bottom, left and right
 *  which are going to be used to point where we will start printing rows and columns i.e
 *  when upper > bottom or left > right then we are finished.
 */

public class Matrix
{
	public static void main(String[] args) 
	{
		// we can use a scanner to read line from standard input but i will keep it simple by 
		// initializing the matrix.
		int[][] Matrix = {
				{11, 12, 13, 14, 15},
				{21, 22, 23, 24, 25},
				{31, 32, 33, 34, 35},
				{41, 42, 43, 44, 45}
				};
		// Call a function that prints the elements spirally
		printMatrix(Matrix); 
		System.exit(0);
	}


private static void printMatrix(int[][] matrix)
{
     if(matrix.length == 0)
         return;
     // Initialize the four indices
     int upper = 0;
     int bottom = matrix.length - 1; // number of rows minus 1
     int left = 0;
     int right = matrix[0].length - 1; // number of columns minus 1
 
     while(true)
     {
         // Std out  first row
         for(int j = left; j <= right; ++j) 
        	 System.out.print(matrix[upper][j] + " ");
         upper++;
         if(upper > bottom || left > right)
        	 break;
         // Std out  the rightmost column
         for(int i = upper; i <= bottom; ++i) 
        	 System.out.print(matrix[i][right] + " ");
         right--;
         if(upper > bottom || left > right) 
        	 break;
         // Std out  the bottom row
         for(int j = right; j >= left; --j)
        	 System.out.print(matrix[bottom][j] + " ");
         bottom--;
         if(upper > bottom || left > right) 
        	 break;
         // Std out  the leftmost column
         for(int i = bottom; i >= upper; --i) 
        	 System.out.print(matrix[i][left] + " ");
         left++;
         if(upper > bottom || left > right) 
        	 break;
     }
 }
}
