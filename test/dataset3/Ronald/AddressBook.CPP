/******************************************************
 * File: AddressBook.cpp
 *
 * Methods in this file:
 *  1-  AddRec( int n ) - Adds a new record to the file
 *  2-  DeleteRec( int n) - Deletes a record from the file
 *  3-  DisplayData( int n ) - Displays all records in the file
 *  4-  InitData() - Initializes the file if it is empty
 *  5-  ReadData(int recID) - Reads a record from the file
 *  6-  RecordCount() - Calculates the number of records in the file
 *  7-  UpdateData( long n) - Updates a record in the file 
 *  8-  UpdateRec( int n ) - Gets the data to update a record 
 *  9-  WriteData() - Writes a record to the file
 * 
 * Copyright (c) 2002-2010 Advanced Applications Total Applications Works.
 * (AATAW)  all Rights Reserved.

 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 *   - Redistributions of source code must retain the above copyright
 *     notice, this list of conditions and the following disclaimer.
 *
 *   - Redistributions in binary form must reproduce the above copyright
 *     notice, this list of conditions and the following disclaimer in the
 *     documentation and/or other materials provided with the distribution.
 *
 *   - Neither the name of Sun Microsystems nor the names of its
 *     contributors may be used to endorse or promote products derived
 *     from this software without specific prior written permission.
 *
 *
 * AATAW grants you ("licensee") a non-exclusive, royalty free, license to use,
 * modify and redistribute this software in source and binary code form,
 * provided that i) this copyright notice and license appear on all copies of
 * the software; and ii) licensee does not utilize the software in a manner
 * which is disparaging to AATAW.
 *
 * This software is provided "as IS," without a warranty of any kind. all
 * express or implied conditions, representations and warranties, including any
 * implied warranty of merchantability, fitness for a particular purpose or
 * non-infringement, are hereby excluded. AATAW and its licensors shall not be
 * liable for any damages suffered by licensee as a result of using, modifying
 * or distributing the software or its derivatives. in no event will AATAW or its
 * licensors be liable for any lost revenue, profit or data, or for direct,
 * indirect, special, consequential, incidental or punitive damages, however
 * caused and regardless of the theory or liability arisinG out of the use of
 * or inability TO use software, even if AATAW Has been advised of the
 * possibility of such damages.
 *
 * This software is not designed or intended for use in on-line control of
 * aircraft, air traffic, aircraft navigation or aircraft communications; or in
 * the design, construction, operation or maintenance of any nuclear
 * facility. licensee represents and warrants that it will not use or
 * redistribute the Software for such purposes.
 *
 * Changelog:
 *
 *
 ******************************************************/ 
            

#include <iostream>
#include <iomanip>
#include <string.h>
#include <cstdlib>
#include <stdio.h>
#include "addressbook.h"
#include <fstream>  

using std::ofstream ;
using std::ifstream ;
using std::cout ;
using std::cin ;
using std::ios;
using std::endl;
using std::setw;
using std::setiosflags;

/* *************************************************
 *
 * *************************************************/
AddressBook::AddressBook() {
      // If file is empty, initialize it
   if ( RecordCount() < 1 )
      InitData() ;
}


/* *************************************************
 * 
 * *************************************************/
AddressBook::~AddressBook() {
 
}
/* *************************************************
 * Display all records in the AddressBook.dat file
 * 1- Create a header for the data to be displayed
 * 2- Create a loop to read all of the records in the file
 * 3- Write data from each record to stdout:`cout
 * *************************************************/
void AddressBook::DisplayData(  int n )    {    
   
                
   cout << "\nThere are " << n << " address records in file\n";
   cout << setiosflags( ios::left ) << setw( 10 ) << "RecID"
      << setw( 16 ) << "Last Name" << setw( 12 )
      << "First Name" << resetiosflags( ios::left )
      << setw( 12 ) << "Telephone" << setw( 13 ) << "Address" << endl;
	  
   for( int ii = 0; ii < n; ii++)    {    // for each one,
         
      ReadData(ii);               // read an address record from disk
      //LoadAddrArray( addrRec , ii ) ;             
   
      cout << setiosflags( ios::left ) << setw( 10 ) 
         << recordID 
         << setw( 16 ) << lastName 
         << setw( 15 ) << firstName 
         << setw( 15 ) << telephone 
		 << setw( 15 ) << address 
         << endl; 
   }
}
/************* End of DisplayData ***************/


