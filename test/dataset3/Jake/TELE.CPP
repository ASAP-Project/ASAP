    // TELEPHONE BILLING //

// HEADER FILES

#include <stdio.h>
#include <conio.h>
#include <string.h>
#include <process.h>
#include <ctype.h>
#include <dos.h>
#include <dir.h>
#include <fstream.h>


// CLASS HAVING THE RECORD OF CUSTOMER
class customer
{
          char ph[10];
          char name[30];
          char add[40];
          char type;
     public :
          void append();
          void display();
          void deleter();
          void modify();
          void list();
          void help();
}cust;


// FUNCTION TO DISPLAY THE MESSAGE AT THE BOTTOM OF THE SCREEN

void message(char mess[80])
{
     int l,d;
     l=strlen(mess);
     d=l/2;
     gotoxy(2,24);
     textcolor(WHITE+BLINK);
     textbackground(BLACK);
     cprintf("                                                                             ");
     gotoxy(40-d,24);
     clreol();
     cprintf("%s",mess);
     textcolor(BLACK);
     textbackground(WHITE);
}


// MAIN FUNCTION HAVING THE MAIN MENU

void main()
{
     textcolor(BLACK);
     textbackground(WHITE);
     char ch,ch1;
     while(1)
     {
          clrscr();
          textcolor(WHITE);
          textbackground(BLACK);
          gotoxy(25,5);
	  cprintf("TELEPHONE BILLING SYSTEM 1.0");
          textcolor(BLACK);
          textbackground(WHITE);
          gotoxy(25,8);
          cout<<"  D    -    Display a Bill";
          gotoxy(25,10);
          cout<<"  L    -    List of customers";
          gotoxy(25,12);
          cout<<"  H    -    Help";
          gotoxy(25,14);
          cout<<"  M    -    Modify a record";
          gotoxy(25,16);
          cout<<"  Q    -    Quit";
          message("Select your choice");
          gotoxy(40,18);
          ch =getch();
          ch = toupper(ch);
          switch(ch)
          {
          case ('Q') : textcolor(WHITE);
                       textbackground(BLACK);
                       clrscr();
                       exit(1);
          case ('D') : cust.display();
                       break;
          case ('L') : cust.list();
                       break;
          case ('H') : cust.help();
                       break;
          case ('M') :
                         ch1 = 'A' ;
                         while(ch1 != 'Q')
                         {
                              clrscr();
                              textcolor(WHITE);
                              textbackground(BLACK);
                              gotoxy(25,5);
                              cprintf("MAHANAGAR TELEPHONE NIGAM LTD.");
                              textcolor(BLACK);
                              textbackground(WHITE);
                              gotoxy(25,9);
                              cout<<"  A    -    Append a record";
                              gotoxy(25,11);
                              cout<<"  D    -    Delete a record";
                              gotoxy(25,13);
                              cout<<"  M    -    Change a record";
                              gotoxy(25,15);
                              cout<<"  Q    -    Quit";
                              message("Select your option");
                              ch1 = getch();
                              ch1 = toupper(ch1);
                              switch(ch1)
                              {
                                   case ('A') : cust.append();
                                                break;
                                   case ('D') : cust.deleter();
                                                break;
                                   case ('M') : cust.modify();
                                                break;
                              }
                    }

          }
     }
}


// FUNCTION TO ADD THE CUSTOMER RECORD IN THE FILE

