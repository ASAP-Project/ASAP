// this program approximates the function e raised to the x power
// using one, two, three, an four terms of an approximating polynomial

import java.io.*;   // needed to access input stream classes
import java.text.*; // needed for formatting
public class ApproxExponential
{  
  public static void main (String[] args) 
  throws java.io.IOException  
  {    
   String s1;  
   double x, actualValue, approx, difference;

   DecimalFormat df = new DecimalFormat("#.000000");

    // set up the basic input stream
      // needed for conversion capabilities  
    InputStreamReader isr = new InputStreamReader(System.in);
      // needed to use readLine()
    BufferedReader br = new BufferedReader(isr);
     
    System.out.print("Enter a value for x: ");
    s1 = br.readLine();
    x = Double.parseDouble(s1);

      // print two title lines
    System.out.println(" e to the x       Approximation      Difference");
    System.out.println("-------------     -------------     -------------");
  
    actualValue = Math.exp(x);    // use the Math class method

      // calculate the first approximation
    approx = 1;
    difference = Math.abs(actualValue - approx);
    System.out.println("  " + df.format(actualValue) + "          "
                            + df.format(approx) + "          "
                            + df.format(difference));

      // calculate the second approximation
    approx = approx + x;
    difference = Math.abs(actualValue - approx);
    System.out.println("  " + df.format(actualValue) + "          " 
                            + df.format(approx) + "          "
                            + df.format(difference));

      // calculate the third approximation
    approx = approx + Math.pow(x,2)/2.0;
    difference = Math.abs(actualValue - approx);
    System.out.println("  " + df.format(actualValue) + "          "
                            + df.format(approx) + "          "
                            + df.format(difference));
    
      // calculate the fourth approximation
    approx = approx + Math.pow(x,3)/6.0;
    difference = Math.abs(actualValue - approx);
    System.out.println("  " + df.format(actualValue) + "          "
                            + df.format(approx) + "          "
                            + df.format(difference));
  }
}