/****************************************************
 * 1- Create and initialize an array with address records
 * 2- Use the array to write the data to instance variables
 * 3- Write object to file a record at a time
 ****************************************************/
void AddressBook::InitData() {
   	long sizeAR = 14 ;	 

    char *addrRecord[ 14 ][ 9 ]  = {
                  {"James", "Wilie", "123 Main St.", "Garner", "NC", "27500",  "MyID@MyISP", "919-555-3442", "919-555-5442"},
                  {"Julie", "Smith", "123 Oak St.", "Raleigh", "NC", "27500",  "MyID@MyISP",   "919-555-3782", "919-555-5782"},
                  {"Mary", "Easley", "123 Walnut St.", "Apex", "NC", "27500",  "MyID@MyISP",   "919-555-5552", "919-555-6552"},
                  {"Cato", "Willingham", "123 Jones St.", "Durham", "NC", "27500", "MyID@MyISP",   "919-555-3492", "919-555-5492"},
                  {"Mike", "Jordan", "123 Saunders St.", "Apex", "NC", "27500",  "MyID@MyISP",   "919-555-3882", "919-555-5882"},
                  {"Carole", "Fusemi", "123 Oak Lane", "Raleigh", "NC", "27500",  "MyID@MyISP",   "919-555-3472", "919-555-5472"},
                  {"Peter", "Wie", "123 Oak Way", "Garner", "NC", "27500", "MyID@MyISP",   "919-555-3642", "919-555-5642"},
                  {"Donald", "Hill", "123 Oak Blvd.", "Cary", "NC", "27500", "MyID@MyISP",   "919-555-3452", "919-555-5452"},
                  {"Regina", "Bell", "123 Walnut Lane", "Apex", "NC", "27500",  "MyID@MyISP",   "919-555-3342", "919-555-5342"},
                  {"Alicia", "Keyes", "123 Walnut Way", "Raleigh", "NC", "27500",  "MyID@MyISP",   "919-555-3332", "919-555-5332"},
                  {"Charles", "Lawrence", "123 Whatis St.", "Garner", "NC", "27500",  "MyID@MyISP",   "919-555-3222", "919-555-5222"},
                  {"Robert", "Urengo", "123 Academy St.", "Durham", "NC", "27500",  "MyID@MyISP",   "919-555-3112", "919-555-5112"},
                  {"John", "Wieland", "123 MaIn St.", "Apex", "NC", "27709",  "MyID@MyISP", "919-555-9088", "919-555-9089"},
                  {"Keith", "Makey", "404 Walnut Ave.", "Raleigh", "NC", "27511",  "MyID@MyISP", "919-555-9088", "919-555-9089"}
             } ;

   
   for ( int ii = 0; ii < sizeAR; ii++ ) {
		 
      recordID = ii ;
      strcpy( firstName, addrRecord[ ii ][ 0 ] ) ;
      strcpy( lastName, addrRecord[ ii ][ 1 ] ) ;		 
      strcpy( address, addrRecord[ ii ][ 2 ] ) ;
      strcpy( city, addrRecord[ ii ][ 3 ] ) ;
      strcpy( state, addrRecord[ ii ][ 4 ] ) ;
      strcpy( zip, addrRecord[ ii ][ 5 ] ) ;
      strcpy( telephone, addrRecord[ ii ][ 7 ] ) ;
      strcpy( fax, addrRecord[ ii ][ 8 ] ) ;
      strcpy( email, addrRecord[ ii ][ 6 ] ) ;

	  //pad( this ) ;
	  WriteData();
   }

}
/************* End of InitData2 ***************/


/* *************************************************
 * 1- Create an ifstream object for input
 * 2- Open the Addressbook.dat file for reading
 * 3- Calculate the point where the record to be read is located
 * 4- Read the record from the file  
 * *************************************************/
void AddressBook::ReadData(int recID)  {    // read recordID = recID
                                 // from file
   ifstream infile;                           // make stream
   infile.open("Addressbook.dat", ios::binary);
   infile.seekg( recID * sizeof( AddressBook ) );         // move file ptr  
   infile.read( (char*)this, sizeof(*this) ); // read one addressrecord
}
/************* End of ReadData ***************/


