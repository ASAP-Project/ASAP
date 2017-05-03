package chapter14;

import javax.swing.*;                        // User interface classes
import java.awt.*;                           // User interface classes
import java.awt.event.*;                     // Event handling classes
public class Calculator2 extends JApplet implements ActionListener
{
	// Field, label, and variable for use by the event handler
	private JTextField inputField;             // Data field
	private JLabel register;                   // Result shown on screen
	private double result;                     // Keeps current value

	// Event handler for buttons in the applet
	public void actionPerformed(ActionEvent event)
	{
		double secondOperand;                    // Holds input value
		String whichButton;                      // Holds the button's name
		// Get the operand, checking for numeric format error
		try
		{
			secondOperand = Double.parseDouble(inputField.getText());
		}
		catch (NumberFormatException except)
		{
			secondOperand = 0.0;                   // If error, set to zero
		}
		whichButton = event.getActionCommand();  // Get the button's name
		if (whichButton.equals("+"))             // When the name is "+"
			result = result + secondOperand;       //  add the operand
		else if (whichButton.equals("-"))        // When the name is "-"
			result = result - secondOperand;       //  subtract operand
		else
			result = 0.0;                          // Clear result to zero
		register.setText("" + result);           // Display result
		inputField.setText("");                  // Clear input
	}

//	Applet initialization method
	public void init()
	{
		JLabel resultLabel;                      // Indicates output area
		JLabel entryLabel;                       // Label for input field
		JButton add;
		JButton subtract;
		JButton clear;
		result = 0.0;
		// Instantiate labels and initialize input field
		resultLabel = new JLabel("Result:");
		register = new JLabel("0.0", JLabel.RIGHT);
		entryLabel = new JLabel("Enter #:");
		inputField = new JTextField("", 10);
		// Instantiate button objects
		add = new JButton("+");
		subtract = new JButton("-");
		clear = new JButton("Clear");
		// Register the button listener with the buttons
		add.addActionListener(this);
		subtract.addActionListener(this);
		clear.addActionListener(this);
		// Add interface elements to applet window
		setLayout(new GridLayout(4,2));          // Set the layout manager
		add(resultLabel);
		add(register);
		add(entryLabel);
		add(inputField);
		add(add);
		add(subtract);
		add(clear);
	}
}
