//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#include "Connect4Unit1.h"
#include "netplayUnit.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;

bool switcher, wait = false;
bool pTurn = false;
int gSlot[10][11];  //extras slots for my search method :p
int PlayersTurn()
{
  if(pTurn == false){
      pTurn = true;
      return 1;
  }
  else{
      pTurn = false;
      return 5;
  }
}

void Column1()
{
  if( gSlot[0][0] == 0 ){
     gSlot[0][0] = PlayersTurn();
     if( gSlot[0][0] == 1 )
        Form1->s1->Brush->Color = clBlack;
     else
        Form1->s1->Brush->Color = clRed;
  }
  else if( gSlot[1][0] == 0 ){
     gSlot[1][0] = PlayersTurn();
     if(gSlot[1][0] == 1)
        Form1->s8->Brush->Color = clBlack;
     else
        Form1->s8->Brush->Color = clRed;
  }
  else if( gSlot[2][0] == 0 ){
     gSlot[2][0] = PlayersTurn();
     if(gSlot[2][0] == 1)
        Form1->s15->Brush->Color = clBlack;
     else
        Form1->s15->Brush->Color = clRed;
  }
  else if( gSlot[3][0] == 0 ){
     gSlot[3][0] = PlayersTurn();
     if(gSlot[3][0] == 1)
        Form1->s22->Brush->Color = clBlack;
     else
        Form1->s22->Brush->Color = clRed;
  }
  else if( gSlot[4][0] == 0 ){
     gSlot[4][0] = PlayersTurn();
     if(gSlot[4][0] == 1)
        Form1->s29->Brush->Color = clBlack;
     else
        Form1->s29->Brush->Color = clRed;
  }
  else if( gSlot[5][0] == 0 ){
     gSlot[5][0] = PlayersTurn();
     if(gSlot[5][0] == 1)
        Form1->s36->Brush->Color = clBlack;
     else
        Form1->s36->Brush->Color = clRed;
  }
  else
     MessageDlg("This column is full!",mtInformation,TMsgDlgButtons()<<mbOK,0);
}

void Column2()
{
  if( gSlot[0][1] == 0 ){
     gSlot[0][1] = PlayersTurn();
     if( gSlot[0][1] == 1 )
        Form1->s2->Brush->Color = clBlack;
     else
        Form1->s2->Brush->Color = clRed;
  }
  else if( gSlot[1][1] == 0 ){
     gSlot[1][1] = PlayersTurn();
     if(gSlot[1][1] == 1)
        Form1->s9->Brush->Color = clBlack;
     else
        Form1->s9->Brush->Color = clRed;
  }
  else if( gSlot[2][1] == 0 ){
     gSlot[2][1] = PlayersTurn();
     if(gSlot[2][1] == 1)
        Form1->s16->Brush->Color = clBlack;
     else
        Form1->s16->Brush->Color = clRed;
  }
  else if( gSlot[3][1] == 0 ){
     gSlot[3][1] = PlayersTurn();
     if(gSlot[3][1] == 1)
        Form1->s23->Brush->Color = clBlack;
     else
        Form1->s23->Brush->Color = clRed;
  }
  else if( gSlot[4][1] == 0 ){
     gSlot[4][1] = PlayersTurn();
     if(gSlot[4][1] == 1)
        Form1->s30->Brush->Color = clBlack;
     else
        Form1->s30->Brush->Color = clRed;
  }
  else if( gSlot[5][1] == 0 ){
     gSlot[5][1] = PlayersTurn();
     if(gSlot[5][1] == 1)
        Form1->s37->Brush->Color = clBlack;
     else
        Form1->s37->Brush->Color = clRed;
  }
  else
     MessageDlg("This column is full!",mtInformation,TMsgDlgButtons()<<mbOK,0);
}

