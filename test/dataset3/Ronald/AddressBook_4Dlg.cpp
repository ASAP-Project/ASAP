/********************************************************
 * AddressBook_4Dlg.cpp : This is the main file for this application
 *  
 * Copyright (c) 2002-2004 Advanced Applications Total Applications Works.
 * (AATAW)  All Rights Reserved.
 *
 * AATAW grants you ("Licensee") a non-exclusive, royalty free, license to use,
 * modify and redistribute this software in source and binary code form,
 * provided that i) this copyright notice and license appear on all copies of
 * the software; and ii) Licensee does not utilize the software in a manner
 * which is disparaging to AATAW.
 *
 * This software is provided "AS IS," without a warranty of any kind. ALL
 * EXPRESS OR IMPLIED CONDITIONS, REPRESENTATIONS AND WARRANTIES, INCLUDING ANY
 * IMPLIED WARRANTY OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE OR
 * NON-INFRINGEMENT, ARE HEREBY EXCLUDED. AATAW AND ITS LICENSORS SHALL NOT BE
 * LIABLE FOR ANY DAMAGES SUFFERED BY LICENSEE AS A RESULT OF USING, MODIFYING
 * OR DISTRIBUTING THE SOFTWARE OR ITS DERIVATIVES. IN NO EVENT WILL AATAW OR ITS
 * LICENSORS BE LIABLE FOR ANY LOST REVENUE, PROFIT OR DATA, OR FOR DIRECT,
 * INDIRECT, SPECIAL, CONSEQUENTIAL, INCIDENTAL OR PUNITIVE DAMAGES, HOWEVER
 * CAUSED AND REGARDLESS OF THE THEORY OF LIABILITY, ARISING OUT OF THE USE OF
 * OR INABILITY TO USE SOFTWARE, EVEN IF SUN HAS BEEN ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGES.
 *
 * This software is not designed or intended for use in on-line control of
 * aircraft, air traffic, aircraft navigation or aircraft communications; or in
 * the design, construction, operation or maintenance of any nuclear
 * facility. Licensee represents and warrants that it will not use or
 * redistribute the Software for such purposes or for commercial purposes.
 *
 *
 *
 *******************************************************/


         

#include <iostream.h>
#include <cstdlib>
#include <stdio.h>
#include "stdafx.h"
#include "AddressBook_4.h"
#include "AddressBook_4Dlg.h"
#include "AddRecord.h"
#include "DeleteRec.h"
#include "UpdateRec.h"
#include <fstream.h>   
#include <iomanip.h> 
#include <strstrea.h>
#include <string>

using std::string ;

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAddressBook_4Dlg dialog

CAddressBook_4Dlg::CAddressBook_4Dlg(CWnd* pParent /*=NULL*/)
	: CDialog(CAddressBook_4Dlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CAddressBook_4Dlg)
	m_lAddress = _T("");
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CAddressBook_4Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAddressBook_4Dlg)
	DDX_LBString(pDX, IDC_ADDRESSLIST, m_lAddress);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAddressBook_4Dlg, CDialog)
	//{{AFX_MSG_MAP(CAddressBook_4Dlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_COMMAND( IDC_ADD , OnAdd)
	ON_COMMAND( IDC_UPDATE , OnUpdate)
	ON_COMMAND( IDC_DELETE , OnDelete)
	ON_COMMAND( IDC_REFRESH , OnRefresh )
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAddressBook_4Dlg message handlers

BOOL CAddressBook_4Dlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here

    if ( RecordCount() < 1 )
      InitData() ;

	DisplayData( RecordCount() )  ;
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

/* *************************************************
 * Display all records in the AddressBook.dat file
 * 1- Create a header for the data to be displayed
 * 2- Create a loop to read all of the records in the file
 * 3- Write data from each record to stdout:`cout
 * *************************************************/
