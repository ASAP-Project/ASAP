// Employees Management System 1.0
// Created By: Mr. Jake Rodriguez Pomperada, MAED-Instructional Technology
// Email Address : jakerpomperada@yahoo.com
// Date : November 1, 2009
// Tool : Turbo C++ 3.0
// Mobile Number : 09296768375
// Telephone Number : +63 (034) 4335081


#include<iostream.h>
#include<string.h>
#include<iomanip.h>
#include<dos.h>
#include<conio.h>
#include<stdio.h>
#define max 20
struct employee
{
 char name[20];
 long int code;
 char designation[20];
 int exp;
 int age;
};
int num;
employee emp[max],tempemp[max],sortemp[max],sortemp1[max];
void main()
{
 clrscr();
 void build();
 void list();
 void insert();
 void deletes();
 void edit();
 void search();
 void sort();
 char option;
 void menu();
 menu();
 while((option=cin.get())!='q')
 {
  switch(option)
  {
   case 'b':
		     build();
		     break;
   case 'l':
		     list();
		     break;
   case 'i':
		     insert();
		     break;
   case 'd':
		     deletes();
		     break;
   case 'e':
		   edit();
		    break;
   case 's':
		    search();
		    break;
   case 'n':
		     sort();
		     break;
  }
   menu();
  }
 }
 void menu()
 {
  clrscr();
  highvideo();
cout<<"		      ";
cprintf("\n*****  Employees Management System 1.0 ***** ");
printf("\n\n\t               Created By: Mr. Jake R. Pomperada, MAED-IT");

normvideo();
cout<<endl;
cout<<"		         ";
cout<<"\n\t\t Press  b---->Built The Employee Table ";
cout<<"		         ";
cout<<"\n\t\t Press  l---->List The Employee Table  ";
cout<<"		         ";
cout<<"\n\t\t Press  i---->Insert New Entry        ";
cout<<"		         ";
cout<<"\n\t\t Press  d---->Delete An Entry         ";
cout<<"		         ";
cout<<"\n\t\t Press  e---->Edit An Entry           ";
cout<<"		         ";
cout<<"\n\t\t Press  s---->Search Arecord          ";
cout<<"		         ";
cout<<"\n\t\t Press  n---->Sort The Table          ";
cout<<"		         ";
cout<<"\n\t\t Press  q---------->Quit Program              ";
cout<<"		         ";
cout<<"\n\n \t\t Select Your Option Please ====> ";
}

void build()
{

 clrscr();
 highvideo();
 cprintf("Build The Table");
 cout<<endl;
 normvideo();
 cout<<"maximum number of entries  -----  >  20"<<endl;
 cout<<"how many do you want    ----->";
 cin>>num;
 cout<<"Enter The Following Items";
 for(int i=0;i<=num-1;i++)
 {
  cout<<" Name	";
  cin>>emp[i].name;
  cout<<"Code	";
  cin>>emp[i].code;
  cout<<"Designation	";
  cin>>emp[i].designation;
  cout<<"Years of Experience	";
  cin>>emp[i].exp;
  cout<<"Age	";
  cin>>emp[i].age;
 }
  cout<<"going to main menu";
  delay(500);
}

void  list()
{
 clrscr();
 highvideo();
 cprintf("       ********List The Table********");
 cout<<endl;
 normvideo();
 cout<<"     Name		 Code		 Designation		 Years(EXP)		 Age ";
 cout<<"    ------------------------------------------------------";
 for(int i=0;i<=num-1;i++)
 {
  cout<<setw(13)<<emp[i].name;
  cout<<setw(6)<<emp[i].code;
  cout<<setw(15)<<emp[i].designation;
  cout<<setw(10)<<emp[i].exp;
  cout<<setw(15)<<emp[i].age;
  cout<<endl;
 }
  cout<<"going to main menu";
 getch();
  }
  void insert()
  {
  clrscr();
  int i=num;
  num+=1;
  highvideo();
  cprintf("Insert New Record");
  cout<<endl;
  normvideo();
  cout<<"Enter The Following Items";
  cout<<"Name	";
  cin>>emp[i].name;
  cout<<"Code	";
  cin>>emp[i].code;
  cout<<"Designation	";
  cin>>emp[i].designation;
  cout<<"Years of Experience	";
  cin>>emp[i].exp;
  cout<<"Age	";
  cin>>emp[i].age;
  cout<<endl<<endl;
  cout<<"going to main menu";
  delay(500);

  }


  void deletes()
  {
   clrscr();
   highvideo();
   int code;
   int check;
   cprintf("Delete An Entry");
   normvideo();
   cout<<endl;
   cout<<"Enter An JobCode To Delete That Entry	";
   cin>>code;
   int i;
   for(i=0;i<=num-1;i++)
   {
    if(emp[i].code==code)
    {
      check=i;
    }
   }
   for(i=0;i<=num-1;i++)
   {
    if(i==check)
    {
    continue;
    }
    else
    {
    if(i>check)
    {
     tempemp[i-1]=emp[i];
    }
    else
    {
     tempemp[i]=emp[i];
    }
     }
   }
  num--;

  for(i=0;i<=num-1;i++)
  {
   emp[i]=tempemp[i];
  }
 }