void Column3()
{
  if( gSlot[0][2] == 0 ){
    gSlot[0][2] = PlayersTurn();
    if( gSlot[0][2] == 1 )
       Form1->s3->Brush->Color = clBlack;
    else
       Form1->s3->Brush->Color = clRed;
  }
  else if( gSlot[1][2] == 0 ){
     gSlot[1][2] = PlayersTurn();
     if(gSlot[1][2] == 1)
        Form1->s10->Brush->Color = clBlack;
     else
        Form1->s10->Brush->Color = clRed;
  }
  else if( gSlot[2][2] == 0 ){
     gSlot[2][2] = PlayersTurn();
     if(gSlot[2][2] == 1)
        Form1->s17->Brush->Color = clBlack;
     else
        Form1->s17->Brush->Color = clRed;
  }
  else if( gSlot[3][2] == 0 ){
     gSlot[3][2] = PlayersTurn();
     if(gSlot[3][2] == 1)
        Form1->s24->Brush->Color = clBlack;
     else
        Form1->s24->Brush->Color = clRed;
  }
  else if( gSlot[4][2] == 0 ){
     gSlot[4][2] = PlayersTurn();
     if(gSlot[4][2] == 1)
        Form1->s31->Brush->Color = clBlack;
     else
        Form1->s31->Brush->Color = clRed;
  }
  else if( gSlot[5][2] == 0 ){
     gSlot[5][2] = PlayersTurn();
     if(gSlot[5][2] == 1)
        Form1->s38->Brush->Color = clBlack;
     else
        Form1->s38->Brush->Color = clRed;
  }
  else
     MessageDlg("This column is full!",mtInformation,TMsgDlgButtons()<<mbOK,0);
}

void Column4()
{
  if( gSlot[0][3] == 0 ){
    gSlot[0][3] = PlayersTurn();
    if( gSlot[0][3] == 1 )
       Form1->s4->Brush->Color = clBlack;
    else
       Form1->s4->Brush->Color = clRed;
  }
  else if( gSlot[1][3] == 0 ){
     gSlot[1][3] = PlayersTurn();
     if(gSlot[1][3] == 1)
        Form1->s11->Brush->Color = clBlack;
     else
        Form1->s11->Brush->Color = clRed;
  }
  else if( gSlot[2][3] == 0 ){
     gSlot[2][3] = PlayersTurn();
     if(gSlot[2][3] == 1)
        Form1->s18->Brush->Color = clBlack;
     else
        Form1->s18->Brush->Color = clRed;
  }
  else if( gSlot[3][3] == 0 ){
     gSlot[3][3] = PlayersTurn();
     if(gSlot[3][3] == 1)
        Form1->s25->Brush->Color = clBlack;
     else
        Form1->s25->Brush->Color = clRed;
  }
  else if( gSlot[4][3] == 0 ){
     gSlot[4][3] = PlayersTurn();
     if(gSlot[4][3] == 1)
        Form1->s32->Brush->Color = clBlack;
     else
        Form1->s32->Brush->Color = clRed;
  }
  else if( gSlot[5][3] == 0 ){
     gSlot[5][3] = PlayersTurn();
     if(gSlot[5][3] == 1)
        Form1->s39->Brush->Color = clBlack;
     else
        Form1->s39->Brush->Color = clRed;
  }
  else
     MessageDlg("This column is full!",mtInformation,TMsgDlgButtons()<<mbOK,0);
}

void Column5()
{
  if( gSlot[0][4] == 0 ){
    gSlot[0][4] = PlayersTurn();
    if( gSlot[0][4] == 1 )
       Form1->s5->Brush->Color = clBlack;
    else
       Form1->s5->Brush->Color = clRed;
  }
  else if( gSlot[1][4] == 0 ){
     gSlot[1][4] = PlayersTurn();
     if(gSlot[1][4] == 1)
        Form1->s12->Brush->Color = clBlack;
     else
        Form1->s12->Brush->Color = clRed;
  }
  else if( gSlot[2][4] == 0 ){
     gSlot[2][4] = PlayersTurn();
     if(gSlot[2][4] == 1)
        Form1->s19->Brush->Color = clBlack;
     else
        Form1->s19->Brush->Color = clRed;
  }
  else if( gSlot[3][4] == 0 ){
     gSlot[3][4] = PlayersTurn();
     if(gSlot[3][4] == 1)
        Form1->s26->Brush->Color = clBlack;
     else
        Form1->s26->Brush->Color = clRed;
  }
  else if( gSlot[4][4] == 0 ){
     gSlot[4][4] = PlayersTurn();
     if(gSlot[4][4] == 1)
        Form1->s33->Brush->Color = clBlack;
     else
        Form1->s33->Brush->Color = clRed;
  }
  else if( gSlot[5][4] == 0 ){
     gSlot[5][4] = PlayersTurn();
     if(gSlot[5][4] == 1)
        Form1->s40->Brush->Color = clBlack;
     else
        Form1->s40->Brush->Color = clRed;
  }
  else
     MessageDlg("This column is full!",mtInformation,TMsgDlgButtons()<<mbOK,0);
}

