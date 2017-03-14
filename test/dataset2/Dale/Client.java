package chapter6;

//*********************************************************************
// This class represents a lawncare client for billing purposes
//*********************************************************************
import java.util.Scanner;
import java.io.*;

import chapter3.Name;
import chapter4.Time;

public class Client {
	Name name; // Client name

	Address address; // Client address

	String billing; // Time and charge string

	Time totalTime; // Total time for this client

	double totalCharges; // Total charges for this client

	static double rate = 0.0; // Billing rate for all clients

	public Client(Scanner in) throws IOException // Scanner constructor
	{
		Time time; // Declare local variables
		int hours;
		int minutes;
		double charge;
		String last = in.next(); // Read name
		String first = in.next();
		String middle = in.next();
		name = new Name(first, last, middle);
		String separator = in.nextLine();
		address = new Address(in); // Read address
		int numberOfJobs = in.nextInt(); // Loop termination value
		// Read and process jobs to create billing string and totals
		int count = 1; // Initialize loop
		billing = "";
		totalTime = new Time();
		totalCharges = 0.0;
		while (count <= numberOfJobs) {
			hours = in.nextInt(); // Read time
			minutes = in.nextInt();
			time = new Time(hours, minutes, 0);
			charge = time.getTime() / 3600.0 * rate; // Compute charge
			// Add time and charge to billing string
			billing = billing + "  " + hours + ":" + minutes + "     $"
					+ charge + '\n';
			totalTime = totalTime.plus(time); // Update totals
			totalCharges = totalCharges + charge;
			count++; // Increment loop control variable
		}
		separator = in.nextLine();
	}

	public Client() // Default constructor
	{
		name = new Name();
		address = new Address();
		billing = "";
		totalTime = new Time();
		totalCharges = 0.0;
	}

	public void printBill(PrintWriter out) {
		out.println(name);
		out.println(address);
		out.println();
		out.println("Job Time    Charge");
		out.println(billing);
		out.println("Total time: " + totalTime.getHours() + ":"
				+ totalTime.getMinutes());
		out.println("Total charges: $" + totalCharges);
		out.println();
	}

	// Field get methods
	public Time getTotalTime() {
		return totalTime;
	}

	public double getTotalCharges() {
		return totalCharges;
	}

	// Field set method
	public static void setRate(double newRate) {
		rate = newRate;
	}
}