void edit()
{
 clrscr();
 int jobcode;
 highvideo();
 cprintf("          Edit An Entry           ");
 cout<<endl;
 cout<<endl;
 int i;
 void editmenu();
 void editname(int);
 void editcode(int);
 void editdes(int);
 void editexp(int);
 void editage(int);
 char option;
 normvideo();
 cout<<"Enter An jobcode To Edit An Entry----	";
 cin>>jobcode;
  editmenu();
 for(i=0;i<=num-1;i++)
   {
    if(emp[i].code==jobcode)
    {

while((option=cin.get())!='q')
{
      switch(option)
      {
       case 'n':
		 		   editname(i);
		 		   break;
       case 'c':
		 		   editcode(i);
		 		   break;
       case 'd':
		 		   editdes(i);
		 		   break;
       case 'e':
		 		   editexp(i);
		 		   break;
       case 'a':
		 		  editage(i);
		 		  break;
     }
   editmenu();
    }
  }
  }
  }
  void editmenu()
  {
   clrscr();
   cout<<"	 		 What Do You Want To edit";
   cout<<"		 		 n--------->Name ";
   cout<<"		 		 c--------->Code ";
   cout<<"		 		 d--------->Designation";
   cout<<"		 		 e--------->Experience ";
   cout<<"		 		 a--------->Age        ";
   cout<<"              q----->QUIT                            ";
   cout<<"   Options Please ---->>>	";
  }
  void editname(int i)
  {
     cout<<"Enter New Name----->	";
     cin>>emp[i].name;
  }
  void editcode(int i)
  {
   cout<<"Enter New Job Code----->	";
   cin>>emp[i].code;
  }
  void editdes(int i)
  {
   cout<<"enter new designation----->	";
   cin>>emp[i].designation;
  }
  void editexp(int i)
  {
   cout<<"Enter new Years of Experience";
   cin>>emp[i].exp;
  }
  void editage(int i)
  {
   cout<<"Enter new Age ";
   cin>>emp[i].age;
  }

void search()
{
 clrscr();
  highvideo();
  cprintf("Welcome To Search Of Employee Database ");
  normvideo();
  cout<<endl;
  cout<<endl;
  int jobcode;
  cout<<"You Can Search Only By Jobcode Of An Employee";
  cout<<"Enter Code Of An Employee                    ";
 cin>>jobcode;
 for(int i=0;i<=num-1;i++)
   {
    if(emp[i].code==jobcode)
    {

    cout<<"     Name		 Code		 Designation		 Years(EXP)		 Age ";
 cout<<"     ------------------------------------------------------                                  ";
  cout<<setw(13)<<emp[i].name;
  cout<<setw(6)<<emp[i].code;
  cout<<setw(15)<<emp[i].designation;
  cout<<setw(10)<<emp[i].exp;
  cout<<setw(15)<<emp[i].age;
  cout<<endl;
 }

  }
    cout<<"going to main menu";
 getch();


}

void sort()
{
 clrscr();
 highvideo();
 cprintf("Sort The Databse By JobCode");
 normvideo();
 void sortmenu();
 void sortname();
 void sortcode();
 void sortdes();
 void sortexp();
 char option;
 void sortage();

 cout<<endl;
 cout<<endl;
 sortmenu();
 while((option=cin.get())!='q')
 {
  switch(option)
  {
   case 'n':
		 		 sortname();
		 		 break;
   case 'c':
		 		 sortcode();
		 		 break;
   case 'd':
		 		 sortdes();
		 		 break;
   case 'e':
		 		 sortexp();
		 		 break;
   case 'a':
		 		 sortage();
		 		 break;
   }
   sortmenu();
  }
 }


 void sortmenu()
 {
    clrscr();
   cout<<"		 		 What Do You Want To edit";
   cout<<"		 		 n--------->Name         ";
   cout<<"		 		 c--------->Code         ";
   cout<<"		 		 d--------->Designation  ";
   cout<<"		 		 e--------->Experience   ";
   cout<<"		 		 a--------->Age          ";
   cout<<"                               q----->QUIT            ";
   cout<<"   Options Please ---->>>	";  }



void sortname()
{
 clrscr();
 int i,j;
 struct employee temp[max];
 for(i=0;i<=num-1;i++)
 {
  sortemp1[i]=emp[i];
 }
 for(i=0;i<=num-1;i++)
  {
   for(j=0;j<=num-1;j++)
   {
    if(strcmp(sortemp1[i].name,sortemp1[j].name)<=0)
    {
     temp[i]=sortemp1[i];
     sortemp1[i]=sortemp1[j];
     sortemp1[j]=temp[i];
    }
   }
 }

 for( i=0;i<=num-1;i++)
   {

    cout<<"     Name		 Code		 Designation		 Years(EXP)		 Age ";
 cout<<"     ------------------------------------------------------                                  ";
 for( i=0;i<=num-1;i++)
 {
  cout<<setw(13)<<sortemp1[i].name;
  cout<<setw(6)<<sortemp1[i].code;
  cout<<setw(15)<<sortemp1[i].designation;
  cout<<setw(10)<<sortemp1[i].exp;
  cout<<setw(15)<<sortemp1[i].age;
  cout<<endl;
 }
  cout<<"Press Any Key To Go Back";
 getch();

} }