void Column6()
{
  if( gSlot[0][5] == 0 ){
    gSlot[0][5] = PlayersTurn();
    if( gSlot[0][5] == 1 )
       Form1->s6->Brush->Color = clBlack;
    else
       Form1->s6->Brush->Color = clRed;
  }
  else if( gSlot[1][5] == 0 ){
     gSlot[1][5] = PlayersTurn();
     if(gSlot[1][5] == 1)
        Form1->s13->Brush->Color = clBlack;
     else
        Form1->s13->Brush->Color = clRed;
  }
  else if( gSlot[2][5] == 0 ){
     gSlot[2][5] = PlayersTurn();
     if(gSlot[2][5] == 1)
        Form1->s20->Brush->Color = clBlack;
     else
        Form1->s20->Brush->Color = clRed;
  }
  else if( gSlot[3][5] == 0 ){
     gSlot[3][5] = PlayersTurn();
     if(gSlot[3][5] == 1)
        Form1->s27->Brush->Color = clBlack;
     else
        Form1->s27->Brush->Color = clRed;
  }
  else if( gSlot[4][5] == 0 ){
     gSlot[4][5] = PlayersTurn();
     if(gSlot[4][5] == 1)
        Form1->s34->Brush->Color = clBlack;
     else
        Form1->s34->Brush->Color = clRed;
  }
  else if( gSlot[5][5] == 0 ){
     gSlot[5][5] = PlayersTurn();
     if(gSlot[5][5] == 1)
        Form1->s41->Brush->Color = clBlack;
     else
        Form1->s41->Brush->Color = clRed;
  }
  else
     MessageDlg("This column is full!",mtInformation,TMsgDlgButtons()<<mbOK,0);
}

void Column7()
{
  if( gSlot[0][6] == 0 ){
    gSlot[0][6] = PlayersTurn();
    if( gSlot[0][6] == 1 )
       Form1->s7->Brush->Color = clBlack;
    else
       Form1->s7->Brush->Color = clRed;
  }
  else if( gSlot[1][6] == 0 ){
     gSlot[1][6] = PlayersTurn();
     if(gSlot[1][6] == 1)
        Form1->s14->Brush->Color = clBlack;
     else
        Form1->s14->Brush->Color = clRed;
  }
  else if( gSlot[2][6] == 0 ){
     gSlot[2][6] = PlayersTurn();
     if(gSlot[2][6] == 1)
        Form1->s21->Brush->Color = clBlack;
     else
        Form1->s21->Brush->Color = clRed;
  }
  else if( gSlot[3][6] == 0 ){
     gSlot[3][6] = PlayersTurn();
     if(gSlot[3][6] == 1)
        Form1->s28->Brush->Color = clBlack;
     else
        Form1->s28->Brush->Color = clRed;
  }
  else if( gSlot[4][6] == 0 ){
     gSlot[4][6] = PlayersTurn();
     if(gSlot[4][6] == 1)
        Form1->s35->Brush->Color = clBlack;
     else
        Form1->s35->Brush->Color = clRed;
  }
  else if( gSlot[5][6] == 0 ){
     gSlot[5][6] = PlayersTurn();
     if(gSlot[5][6] == 1)
        Form1->s42->Brush->Color = clBlack;
     else
        Form1->s42->Brush->Color = clRed;
  }
  else
     MessageDlg("This column is full!",mtInformation,TMsgDlgButtons()<<mbOK,0);
}




void ArrayIntilize()
{
  for(int row = 0; row < 9; row++)
     for(int column = 0; column < 10; column++)
        gSlot[row][column] = 0;
}

