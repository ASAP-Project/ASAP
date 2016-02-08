//---------------------------------------------------------------------------

#include <vcl.h>
#include <MMSYSTEM>
#include <ShellApi>
#pragma hdrstop

#include "BeginnersUnit1.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;
String GlobalString;
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TForm1::lbAddBnClick(TObject *Sender)
{
GlobalString = EmptyStr; //Makes a string empty you could just do "" to
if(InputQuery("Enter in a string to add to the listbox","Add String",GlobalString) && (GlobalString != EmptyStr)) //if they hit okay and the string is not empty continue else you get a error
ListBox1->Items->Add(GlobalString); //adds a string to the end of the listbox
else
MessageDlg("Error your string was blank",mtError,TMsgDlgButtons()<<mbOK,0);
}
//---------------------------------------------------------------------------
void __fastcall TForm1::lbSortBnClick(TObject *Sender)
{
ListBox1->Sorted = True; //Sorts the listbox out
}
//---------------------------------------------------------------------------
void __fastcall TForm1::lbUnsortBnClick(TObject *Sender)
{
ListBox1->Sorted = False; //Makes it so the strings are not sorted
}
//---------------------------------------------------------------------------
void __fastcall TForm1::lbClearBnClick(TObject *Sender)
{
ListBox1->Clear(); //emptys the whole listbox
}
//---------------------------------------------------------------------------
void __fastcall TForm1::lbFontBnClick(TObject *Sender)
{
if(FontDialog1->Execute()) //If the dialog opens you can set the font of the listbox
ListBox1->Font = FontDialog1->Font;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::lbBackColorBnClick(TObject *Sender)
{
if(ColorDialog1->Execute()) //If the color dialog opens then set the listbox back color
ListBox1->Color = ColorDialog1->Color;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::lbSelectedBnClick(TObject *Sender)
{
if(ListBox1->ItemIndex != -1) //if a string is highlighted then continue
MessageDlg("You selected: " + ListBox1->Items->Strings[ListBox1->ItemIndex],mtInformation,TMsgDlgButtons()<<mbOK,0);
else
MessageDlg("Error you must select a string in the listbox",mtError,TMsgDlgButtons()<<mbOK,0);
}
//---------------------------------------------------------------------------
void __fastcall TForm1::lbRemoveBnClick(TObject *Sender)
{
if(ListBox1->ItemIndex != -1) //if a string is highlighted then continue
ListBox1->DeleteSelected();
else
MessageDlg("Error you must select a string in the listbox",mtError,TMsgDlgButtons()<<mbOK,0);
}
//---------------------------------------------------------------------------
void __fastcall TForm1::About1Click(TObject *Sender)
{
Beep();
MessageDlg("This program was coded by Jerome Scott II aka c_lisp",mtInformation,TMsgDlgButtons()<<mbOK,0);
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Exit1Click(TObject *Sender)
{
Application->Terminate(); //Kills the whole application
}
//---------------------------------------------------------------------------
void __fastcall TForm1::OpenCdBnClick(TObject *Sender)
{
//for this you must have <MMSYSTEM> Added in include
mciSendStringA("set cdAudio door Open",0,0,0);
}
//---------------------------------------------------------------------------
void __fastcall TForm1::CloseCdBnClick(TObject *Sender)
{
//for this you must have <MMSYSTEM> Added in include
mciSendStringA("set cdAudio door Closed",0,0,0);        
}
//---------------------------------------------------------------------------
void __fastcall TForm1::CursorPosBnClick(TObject *Sender)
{
Randomize(); //Lets you have true random positions when useing random else you will have the same random numbers everytime you load the program
SetCursorPos(random(Screen->Width),random(Screen->Height));
}
//---------------------------------------------------------------------------
void __fastcall TForm1::SwapMouseBnClick(TObject *Sender)
{
if(SwapMouseButton(1))
SwapMouseButton(0);
else
SwapMouseButton(1); 
}
//---------------------------------------------------------------------------
void __fastcall TForm1::OpenWebPageBnClick(TObject *Sender)
{
//must add #include <shellapi> to use this
ShellExecuteA(Handle,"Open","www.geocities.com/catdaddyownsme",0,0,SW_SHOWNORMAL);
}
//---------------------------------------------------------------------------
void __fastcall TForm1::OpenFileBnClick(TObject *Sender)
{
OpenDialog1->Filter = "TextFiles (*.txt)|*.txt|AllFiles (*.*)|*.*";  //Filters own joO (*.extension)|*.extension too add other file extensions
if(OpenDialog1->Execute()) //If it Opens
ShellExecuteA(Handle,"Open",OpenDialog1->FileName.c_str(),0,0,SW_NORMAL);
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Timer1Timer(TObject *Sender)
{
POINT p;//Delcares p as a point so you can have x and y axis
GetCursorPos(&p);//get mouse cusor position and put it in a the address of p
ScreenCursorPoslb->Caption = ("Cursor Position x pos: " + (String)p.x + "  y pos: " + (String)p.y); //(String) converts a integer to a string you can also do borlands way like I use in delphi IntToStr(you int here) I do (String)
Timelb->Caption = TimeToStr(Time());
}
//---------------------------------------------------------------------------
void __fastcall TForm1::WindowsDirBnClick(TObject *Sender)
{
char winDir[256] = "";
GetWindowsDirectoryA(winDir,sizeof(winDir));//size of gets the size of winDir buffer
MessageDlg("Windows Directory: " + (String)winDir,mtInformation,TMsgDlgButtons()<<mbOK,0); //once again see how I coverted array of characters to a string like I converted its done the same way as I did the integer
}
//---------------------------------------------------------------------------
void __fastcall TForm1::SystemDirBnClick(TObject *Sender)
{
char sysDir[256] = "";
GetSystemDirectoryA(sysDir,sizeof(sysDir));//size of gets the size of winDir buffer
MessageDlg("System Directory: " + (String)sysDir,mtInformation,TMsgDlgButtons()<<mbOK,0); //once again see how I coverted array of characters to a string like I converted its done the same way as I did the integer
}
//---------------------------------------------------------------------------
void __fastcall TForm1::ComputerNameBNClick(TObject *Sender)
{
DWord NameSize = (DWORD)MAX_COMPUTERNAME_LENGTH + 1; //once again I have to type cast this time im changing a integer to a dword
char compName[MAX_COMPUTERNAME_LENGTH + 1] = "";
GetComputerNameA(compName,&NameSize);
MessageDlg("Computer Name: " + (String)compName,mtInformation,TMsgDlgButtons()<<mbOK,0);
}
//---------------------------------------------------------------------------
void __fastcall TForm1::UserNameBnClick(TObject *Sender)
{
DWord UserNameSize = (DWORD)100;
char UserName[100] = "";
GetUserNameA(UserName,&UserNameSize);//size of gets the size of winDir buffer
MessageDlg("User Name: " + (String)UserName,mtInformation,TMsgDlgButtons()<<mbOK,0); //once again see how I coverted array of characters to a string like I converted its done the same way as I did the integer
}
//---------------------------------------------------------------------------
void __fastcall TForm1::TandDBnClick(TObject *Sender)
{
MessageDlg("Time: " + TimeToStr(Time()) + '\n' + "Date: " + DateToStr(Date()),mtInformation,TMsgDlgButtons()<<mbOK,0);
}
//---------------------------------------------------------------------------
void __fastcall TForm1::MessageBoxBnClick(TObject *Sender)
{
if(Application->MessageBox("Hello c_lisp", "Mwahwha", MB_YESNO) == IDYES)
ShowMessage("You Choosed Yes");
else
ShowMessage("you Choosed No");
}
//---------------------------------------------------------------------------
void __fastcall TForm1::DeleteFileBnClick(TObject *Sender)
{
//I would orginal make my own delete file dialog to look more professional this is just a example
OpenDialog1->Filter = "AllFiles (*.*)|*.*";
if(OpenDialog1->Execute())
if(DeleteFileA(OpenDialog1->FileName) == 1) //This api returns bool so 1 if it word 0 if it fails
MessageDlg(OpenDialog1->FileName + " Was Successfully Delete",mtConfirmation,TMsgDlgButtons()<<mbOK,0);
else
MessageDlg("Could not deleted file :(",mtError,TMsgDlgButtons()<<mbOK,0);
}
//---------------------------------------------------------------------------
void __fastcall TForm1::CreateFolderBnClick(TObject *Sender)
{
//ExtractFileDir is a api call to get the directory of where the file is you also have ExtractFileName ExtractFileDrive ExtractFileExt they pretty much explain easy to understand
//Application->ExeName gets the path and the file name of your application
GlobalString = ExtractFileDir(Application->ExeName) + "\\JoO";
if(InputQuery("Enter in the path and folder name you want to create","Create Folder",GlobalString) && (GlobalString != EmptyStr))
if(CreateDir(GlobalString) == 1)
MessageDlg(GlobalString + " Was Successfully Created",mtConfirmation,TMsgDlgButtons()<<mbOK,0);
else
MessageDlg("Could not create file :(",mtError,TMsgDlgButtons()<<mbOK,0);
}
//---------------------------------------------------------------------------
void __fastcall TForm1::ResultBnClick(TObject *Sender)
{
if(RadioButton1->Checked)
ShowMessage("Option1 is selected");
else if(RadioButton2->Checked)
ShowMessage("Option2 is selected");
else if(RadioButton3->Checked)
ShowMessage("Option3 is selected");
else
ShowMessage("No Option is selected");
if((CheckBox1->Checked) && (CheckBox2->Checked) && (CheckBox3->Checked))
ShowMessage("All three check boxes or Checked");
else if((CheckBox1->Checked) && (CheckBox2->Checked))
ShowMessage("Check1 and Check2 is Checked");
else if((CheckBox1->Checked) && (CheckBox3->Checked))
ShowMessage("Check1 and Check3 is Checked");
else if((CheckBox2->Checked) && (CheckBox3->Checked))
ShowMessage("Check2 and Check3 is Checked");
else if(CheckBox1->Checked)
ShowMessage("Check1 is Checked");
else if(CheckBox2->Checked)
ShowMessage("Check2 is Checked");
else if(CheckBox3->Checked)
ShowMessage("Check3 is Checked");
else
ShowMessage("No CheckBoxes are checked");
}
//---------------------------------------------------------------------------
void __fastcall TForm1::ForLoopBnClick(TObject *Sender)
{
//You use { } if you have more then 1 line in a forloop if statement so on if not it only loops the first line of code under it
for(int i = 1;i<=10;i++)
ShowMessage("I own JoO #" + (String)i);
ShowMessage("For loop is done!");
}
//---------------------------------------------------------------------------
void __fastcall TForm1::WhileLoopBnClick(TObject *Sender)
{
int i = 0;
while(i != 10)
{
i++;
ShowMessage("I Own JoO #" + (String)i);
}
}
//---------------------------------------------------------------------------
void __fastcall TForm1::DoWhileBnClick(TObject *Sender)
{
//The difference between do whiles and while loops do whiles will always run atleast once
int i = 0;
do
{
i++;
ShowMessage("I own JoO #" + (String)i);
}while(i!=10);
}
//---------------------------------------------------------------------------
void __fastcall TForm1::CaseBnClick(TObject *Sender)
{
int i = 0;
GlobalString = EmptyStr;
if(InputQuery("How old are you","Age",GlobalString) && (GlobalString != EmptyStr))
i = StrToInt(GlobalString);
//case statemeants if you don't have a break it keeps doing all the code it sees until it hits a break so say I had case 1: case 2: case 3: if the break is on case 3 and they choose one it will run the code off case 3
switch(i)
{
case 0 :
ShowMessage("Your Still your mom and already coding?");
break;
case 1 :
case 2 :
case 3 :
case 4 :
case 5 :
case 6 :
case 7 :
case 8 :
case 9 :
ShowMessage("Your a young buck keep coding!");
break;
case 10 :
case 11 :
case 12 :
ShowMessage("Your almost a teen!");
break;
case 13 :
case 14 :
case 15 :
case 16 :
case 17 :
ShowMessage("You are a teen");
break;
case 18 :
case 19 :
case 20 :
ShowMessage("Your a young adult now you can smoke!");
break;
default : //anything thats not in the case will go to the default
ShowMessage("Your old enough to do anything you want!");
}
}
//---------------------------------------------------------------------------
void __fastcall TForm1::HideStartBnClick(TObject *Sender)
{
//ShowWindow shows a window hidden normal maximized etc
//FindWindowEx I use this to find handles from within a window
//FindWindow I use this to find the handle of a window by class name or window name
//You can use WinSight32 to get windows class names etc
ShowWindow(FindWindowEx(FindWindow("shell_traywnd",NULL),0,"Button",NULL),0);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::ShowStartBnClick(TObject *Sender)
{
//ShowWindow shows a window hidden normal maximized etc
//FindWindowEx I use this to find handles from within a window
//FindWindow I use this to find the handle of a window by class name or window name
//You can use WinSight32 to get windows class names etc
ShowWindow(FindWindowEx(FindWindow("shell_traywnd",NULL),0,"Button",NULL),1);
}
//---------------------------------------------------------------------------
void __fastcall TForm1::HideTaskbarBnClick(TObject *Sender)
{
//ShowWindow shows a window hidden normal maximized etc
//FindWindowEx I use this to find handles from within a window
//FindWindow I use this to find the handle of a window by class name or window name
//You can use WinSight32 to get windows class names etc
ShowWindow(FindWindow("shell_traywnd",NULL),0);
}
//---------------------------------------------------------------------------
void __fastcall TForm1::ShowTaskbarBnClick(TObject *Sender)
{
//ShowWindow shows a window hidden normal maximized etc
//FindWindowEx I use this to find handles from within a window
//FindWindow I use this to find the handle of a window by class name or window name
//You can use WinSight32 to get windows class names etc
ShowWindow(FindWindow("shell_traywnd",NULL),1);
}
//---------------------------------------------------------------------------
void __fastcall TForm1::ReverseEditKeyPress(TObject *Sender, char &Key)
{
//It Explains itself :p
ReverseEdit->SelStart = ReverseEdit->SelStart - 1;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::ClearEditBnClick(TObject *Sender)
{
//It Explains itself :p
ReverseEdit->Text = EmptyStr;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::UppercaseBnClick(TObject *Sender)
{
//It Explains itself :p
ReverseEdit->Text = ReverseEdit->Text.UpperCase();
}
//---------------------------------------------------------------------------
void __fastcall TForm1::LowerCaseBnClick(TObject *Sender)
{
//It Explains itself :p
ReverseEdit->Text = ReverseEdit->Text.LowerCase();
}
//---------------------------------------------------------------------------
