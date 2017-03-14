package chapter9;

//**************************************************************************
//Class CountLetters reads in a sample of text line by line and counts the
//frequency of occurrence of each alphabetic character.
//**************************************************************************
import java.io.*;
import java.util.*;
public class CountLetters
{
public static void main(String[] args) throws IOException
{
 Scanner dataFile;
 char letter;
 int index;
 int location;
 String inString;
 int[] letterCount = new int[26];
 dataFile = new Scanner(new FileReader("Words.in"));

 while (dataFile.hasNextLine())
 {
   inString = dataFile.nextLine();

   for (location = 0; location < inString.length(); location++)
   {
     letter = inString.charAt(location);
     if ((letter >= 'A' && letter <= 'Z') || 
         (letter >= 'a' && letter <= 'z'))
     {
       // Convert letter to an index
       index = (int)Character.toUpperCase(letter) - (int)'A';
       // Increment counter
       letterCount[index] = letterCount[index] + 1;
     }
   }
 }
 // Write the character and the count on the screen
 for (index = 0; index < letterCount.length; index++)
   System.out.println("The number of " +
     (char)(index + (int)'A') + "'s is " + letterCount[index]);
 dataFile.close();
}
}