void clear()
{
Form1->s1->Brush->Color = clSilver;
Form1->s2->Brush->Color = clSilver;
Form1->s3->Brush->Color = clSilver;
Form1->s4->Brush->Color = clSilver;
Form1->s5->Brush->Color = clSilver;
Form1->s6->Brush->Color = clSilver;
Form1->s7->Brush->Color = clSilver;
Form1->s8->Brush->Color = clSilver;
Form1->s9->Brush->Color = clSilver;
Form1->s10->Brush->Color = clSilver;
Form1->s11->Brush->Color = clSilver;
Form1->s12->Brush->Color = clSilver;
Form1->s13->Brush->Color = clSilver;
Form1->s14->Brush->Color = clSilver;
Form1->s15->Brush->Color = clSilver;
Form1->s16->Brush->Color = clSilver;
Form1->s17->Brush->Color = clSilver;
Form1->s18->Brush->Color = clSilver;
Form1->s19->Brush->Color = clSilver;
Form1->s20->Brush->Color = clSilver;
Form1->s21->Brush->Color = clSilver;
Form1->s22->Brush->Color = clSilver;
Form1->s23->Brush->Color = clSilver;
Form1->s24->Brush->Color = clSilver;
Form1->s25->Brush->Color = clSilver;
Form1->s26->Brush->Color = clSilver;
Form1->s27->Brush->Color = clSilver;
Form1->s28->Brush->Color = clSilver;
Form1->s29->Brush->Color = clSilver;
Form1->s30->Brush->Color = clSilver;
Form1->s31->Brush->Color = clSilver;
Form1->s32->Brush->Color = clSilver;
Form1->s33->Brush->Color = clSilver;
Form1->s34->Brush->Color = clSilver;
Form1->s35->Brush->Color = clSilver;
Form1->s36->Brush->Color = clSilver;
Form1->s37->Brush->Color = clSilver;
Form1->s38->Brush->Color = clSilver;
Form1->s39->Brush->Color = clSilver;
Form1->s40->Brush->Color = clSilver;
Form1->s41->Brush->Color = clSilver;
Form1->s42->Brush->Color = clSilver;
ArrayIntilize();
}

void bWin()
{

Beep();
wait = true;
MessageDlg("black wins",mtInformation,TMsgDlgButtons()<<mbOK,0);
if(Form1->ClientSocket1->Active)
   Form1->ClientSocket1->Socket->SendText("ready");
else
   Form1->ServerSocket1->Socket->Connections[0]->SendText("ready");
PlayersTurn();
clear();
}

void rWin()
{
Beep();
wait = true;
MessageDlg("red wins",mtInformation,TMsgDlgButtons()<<mbOK,0);
if(Form1->ClientSocket1->Active)
   Form1->ClientSocket1->Socket->SendText("ready");
else
   Form1->ServerSocket1->Socket->Connections[0]->SendText("ready");
PlayersTurn();
clear();
}

void tie()
{
Beep();
wait = true;
MessageDlg("tie game!",mtInformation,TMsgDlgButtons()<<mbOK,0);
if(Form1->ClientSocket1->Active)
   Form1->ClientSocket1->Socket->SendText("ready");
else
   Form1->ServerSocket1->Socket->Connections[0]->SendText("ready");
clear();
}

void winner()
{
  int isTie = 0;
  for(int y = 0; y < 9; y++)
  for(int x = 0; x < 10; x++){
     if(gSlot[x][y] != 0){
        isTie += gSlot[x][y];
        if(gSlot[x][y] + gSlot[x + 1][y] + gSlot[x + 2][y] + gSlot[x + 3][y] == 4) bWin();
        if(gSlot[x][y] + gSlot[x + 1][y] + gSlot[x + 2][y] + gSlot[x + 3][y] == 20) rWin();

        if(gSlot[x][y] + gSlot[x + 1][y + 1] + gSlot[x + 2][y + 2] + gSlot[x + 3][y + 3] == 4) bWin();
        if(gSlot[x][y] + gSlot[x + 1][y + 1] + gSlot[x + 2][y + 2] + gSlot[x + 3][y + 3] == 20) rWin();

        if(gSlot[x][y] + gSlot[x - 1][y + 1] + gSlot[x - 2][y + 2] + gSlot[x - 3][y + 3] == 4) bWin();
        if(gSlot[x][y] + gSlot[x - 1][y + 1] + gSlot[x - 2][y + 2] + gSlot[x - 3][y + 3] == 20) rWin();

        if(gSlot[x][y] + gSlot[x][y + 1] + gSlot[x][y + 2] + gSlot[x][y + 3] == 4) bWin();
        if(gSlot[x][y] + gSlot[x][y + 1] + gSlot[x][y + 2] + gSlot[x][y + 3] == 20) rWin();
     }
   }
   if(isTie == 126) tie();
}