/* *************************************************
 * 1- Create an ofstream object for output
 * 2- Open the Addressbook.dat file for writing
 * 3- Calculate the point where the record to be written is located
 * 4- Write the record to the file  
 * *************************************************/
void AddressBook::WriteData()   {        // write AddressBook to end of file
   
   ofstream outfile;             // make an output file stream
                                 // open it
   outfile.open("Addressbook.dat", ios::app | ios::binary);
   outfile.write( (char*)this, sizeof(*this) ); // write to it
}
/************* End of WriteData ***************/

/* *************************************************
 * 1- Create an ofstream object
 * 2- Open the Addressbook.dat file for writing
 * 3- Calculate the point where the record to be updated is located
 * 4- Write the record to the file using ios::ate so data 
 *    can be written anywhere in the file. 
 * *************************************************/
void AddressBook::UpdateData( long n)   {        
   
   ofstream outfile;             // make an output file stream
                                 // open the file                                 
   outfile.open("Addressbook.dat", ios::ate | ios::binary);
   outfile.seekp( (n * sizeof(*this) ) , ios::beg); 
   outfile.write( (char*)this, sizeof(*this) ); // write to it
}
/************* End of UpdateData ***************/

/* *************************************************
 * 1- Create an ifstream object
 * 2- Open the Addressbook.dat file for reading
 * 3- Calculate the size of the file
 * 4- Using the size of the file, divide this size
 *    by the size of the record to determine the 
 *    number of records.
 * *************************************************/
int AddressBook::RecordCount()    {      
                                 
   ifstream infile;
   infile.open("Addressbook.dat", ios::binary);
   infile.seekg(0, ios::end);    // go to 0 bytes from end
                                 // calculate number of  address records
   return (int)infile.tellg() / sizeof( AddressBook );
}
/************* End of RecordCount ***************/

/* *************************************************
 * 1- Get address record dat from user
 * 2- Write record to file
 * *************************************************/
void AddressBook::AddRec(int n )  {
    
   
   recordID = n ; 	
   cout << "\n   Enter first name: "; 
   cin >> firstName;
   cout << "\n   Enter last name: "; 
   cin >> lastName;	   
   cout << "\n   Enter address: ";  
   cin.getline( address , 45 ) ;     // sometimes it takes two
                                     // tries to get a multi-word
   cin.getline( address , 45 ) ;     // input fron stdin
   cout << "\n   Enter city: "; 
   cin >> city;	 
   cout << "\n   Enter state: "; 
   cin >> state;
   cout << "\n   Enter zip code: "; 
   cin >> zip;	 
   cout << "\n   Enter telephone: "; 
   cin >> telephone;
   cout << "\n   Enter fax: "; 
   cin >> fax;
   cout << "\n   Enter email: "; 
   cin >> email;   
   
   WriteData() ;   // write record to file

}
/************* End of InsertNode ***************/

/* *************************************************
 * 1- Dispal all of the records 
 * 2- Get record to be updated
 * 3- Determine the fields to be updated using a menu
 * 4- When all of the intended fields have been updated, 
 *    write the record to the file
 * 5- Otherwise, allow the user to quit
 * *************************************************/
