public class ArrayArgument
{ 
  public static void main(String[] args)
  {
    int nums[ ] = {2, 18, 1, 27, 16};

    // the call is made here
    System.out.println("The maximum value is " + findMaximum(nums));
    
  }

  // this is the called method
  // it is used to find the maximum value
  // stored in an array of integers
  public static int findMaximum(int vals[])
  {
    int i, max = vals[0];

    for (i = 1; i < vals.length; i++)
      if (max < vals[i]) max = vals[i];

    return max;
  }

}