//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------

void __fastcall TForm1::s55MouseDown(TObject *Sender, TMouseButton Button,
      TShiftState Shift, int X, int Y)
{
if(ClientSocket1->Active == true  && pTurn == true)
   if(Button == mbLeft){
      Column1();
      ClientSocket1->Socket->SendText("c1");
      winner();
   }
   if(switcher == true && ServerSocket1->Active == true && pTurn == false)
      if(Button == mbLeft){
         switcher = false;
         Column1();
         ServerSocket1->Socket->Connections[0]->SendText("c1");
         winner();
      }
}
//---------------------------------------------------------------------------
void __fastcall TForm1::s74MouseDown(TObject *Sender, TMouseButton Button,
      TShiftState Shift, int X, int Y)
{
if(ClientSocket1->Active == true  && pTurn == true)
  if(Button == mbLeft){
     Column2();
     ClientSocket1->Socket->SendText("c2");
     winner();
  }
if(ServerSocket1->Socket->ActiveConnections > 0 && ServerSocket1->Active == true && pTurn == false)

  if(Button == mbLeft){
     switcher = false;
     Column2();
     ServerSocket1->Socket->Connections[0]->SendText("c2");
     winner();
  }
}
//---------------------------------------------------------------------------
void __fastcall TForm1::s75MouseDown(TObject *Sender, TMouseButton Button,
      TShiftState Shift, int X, int Y)
{
if(ClientSocket1->Active == true  && pTurn == true)
  if(Button == mbLeft){
     Column3();
     ClientSocket1->Socket->SendText("c3");
     winner();
  }
if(switcher == true && ServerSocket1->Active == true && pTurn == false)
  if(Button == mbLeft){
     switcher = false;
     Column3();
     ServerSocket1->Socket->Connections[0]->SendText("c3");
     winner();
  }
}
//---------------------------------------------------------------------------

void __fastcall TForm1::s76MouseDown(TObject *Sender, TMouseButton Button,
      TShiftState Shift, int X, int Y)
{
if(ClientSocket1->Active == true  && pTurn == true)
  if(Button == mbLeft){
     Column4();
     ClientSocket1->Socket->SendText("c4");
     winner();
  }
if(switcher == true && ServerSocket1->Active == true && pTurn == false)
  if(Button == mbLeft){
     switcher = false;
     Column4();
     ServerSocket1->Socket->Connections[0]->SendText("c4");
     winner();
  }
}
//---------------------------------------------------------------------------

void __fastcall TForm1::s77MouseDown(TObject *Sender, TMouseButton Button,
      TShiftState Shift, int X, int Y)
{
if(ClientSocket1->Active == true  && pTurn == true)
  if(Button == mbLeft){
     Column5();
     ClientSocket1->Socket->SendText("c5");
     winner();
  }
if(switcher == true && ServerSocket1->Active == true && pTurn == false)
  if(Button == mbLeft){
     switcher = false;
     ServerSocket1->Socket->Connections[0]->SendText("c5");
     Column5();
     winner();
  }
}
//---------------------------------------------------------------------------

void __fastcall TForm1::s78MouseDown(TObject *Sender, TMouseButton Button,
      TShiftState Shift, int X, int Y)
{
if(ClientSocket1->Active == true  && pTurn == true)
  if(Button == mbLeft){
     Column6();
     ClientSocket1->Socket->SendText("c6");
     winner();
  }
if(switcher == true && ServerSocket1->Active == true && pTurn == false)
  if(Button == mbLeft){
     switcher = false;
     Column6();
     ServerSocket1->Socket->Connections[0]->SendText("c6");
     winner();
  }
}
//---------------------------------------------------------------------------
void __fastcall TForm1::s79MouseDown(TObject *Sender, TMouseButton Button,
      TShiftState Shift, int X, int Y)
{
if(ClientSocket1->Active == true  && pTurn == true)
  if(Button == mbLeft){
     Column7();
     ClientSocket1->Socket->SendText("c7");
     winner();

  }
if(switcher == true && ServerSocket1->Active == true && pTurn == false)
  if(Button == mbLeft){
     switcher = false;
     Column7();
     ServerSocket1->Socket->Connections[0]->SendText("c7");
     winner();
  }
}
//---------------------------------------------------------------------------