void customer :: append()
{
     char choice;
     fstream fp;
     fp.open("tphone.dat", ios::app);
     if (!fp)
     {
          cout<<"Unable to open FILE.";
          getch();
          return;
     }
     while(1)
     {
          clrscr();
          gotoxy(3,3);
          cout<<"Customer Record #";
          message("Enter the customer record");
          while(1)
          {
               message("Enter the name");
               gotoxy(3,5);
               cout<<"Name              :   ";
               gotoxy(25,5);
               gets(name);
               if(strlen(name)==0)
               {
                    gotoxy(2,23);
                    clreol();
                    textcolor(WHITE+BLINK);
                    textbackground(BLACK);
                    cprintf("Name cannot be left blank\a");
                    textcolor(BLACK);
               }
               else
                    break;
          }
          while(1)
          {
               message("Enter the address");
               gotoxy(3,6);
               cout<<"Address           :   ";
               gotoxy(25,6);
               gets(add);
               if (strlen(add) != 0)
               break;
          }

          while(1)
          {
               gotoxy(3,7);
               cout<<"Assigned Ph. No.  :   ";
               gotoxy(25,7);
               cin>>ph;
               if (ph != 0 )
                    break;
               else
               {
                    gotoxy(25,7);
                    clreol();
               }
          }
          message("Enter O for Office and R for residential phone");
          gotoxy(3,8);
          cout<<"catagory ( O/R )  :   ";
          cin>>type;
          gotoxy(4,10);
          cout<<"1 : Save & Exit    2 :  Save & Cont.   0 : Exit without save";
          gotoxy(4,11);
          cout<<"? ";
          cin>>choice;
          switch(choice)
          {
               case ('1') :      fp.write((char *) this,sizeof(cust));
                              fp.close();
                              return;
               case ('2') :     fp.write((char *) this,sizeof(cust));
                              break;
               case ('0') :   fp.close();
                              return;
               default :      fp.close();
                              return;
          }
     }
}


// FUNCTION TO DISPLAY THE CUSTOMER RECORD AND CALCULATE THE BILL
void customer :: display()
{
     char p[10];
     char choice;
     int found=0;
     int no;
     float bill=0.0, tax=0.0, fine=0.0, bbill=0.0, abill=0.0;
     fstream fp;
     fp.open("tphone.dat", ios::in);
     if (!fp)
     {
          cout<<"Unable to open a file";
          getch();
          fp.close();
          return;
     }
     while(choice != '0')
     {
          clrscr();
          gotoxy(3,20);
          cout<<"Please enter the Phone No. ";
          cin>>p;
          if (!strcmp(p,"0"))
               return;
          found = 0;
          fp.seekg(0);
          while (fp.read((char *)this ,sizeof(cust)))
          {
               if (found==1)
                    break;
               if (!strcmp(ph,p))
               {
                    clrscr();
                    gotoxy(28,2);
                    textcolor(BLACK+BLINK) ;
                    textbackground(WHITE);
                    cprintf("MAHANAGAR TELEPHONE BILL");
                    textcolor(WHITE);
                    textbackground(BLACK);
                    gotoxy(3,4);
                    cout<<"Name              :   ";
                    cout<<name;
                    gotoxy(35,5);
                    cout<<"Address           :   ";
                    cout<<add;
                    gotoxy(35,4);
                    cout<<"Assigned Ph. No.  :   ";
                    cout<<ph;
                    gotoxy(3,5);
                    cout<<"Catagory ( O/R )  :   ";
                    cout<<type;
                    gotoxy(23,8);
                    cout<<"___________";
                    gotoxy(10,8);
                    cout<<"No. of calls ";
                    cin>>no;
                    if ( no <= 150 )
                         bill = 0 ;
                    else
                    {
                         no = no - 150;
                         if (toupper(type) == 'O')
                              bill = no * 1.00 ;
                         else
                              bill = no * .80;
                    }
                    gotoxy(10,9);
                    cout<<"Bill";
                    gotoxy(70,9);
                    cout<<bill;
                    tax = (5*bill)/100;
                    gotoxy(10,10 );
                    cout<<"5% Tax";
                    gotoxy(70,10);
                    cout<<tax;
                    gotoxy(10,11);
                    cout<<"Duties";
                    gotoxy(70,11);
                    cout<<"100";
                    int dd,mm,yy;
                    struct date d;   // Getting system Date
                    getdate(&d);
                    dd = d.da_day;
                    mm = d.da_mon;
                    yy = d.da_year;
                    gotoxy(10,15)    ;
                    cout<<"TOTAL BILL before " ;
                    cout<<dd<<"/"<<mm<<"/"<<yy;
                    bbill = bill+tax+100;
                    gotoxy(70,15);
                    cout<<bbill;
                    gotoxy(10,17);
                    cout<<"Late Fine";
                    fine = (bbill*5)/100;
                    gotoxy(70,17);
                    cout<<fine;
                    gotoxy(10,21);
                    cout<<"TOTAL BILL after ";
                    cout<<dd<<"/"<<mm<<"/"<<yy;
                    abill = bbill+fine;
                    gotoxy(70,21);
                    cout<<abill;
                    found = 1;
                    message("Press a Key");
                    getch();
               }
          }
          message("Enter 1 or 2 to cont.");
          gotoxy(4,22);
          cout<<"1 :  Cont.   0 : Exit ";
          cout<<"? ";
          cin>>choice;
          switch(choice)
          {
               case ('1') :
                         break;
               case ('0') : return;
               default : return;
          }

     }
     fp.close();
}