afx_msg void CAddressBook_4Dlg::DisplayData(  int n )    {    
    
   AddressStruct addStruct, *addStructPtr = &addStruct ;

   char chrSW15[15]   ;  
   strcpy( chrSW15 , "               " ) ;
   char chr[700]  ;  	  
   ostrstream str( chr , 700 ) ;

   // Get address of List Box
   pAddresses = ( CListBox * ) GetDlgItem( IDC_ADDRESSLIST );

   pAddresses->EnableWindow( TRUE ) ;

   for( int ii = 0; ii < n; ii++)    { 
	  ReadData(ii, addStruct);

	  sprintf( chrSW15, "%d", addStructPtr->recordID );  
      str.seekp( 0 ) ;
	  str << setiosflags( ios::left  )  
          << setw(12 ) << addStructPtr->recordID  
          <<  setw(18 ) <<  addStructPtr->lastName 
          << setw(22 ) << addStructPtr->firstName  
          << setw(15 ) << addStructPtr->telephone  <<  ends;  
 
      pAddresses->AddString( chr ) ; 
   }

   pAddresses->UpdateWindow();

}
/************* End of DisplayData ***************/


/****************************************************
 * 1- Create and initialize an array with address records
 * 2- Use the array to write the data to instance variables
 * 3- Write object to file a record at a time
 ****************************************************/
void CAddressBook_4Dlg::InitData() {

 AddressStruct addStruct, *addStructPtr = &addStruct ;
   	long sizeAR = 14 ;	

    char *addrRecord[ 14 ][ 9 ]  = {
                  {"James", "Wilie", "123 Main St.", "Garner", "NC", "27500",  "MyID@MyISP.com", "919-555-3442", "919-555-5442"},
                  {"Julie", "Smith", "123 Oak St.", "Raleigh", "NC", "27500",  "MyID@MyISP.com",   "919-555-3782", "919-555-5782"},
                  {"Mary", "Easley", "123 Walnut St.", "Apex", "NC", "27500",  "MyID@MyISP.com",   "919-555-5552", "919-555-6552"},
                  {"Cato", "Willingham", "123 Jones St.", "Durham", "NC", "27500", "MyID@MyISP.com",   "919-555-3492", "919-555-5492"},
                  {"Mike", "Jordan", "123 Saunders St.", "Apex", "NC", "27500",  "MyID@MyISP.com",   "919-555-3882", "919-555-5882"},
                  {"Carole", "Fusemi", "123 Oak Lane", "Raleigh", "NC", "27500",  "MyID@MyISP.com",   "919-555-3472", "919-555-5472"},
                  {"Peter", "Wie", "123 Oak Way", "Garner", "NC", "27500", "MyID@MyISP.com",   "919-555-3642", "919-555-5642"},
                  {"Donald", "Hill", "123 Oak Blvd.", "Cary", "NC", "27500", "MyID@MyISP.com",   "919-555-3452", "919-555-5452"},
                  {"Regina", "Bell", "123 Walnut Lane", "Apex", "NC", "27500",  "MyID@MyISP.com",   "919-555-3342", "919-555-5342"},
                  {"Althea", "Keyes", "123 Walnut Way", "Raleigh", "NC", "27500",  "MyID@MyISP.com",   "919-555-3332", "919-555-5332"},
                  {"Charles", "Lawrence", "123 Whatis St.", "Garner", "NC", "27500",  "MyID@MyISP.com",   "919-555-3222", "919-555-5222"},
                  {"Robert", "Urengo", "123 Academy St.", "Durham", "NC", "27500",  "MyID@MyISP.com",   "919-555-3112", "919-555-5112"},
                  {"John", "Wieland", "123 MaIn St.", "Apex", "NC", "27709",  "MyID@MyISP.com", "919-555-9088", "919-555-9089"},
                  {"Keith", "Makey", "404 Walnut Ave.", "Raleigh", "NC", "27511",  "MyID@MyISP.com", "919-555-9088", "919-555-9089"}
             } ;

   
   for ( int ii = 0; ii < sizeAR; ii++ ) {
		 
      addStructPtr->recordID = ii ;
      strcpy( addStructPtr->firstName, addrRecord[ ii ][ 0 ] ) ;
      strcpy( addStructPtr->lastName, addrRecord[ ii ][ 1 ] ) ;		 
      strcpy( addStructPtr->address, addrRecord[ ii ][ 2 ] ) ;
      strcpy( addStructPtr->city, addrRecord[ ii ][ 3 ] ) ;
      strcpy( addStructPtr->state, addrRecord[ ii ][ 4 ] ) ;
      strcpy( addStructPtr->zip, addrRecord[ ii ][ 5 ] ) ;
      strcpy( addStructPtr->telephone, addrRecord[ ii ][ 7 ] ) ;
      strcpy( addStructPtr->fax, addrRecord[ ii ][ 8 ] ) ;
      strcpy( addStructPtr->email, addrRecord[ ii ][ 6 ] ) ;

	  WriteData( addStruct );
   }

}
/************* End of InitData2 ***************/