void AddressBook::UpdateRec( int n ) {

   bool loopCtl = true ; 
   int  option_1 = 0 , recID = 0;
   char str[5] ;

   system( "Cls" );
   DisplayData( n )   ;   
   cout << "Enter the record number you want to update." << endl ;
   cin >> str ;
   recID = atoi(str);   
   ReadData( recID ) ;

   
   system( "Cls" );
   cout << "Record to be updated\n" << " 1: " << firstName
	    << " 2: " << lastName << " 3: " << address << " 4: " << city
		<< " 5: " << state << "\n 6: " << zip << " 7: " << telephone
		<< " 8: " << fax << " 9: " << email << endl ;
 
   while( loopCtl) {

      n = RecordCount();  // how many records in file?

      cout << "+-----------------------------------------+"  << endl;
      cout << "|                                         |"  << endl;
      cout << "|   UPDATE ADDRESSBOOK RECORD PANEL       |"  << endl ;
      cout << "|                                         |"  << endl;
      cout << "| 1-  Update first name                   |"  << endl;
      cout << "| 2-  Update last name                    |"  << endl;
	  cout << "| 3-  Update address                      |"  << endl;
      cout << "| 4-  Update city                         |"  << endl;
      cout << "| 5-  Update state                        |"  << endl;
	  cout << "| 6-  Update zip                          |"  << endl;
	  cout << "| 7-  Update telephone                    |"  << endl;
	  cout << "| 8-  Update fax                          |"  << endl;
	  cout << "| 9-  Update email                        |"  << endl;
      cout << "| 10- Show updated record                 |"  << endl;
	  cout << "| 11- Save the updated record             |"  << endl;
	  cout << "| 12- Quit                                |"  << endl;
      cout << "|                                         |"  << endl;
	  cout << "|                                         |"  << endl;
	  cout << "| When you are finished updating the      |"  << endl;
	  cout << "| reord, enter 10 to view the updates, or |"  << endl;
	  cout << "| enter 11 to store the updated record.   |"  << endl;
      cout << "+-----------------------------------------+"  << endl;

          cout << " " << endl;
          cout << "Please enter a number for one of the above options." << endl;

      cin >> str ;


	  option_1 = atoi(str);


      switch (option_1) {
         case 1:
            cout << "Please enter the changes to the first name." << firstName << endl ;
			cin >> firstName ;
         break;

         case 2:
            cout << "Please enter the changes to the last name." << lastName << endl ;
			cin >> lastName ;
         break;

         case 3:
            cout << "Please enter the changes to the address." << address << endl ;
			cin.getline( address , 45 ) ;     // sometimes it takes two
                                     // tries to get a multi-word
            cin.getline( address , 45 ) ;     // input fron stdin
         break;

         case 4:
            cout << "Please enter the changes to the city." << city << endl ;
			cin >> city ;
         break;

         case 5:
            cout << "Please enter the changes to the state." << state << endl ;
			cin >> state ;                 
         break;

         case 6:
            cout << "Please enter the changes to the zip." << zip << endl ;
			cin >> zip ;                    
         break;

         case 7:
            cout << "Please enter the changes to the telephone." << telephone << endl ;
			cin >> telephone ;                  
         break;

         case 8:
            cout << "Please enter the changes to the fax." << fax << endl ;
			cin >> fax ; 
         break;

         case 9:
            cout << "Please enter the changes to the email." << email << endl ;
			cin >> email ; 
         break;

         case 10:            
            system( "Cls" );
            cout << "Updated record looks like \n" << " 1: " << firstName
	             << " 2: " << lastName << " 3: " << address << " 4: " << city
                 << " 5: " << state << "\n 6: " << zip << " 7: " << telephone
		         << " 8: " << fax << " 9: " << email << endl ;
            system( "Pause" );
         break;

         case 11:
            UpdateData( recID ) ; 

         break;

         case 12:
            loopCtl = false; 

         break;

         default:
            cout << "Please enter a number between one and ten" << endl ;
			system( "Pause" );
		  }

          system( "Cls" );

   }
}
/************* End of UpdateRec ***************/


/* *************************************************
 * 1- Display all of the records
 * 2- Get the record to be deleted
 * 3- Delete the record
 * 4- Otherwise, quit
 * *************************************************/
void AddressBook::DeleteRec( int n)
{
   
   bool loopCtl = true ; 
   int  option_1 = 0 , recID = 0;
   char str[5] , chr;

   system( "Cls" );
   DisplayData( n )   ;   
   cout << "Enter the record number you want to delete." << endl ;
   cin >> str ;
   recID = atoi(str);   
   ReadData( recID ) ;  // ID of record to be deleted

   
   strcpy( firstName , "" ) ;
   strcpy( lastName , "" ) ;
   strcpy( address , "" ) ;
   strcpy( city , "" ) ;
   strcpy( state , "" ) ;
   strcpy( zip , "" ) ;
   strcpy( telephone , "" ) ;
   strcpy( fax , "" ) ;
   strcpy( email , "" ) ;      
   
   cout << "do you really want to delete recordID " << recID << " (y/n)?" << endl ;
   cin >> chr  ;
   if ( chr == 'y' || chr == 'Y' ) {
	   UpdateData( recID ) ; 
   }
}
/************* End of DeleteNode ***************/