void __fastcall TForm1::Exit1Click(TObject *Sender)
{
Application->Terminate();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::FormCreate(TObject *Sender)
{
ArrayIntilize();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Clear1Click(TObject *Sender)
{
clear();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::About1Click(TObject *Sender)
{
Beep();
MessageDlg("This Program was coded by Jerome Scott II",mtInformation,TMsgDlgButtons()<<mbOK,0);
}
//---------------------------------------------------------------------------


void __fastcall TForm1::Netsetup1Click(TObject *Sender)
{
Form2->Show();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::ClientSocket1Connect(TObject *Sender,
      TCustomWinSocket *Socket)
{
Form2->cConnectlb->Caption = "Connected: True";
Socket->SendText("Connected");
}
//---------------------------------------------------------------------------

void __fastcall TForm1::ClientSocket1Disconnect(TObject *Sender,
      TCustomWinSocket *Socket)
{
   Form2->sPortTxt->Enabled = true;
   Form2->cHostTxt->Enabled = true;
   Form2->cPortTxt->Enabled = true;
   Form2->sButton->Enabled  = true;
   Form2->cButton->Enabled =  true;
   Form2->cConnectlb->Caption = "Connected: False";
}
//---------------------------------------------------------------------------

void __fastcall TForm1::ClientSocket1Error(TObject *Sender,
      TCustomWinSocket *Socket, TErrorEvent ErrorEvent, int &ErrorCode)
{
ErrorCode = 0;
Form2->sPortTxt->Enabled = true;
Form2->cHostTxt->Enabled = true;
Form2->cPortTxt->Enabled = true;
Form2->sButton->Enabled  = true;
Form2->cButton->Enabled =  true;
Form2->cConnectlb->Caption = "Connected: False";
Beep();
MessageDlg("There was a error :(",mtError,TMsgDlgButtons()<<mbOK,0);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::ServerSocket1ClientDisconnect(TObject *Sender,
      TCustomWinSocket *Socket)
{
   Form2->sPortTxt->Enabled = true;
   Form2->cHostTxt->Enabled = true;
   Form2->cPortTxt->Enabled = true;
   Form2->cButton->Enabled  = true;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::ServerSocket1ClientError(TObject *Sender,
      TCustomWinSocket *Socket, TErrorEvent ErrorEvent, int &ErrorCode)
{
   ErrorCode = 0;
   Form2->sPortTxt->Enabled = true;
   Form2->cHostTxt->Enabled = true;
   Form2->cPortTxt->Enabled = true;
   Form2->cButton->Enabled  = true;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::ClientSocket1Read(TObject *Sender,
      TCustomWinSocket *Socket)
{
String blah;
blah = Socket->ReceiveText();

if(blah == "ready")
   wait = false;

if(blah == "c1"){
   Column1();
   winner();
}
if(blah == "c2"){
   Column2();
   winner();
}
if(blah == "c3"){
   Column3();
   winner();
}
if(blah == "c4"){
   Column4();
   winner();
}
if(blah == "c5"){
   Column5();
   winner();
}
if(blah == "c6"){
   Column6();
   winner();
}
if(blah == "c7"){
   Column7();
   winner();
}

}
//---------------------------------------------------------------------------

void __fastcall TForm1::ServerSocket1ClientRead(TObject *Sender,
      TCustomWinSocket *Socket)
{
String blah;
blah = Socket->ReceiveText();

if(blah == "ready")
   wait = false;
   
if(blah == "c1"){
   Column1();
   winner();
}
if(blah == "c2"){
   Column2();
   winner();
}
if(blah == "c3"){
   Column3();
   winner();
}
if(blah == "c4"){
   Column4();
   winner();
}
if(blah == "c5"){
   Column5();
   winner();
}
if(blah == "c6"){
   Column6();
   winner();
}
if(blah == "c7"){
   Column7();
   winner();
}
switcher = true;
}
//---------------------------------------------------------------------------


void __fastcall TForm1::ServerSocket1ClientConnect(TObject *Sender,
      TCustomWinSocket *Socket)
{
Form2->pclb->Caption = "Player Connected: True";
Form2->calb->Caption = "Client Address: " + ServerSocket1->Socket->Connections[0]->RemoteAddress;
}
//---------------------------------------------------------------------------


