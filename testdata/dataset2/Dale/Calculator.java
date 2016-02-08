package chapter11;

//***************************************************************************
//This application implements a simple on-screen calculator
//***************************************************************************
import java.awt.*; 
import java.awt.event.*;
import javax.swing.*;
public class Calculator
{
static JTextField inputField;              // Data entry field
static JLabel register;                    // Result shown on screen
static double result;                      // Keeps current value
static JFrame calcFrame;                   // Declare a frame
static Container calcPane;                 // Content pane of frame
static NumericHandler operation;           // Declare numeric listener  
static ClearHandler clearOperation;        // Declare clear listener  
static JLabel resultLabel;                 // Labels output area
static JLabel entryLabel;                  // Label for input field
static JButton add;                        // Add button
static JButton subtract;                   // Subtract button
static JButton clear;                      // Clear button
 
// Listener for operation buttons
static class NumericHandler implements ActionListener          
{
 public void actionPerformed(ActionEvent event)
 {
   double secondOperand;                   // Holds input value
   String whichButton;                     // Holds the button's name
   // Get the operand
   secondOperand = 
     Double.valueOf(inputField.getText()).doubleValue();  
   whichButton = event.getActionCommand(); // Get the button's name
   if (whichButton.equals("+"))            // When the name is "add"
     result = result + secondOperand;      //   add the operand
   else                                    // Otherwise
     result = result - secondOperand;      //   subtract the operand
   register.setText("" + result);          // Display result
   inputField.setText("");                 // Clear input
 }
}
// Listener for clear button
static class ClearHandler implements ActionListener 
{
 public void actionPerformed(ActionEvent event)
 {
   result = 0.0;                           // Set result back to zero
   register.setText("0.0");                // Reset value in display
   inputField.setText("");                 // Clear input
  }
}

public static void main(String[] args)
{
 operation = new NumericHandler();         // Instantiate operation listener
 clearOperation = new ClearHandler();      // Instantiate clear listener
 result = 0.0;                             // Initialize result
 // Instantiate labels and initialize input field
 resultLabel = new JLabel("Result:");
 register = new JLabel("0.0", JLabel.RIGHT);
 entryLabel = new JLabel("Enter #:");
 inputField = new JTextField("", 10);
 // Instantiate button objects
 add = new JButton("+");
 subtract = new JButton("-");
 clear = new JButton("Clear");
 // Register the button listeners
 add.addActionListener(operation);
 subtract.addActionListener(operation);
 clear.addActionListener(clearOperation);
 calcFrame = new JFrame();                 //Give the frame a value
 calcFrame.setSize(300, 200);              //Specify size of frame
 calcFrame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
 calcPane = calcFrame.getContentPane();    //Get the content pane
 calcPane.setLayout(new GridLayout(4, 2)); //Set the layout manager
 // Add interface elements to calcFrame
 calcPane.add(resultLabel);
 calcPane.add(register);
 calcPane.add(entryLabel);
 calcPane.add(inputField);
 calcPane.add(add);
 calcPane.add(subtract);
 calcPane.add(clear);
 calcFrame.setVisible(true);               //Show the frame
}
}