// FUNCTION TO DISPLAY THE LIST OF THE CUSTOMERS

void customer :: list()
{
     clrscr();
     fstream fp;
     int r;
     fp.open("tphone.dat", ios::in);
     if (!fp)
     {
          cout<<"Unable to open";
          getch();
          fp.close();
          return;
     }
     gotoxy(35,2);
     cout<<"List of Customers";
     gotoxy(35,3);
     cout<<"*****************";
     gotoxy(5,4);
     cout<<"Name";
     gotoxy(40,4);
     cout<<"Phone No.";
     gotoxy(65,4);
     cout<<"Catagory";
     gotoxy(1,5);
     cout<<"*******************************************************************************";
     r=6;
     while (fp.read((char *) this, sizeof(cust)))
     {
          if (r >= 21)
          {
               message("Press a key");
               getch();
               clrscr();
               gotoxy(35,2);
               cout<<"List of customers";
               gotoxy(35,3);
               cout<<"*****************";
               gotoxy(5,4);
               cout<<"Name";
               gotoxy(40,4);
               cout<<"Phone No.";
               gotoxy(65,4);
               cout<<"Catagory";
               gotoxy(1,5);
               cout<<"*******************************************************************************";
               r=6;
          }
          gotoxy(5,r);
          cout<<name;
          gotoxy(40,r);
          cout<<ph;
          gotoxy(65,r);
          if (toupper(cust.type) == 'O')
               cout<<"Office";
          else
               cout<<"Residential";
          r++;
     }
     message("Press a key");
     getch();
     fp.close();
}


// FUNCTION TO DELETE THE RECORD OF CUSTOMER FROM THE FILE

void customer :: deleter()
{
     char ch;
     char p[10];
     fstream temp,fp;
     fp.open("tphone.dat", ios::in);
     if (!fp)
     {
          cout<<"Unable to open Telephone file";
          getch();
          fp.close();
          return;
     }
     temp.open("temp.dat", ios::out);
     if (!temp)
     {
          cout<<"Unable to open Temporary file";
          getch();
          temp.close();
          return;
     }
     clrscr();
     gotoxy(5,3);
     cout<<"Enter the Phone No. to be deleted : ";
     cin>>p;
     if(!strcmp(p,"0"))
          return;
     int found=0;
     while (fp.read((char *) this, sizeof(cust)))
     {
          if (!strcmp(p,ph))
          {
               found = 1;
               gotoxy(5,5);
               cout<<"Name       "<<name;
               gotoxy(5,6);
               cout<<"Address    " <<add;
               gotoxy(5,7);
               cout<<"Catagory   "<<type;
               gotoxy(6,10);
               cout<<"Delete this record (Y/N) ";
               cin>>ch;
               if (toupper(ch) == 'N')
                    temp.write((char *) this,sizeof(cust));
          }
          else
               temp.write((char *) this,sizeof(cust));
     }
     fp.close();
     temp.close();
     if (toupper(ch) == 'N')
          return;
     if (!found)
     {
          cout<<"\n\nTelephone no. not found";
          getch();
          return;
     }
     fp.open("tphone.dat", ios::out);
     temp.open("temp.dat", ios::in);
     while (temp.read((char *) this, sizeof(cust)))
          fp.write((char *) this, sizeof(cust));
     fp.close();
     temp.close();
}