void sortcode()
{
 clrscr();
 int i,j;
 struct employee temp[max];
 for(i=0;i<=num-1;i++)
 {
  sortemp1[i]=emp[i];
 }
 for(i=0;i<=num-1;i++)
  {
   for(j=0;j<=num-1;j++)
   {
    if(sortemp1[i].code<sortemp1[j].code)
    {
     temp[i]=sortemp1[i];
     sortemp1[i]=sortemp1[j];
     sortemp1[j]=temp[i];
    }
   }
 }

 for( i=0;i<=num-1;i++)
   {

    cout<<"     Name		 Code		 Designation		 Years(EXP)		 Age ";
 cout<<"     ------------------------------------------------------                                  ";
 for( i=0;i<=num-1;i++)
 {
  cout<<setw(13)<<sortemp1[i].name;
  cout<<setw(6)<<sortemp1[i].code;
  cout<<setw(15)<<sortemp1[i].designation;
  cout<<setw(10)<<sortemp1[i].exp;
  cout<<setw(15)<<sortemp1[i].age;
  cout<<endl;
 }
  cout<<"Press Any Key To Go Back";
 getch();

} }


void sortdes()
{
 clrscr();
 int i,j;
 struct employee temp[max];
 for(i=0;i<=num-1;i++)
 {
  sortemp1[i]=emp[i];
 }
 for(i=0;i<=num-1;i++)
  {
   for(j=0;j<=num-1;j++)
   {
    if(strcmp(sortemp1[i].designation,sortemp1[j].designation)<=0)
    {
     temp[i]=sortemp1[i];
     sortemp1[i]=sortemp1[j];
     sortemp1[j]=temp[i];
    }
   }
 }

 for( i=0;i<=num-1;i++)
   {

    cout<<"     Name		 Code		 Designation		 Years(EXP)		 Age";
 cout<<"     ------------------------------------------------------                                 ";
 for( i=0;i<=num-1;i++)
 {
  cout<<setw(13)<<sortemp1[i].name;
  cout<<setw(6)<<sortemp1[i].code;
  cout<<setw(15)<<sortemp1[i].designation;
  cout<<setw(10)<<sortemp1[i].exp;
  cout<<setw(15)<<sortemp1[i].age;
  cout<<endl;
 }
  cout<<"Press Any Key To Go Back";
 getch();

} }

void sortage()
{
 clrscr();
 int i,j;
 struct employee temp[max];
 for(i=0;i<=num-1;i++)
 {
  sortemp1[i]=emp[i];
 }
 for(i=0;i<=num-1;i++)
  {
   for(j=0;j<=num-1;j++)
   {
    if(sortemp1[i].age<sortemp1[j].age)
    {
     temp[i]=sortemp1[i];
     sortemp1[i]=sortemp1[j];
     sortemp1[j]=temp[i];
    }
   }
 }

 for( i=0;i<=num-1;i++)
   {

    cout<<"     Name		 Code		 Designation		 Years(EXP)		 Age";
 cout<<"     ------------------------------------------------------                                 ";
 for( i=0;i<=num-1;i++)
 {
  cout<<setw(13)<<sortemp1[i].name;
  cout<<setw(6)<<sortemp1[i].code;
  cout<<setw(15)<<sortemp1[i].designation;
  cout<<setw(10)<<sortemp1[i].exp;
  cout<<setw(15)<<sortemp1[i].age;
  cout<<endl;
 }
  cout<<"Press Any Key To Go Back";
 getch();

} }


void sortexp()
{
 clrscr();
 int i,j;
 struct employee temp[max];
 for(i=0;i<=num-1;i++)
 {
  sortemp1[i]=emp[i];
 }
 for(i=0;i<=num-1;i++)
  {
   for(j=0;j<=num-1;j++)
   {
    if(sortemp1[i].exp<sortemp1[j].exp)
    {
     temp[i]=sortemp1[i];
     sortemp1[i]=sortemp1[j];
     sortemp1[j]=temp[i];
    }
   }
 }

 for( i=0;i<=num-1;i++)
   {

    cout<<"     Name		 Code		 Designation		 Years(EXP)		 Age ";           
 cout<<"  ------------------------------------------------------ "; 
 for( i=0;i<=num-1;i++)
 {
  cout<<setw(13)<<sortemp1[i].name;
  cout<<setw(6)<<sortemp1[i].code;
  cout<<setw(15)<<sortemp1[i].designation;
  cout<<setw(10)<<sortemp1[i].exp;
  cout<<setw(15)<<sortemp1[i].age;
  cout<<endl;
 }
  cout<<"Press Any Key To Go Back";
 getch();

} }