/* *************************************************
 *
 *
 * *************************************************/
void CAddressBook_4Dlg::Add( CString m_sFName , CString m_sLName , 		
              CString m_sAddress , CString  m_sCity  ,
			  CString m_sState , CString m_sZip , 		
              CString m_sTele , CString  m_sFax  ,
              CString m_sEmail   ) {

   AddressStruct addStruct, *addStructPtr = &addStruct ;

   addStructPtr->recordID = RecordCount() ;
   strcpy( addStructPtr->firstName , m_sFName ) ; 
   strcpy( addStructPtr->lastName  , m_sLName ) ;
   strcpy( addStructPtr->address   , m_sAddress ) ;
   strcpy( addStructPtr->city      , m_sCity ) ;
   strcpy( addStructPtr->state     , m_sState ) ;
   strcpy( addStructPtr->zip       , m_sZip ) ;
   strcpy( addStructPtr->telephone , m_sTele ) ;
   strcpy( addStructPtr->fax       , m_sFax ) ;
   strcpy( addStructPtr->email     , m_sEmail ) ;

   
   WriteData( addStruct );
}
/************* End of Add ***************/

/* *************************************************
 *
 *
 * *************************************************/
void CAddressBook_4Dlg::UpDateRec( int m_iRecID , CString m_sFName , CString m_sLName , 		
              CString m_sAddress , CString  m_sCity  ,
			  CString m_sState , CString m_sZip , 		
              CString m_sTele , CString  m_sFax  ,
              CString m_sEmail   ) {

   AddressStruct addStruct, *addStructPtr = &addStruct ;

   addStructPtr->recordID = m_iRecID ;
   strcpy( addStructPtr->firstName , m_sFName ) ; 
   strcpy( addStructPtr->lastName  , m_sLName ) ;
   strcpy( addStructPtr->address   , m_sAddress ) ;
   strcpy( addStructPtr->city      , m_sCity ) ;
   strcpy( addStructPtr->state     , m_sState ) ;
   strcpy( addStructPtr->zip       , m_sZip ) ;
   strcpy( addStructPtr->telephone , m_sTele ) ;
   strcpy( addStructPtr->fax       , m_sFax ) ;
   strcpy( addStructPtr->email     , m_sEmail ) ;

   
   UpdateData( m_iRecID, addStruct );
}
/************* End of Add ***************/

/* *************************************************
 *
 *
 * *************************************************/
void  CAddressBook_4Dlg::Delete( int  m_iRecordID ) {
	
   AddressStruct addStruct, *addStructPtr = &addStruct ;
   
   addStructPtr->recordID = m_iRecordID ;
   strcpy( addStructPtr->firstName , "" ) ; 
   strcpy( addStructPtr->lastName  , "" ) ;
   strcpy( addStructPtr->address   , "" ) ;
   strcpy( addStructPtr->city      , "" ) ;
   strcpy( addStructPtr->state     , "" ) ;
   strcpy( addStructPtr->zip       , "" ) ;
   strcpy( addStructPtr->telephone , "" ) ;
   strcpy( addStructPtr->fax       , "" ) ;
   strcpy( addStructPtr->email     , "" ) ;

   UpdateData( m_iRecordID , addStruct );

}
/************* End of Delete ***************/

/* *************************************************
 * 1- Create an ifstream object for input
 * 2- Open the Addressbook.dat file for reading
 * 3- Calculate the point where the record to be read is located
 * 4- Read the record from the file  
 * *************************************************/
