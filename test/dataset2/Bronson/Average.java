import javax.swing.*; // needed for dialog boxes
import java.text.*;   // needed for formatting
public class Average
{
  public static void main (String[] args) 
  {
     double num1, num2, num3, avg;
     String input;     
    
     DecimalFormat df = new DecimalFormat("###.00");

     input = JOptionPane.showInputDialog("Enter a number:");
     num1 = Double.parseDouble(input);

     input = JOptionPane.showInputDialog("Enter a second number:");
     num2 = Double.parseDouble(input);
     
     input = JOptionPane.showInputDialog("Enter a third number:");
     num3 = Double.parseDouble(input);
     
     avg = (num1 + num2 + num3) / 3.0;
     JOptionPane.showMessageDialog(null, 
		"The average is " + df.format(avg), 
                "Average Computation",
                JOptionPane.INFORMATION_MESSAGE);

    System.exit(0);
 }
}
