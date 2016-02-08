package chapter8;

import java.util.*;

public class ColorDemo
{
	public enum Spectrum {RED, ORANGE, YELLOW, GREEN, BLUE, INDIGO, VIOLET}

	public static void main(String[] args)
	{
		Spectrum color;
		Scanner in = new Scanner(System.in);
		System.out.print("Enter RED, YELLOW, or GREEN: ");
		color = Spectrum.valueOf(in.nextLine());
		switch (color)
		{
		case RED: System.out.println("High forest fire danger"); break;
		case YELLOW: System.out.println("Moderate forest fire danger"); break;
		case GREEN: System.out.println("Low forest fire danger"); break;
		default: System.out.println("No forest fire rating");
		}
	}
}
