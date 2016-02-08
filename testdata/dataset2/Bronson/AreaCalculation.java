import javax.swing.*;
public class AreaCalculation
{
  public static void main(String[] args)
  {
    double radius;
    String s1;

    s1 = JOptionPane.showInputDialog("Please type in the radius:");
    radius = Double.parseDouble(s1);
     
    if (radius < 0.0)
      System.out.println("A negative radius is invalid" );
    else
      System.out.println("The area of this circle is " + Math.PI * Math.pow(radius,2) );

    System.exit(0);
  }
}