void CAddressBook_4Dlg::ReadData(int recID, AddressStruct &addStruct)  {    // read recordID = recID

                                // from file
   ifstream infile;                           // make stream
   infile.open("Addressbook.dat", ios::binary);
   infile.seekg( recID * 220 );         // move file ptr  
   infile.read( (char*)&addStruct, sizeof(addStruct)  ); // read one addressrecord
   infile.close() ;
}
/************* End of ReadData ***************/

/* *************************************************
 * 1- Create an ofstream object for output
 * 2- Open the Addressbook.dat file for writing
 * 3- Calculate the point where the record to be written is located
 * 4- Write the record to the end of the file  
 * *************************************************/
void CAddressBook_4Dlg::WriteData( AddressStruct  &addStruct)   {     

   ofstream outfile;             // make an output file stream
                                 // open it and write at the end of the file
   outfile.open("Addressbook.dat", ios::app | ios::binary);
   outfile.write( (char*)&addStruct, sizeof(addStruct)  ) ; // write to it
   outfile.close() ;
}
/************* End of WriteData ***************/

/* *************************************************
 * 1- Create an ofstream object
 * 2- Open the Addressbook.dat file for writing
 * 3- Calculate the point where the record to be updated is located
 * 4- Write the record to the file using ios::ate so data 
 *    can be written anywhere in the file. 
 * *************************************************/
void CAddressBook_4Dlg::UpdateData( long n, AddressStruct  addStruct)   {        
   
   ofstream outfile;             // make an output file stream
                                 // open the file                                 
   outfile.open("Addressbook.dat", ios::ate | ios::binary);
   outfile.seekp( (n * sizeof(addStruct)  ) , ios::beg); 
   outfile.write( (char*)&addStruct, sizeof(addStruct)  ); // write to it
   outfile.close() ;
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
int CAddressBook_4Dlg::RecordCount()    {      
   
   AddressStruct addStruct, *addStructPtr = &addStruct ;

   ifstream infile;
   infile.open("Addressbook.dat", ios::binary);
   infile.seekg(0, ios::end);    // go to 0 bytes from end
                                 // calculate number of  address records
   return (int)infile.tellg() / sizeof( addStruct ) ;

}
/************* End of RecordCount ***************/

void CAddressBook_4Dlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CAddressBook_4Dlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CAddressBook_4Dlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

/*****************************************************
 * 1- Create a new instance of the AddRecord Dialog class
 * 2- Display the dialog in a modal mode
 * 3- Make dialog invisiable on exit
 *
 ****************************************************/
afx_msg void CAddressBook_4Dlg::OnAdd( int n )
{
   AddRecord *pAddDlg = new AddRecord;	 
   pAddDlg->DoModal() ;
   pAddDlg->OnOK ;
}

/*****************************************************
 * 1- Create a new instance of the OnUpdate Dialog class
 * 2- Display the dialog in a modal mode
 * 3- Make dialog invisiable on exit
 *
 ****************************************************/
afx_msg void CAddressBook_4Dlg::OnUpdate( int n )
{
   UpdateRec *pUpDlg = new UpdateRec;	 
   MessageBox("Enter the record ID of the record you wish to update and then press the GetRecord button." ,
       "Update Dialog Information" ,
	   MB_OK | MB_ICONINFORMATION ) ;
   pUpDlg->DoModal() ; 	 
}

/*****************************************************
 * 1- Create a new instance of the OnDelete Dialog class
 * 2- Display the dialog in a modal mode
 * 3- Make dialog invisiable on exit
 *
 ****************************************************/
afx_msg void CAddressBook_4Dlg::OnDelete( int n )
{
   DeleteRec *pDelDlg = new DeleteRec;	 
   pDelDlg->DoModal() ;	 
}

/*****************************************************
 * 1- Get address to the Listbox control
 * 2- Erase the contents of the listbox
 * 3- Make sure the window is enabled
 * 4- Repopulate the listbox
 *
 ****************************************************/
afx_msg void CAddressBook_4Dlg::OnRefresh(  )
{
     // Get address of List Box
   pAddresses = ( CListBox * ) GetDlgItem( IDC_ADDRESSLIST );
   pAddresses->ResetContent() ;

   pAddresses->EnableWindow( TRUE ) ; 	

   DisplayData( RecordCount() )  ; 

}