// FUNCTION TO MODIFY THE RECORD OF CUSTOMER FROM THE FILE

void customer :: modify()
{
     char ch;
     char p[10];
     fstream temp,fp;
     fp.open("tphone.dat", ios::in);
     if (!fp)
     {
          cout<<"Unable to open Telephone file";
          getch();
          fp.close();
          return;
     }
     temp.open("temp.dat", ios::out);
     if (!temp)
     {
          cout<<"Unable to open Temporary file";
          getch();
          temp.close();
          return;
     }
     clrscr();
     gotoxy(5,3);
     cout<<"Enter the Phone No. to be Modify : ";
     cin>>p;
     if(!strcmp(ph,"0"))
          return;
     int found=0;
     while (fp.read((char *) this, sizeof(cust)))
     {
          if (!strcmp(p,ph))
          {
               found = 1;
               gotoxy(5,5);
               cout<<"Name       "<<name;
               gotoxy(5,6);
               cout<<"Address    " <<add;
               gotoxy(5,7);
               cout<<"Catagory   "<<type;
               gotoxy(6,10);
               cout<<"Modify this record (Y/N) ";
               cin>>ch;
               if (toupper(ch) == 'Y')
               {
                    gotoxy(3,13);
                    cout<<"Customer Record #";
                    message("Enter the customer record");
                    while(1)
                    {
                         gotoxy(3,15);
                         cout<<"Name              :   ";
                         gets(name);
                         if (strlen(name) != 0)
                              break;
                    }
                    gotoxy(3,16);
                    cout<<"Address           :   ";
                    gets(add);
                    while(1)
                    {
                         gotoxy(3,17);
                         cout<<"Assigned Ph. No.  :   ";
                         cin>>ph;
                         if (ph != 0 )
                              break;
                    }
                    message("Enter O for Office and R for residential phone");
                    gotoxy(3,18);
                    cout<<"catagory ( O/R )      :   ";
                    cin>>type;
               }
          }
          temp.write((char *) this,sizeof(cust));
     }
     fp.close();
     temp.close();
     if (toupper(ch) == 'N')
          return;
     if (!found)
     {
          cout<<"\n\nTelephone no. not found";
          getch();
          return;
     }
     fp.open("tphone.dat", ios::out);
     temp.open("temp.dat", ios::in);
     while (temp.read((char *) this, sizeof(cust)))
          fp.write((char *) this, sizeof(cust));
     fp.close();
     temp.close();
}


// FUNCTION TO DISPLAY THE DISCRIPTION FOR THE PROJECT WORKING

void customer :: help()
{
     clrscr();
     gotoxy(35,2);
     textcolor(WHITE + BLINK);
     textbackground(BLACK);
     cprintf(" HELP ");
     textcolor(BLACK);
     textbackground(WHITE);
     gotoxy(8,5);
     cout<<"This software is used to create a telephone bill for the customers. ";
     gotoxy(8,7);
     cout<<"There are two catagories of the customers. First catagories is  of";
     gotoxy(8,9);
     cout<<"Residential phones and second catagories is of Office phones. Both";
     gotoxy(8,11);
     cout<<"the catagories have different charges of the telephone bill. Charges";
     gotoxy(8,13);
     cout<<"of residential phones are 80 Paise per call and Charges of Office ";
     gotoxy(8,15);
     cout<<"office phones are Rs. 1 per call. 150 call are free for each catogory";
     gotoxy(8,17);
     cout<<"Total bill for is equal to 5% tax plus 100 rupees charges for  other";
     gotoxy(8,19);
     cout<<"charges. If bill is not paid before the paticular date then penalty ";
     gotoxy(8,21);
     cout<<"should also be given.";
     getch();
}