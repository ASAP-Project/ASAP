/** **************************************************
 * File: BasicCalculator.h
 * A calculator program built using MFC dialog box
 * Copyright (c) 2002-2010 Advanced Applications Total Applications Works.
 * (AATAW)  all Rights Reserved.
 * 
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
 ****************************************************/

#include <afxwin.h>
#include <iostream>
//#include <ostrstream>
#include <strstream>
#include <iomanip>
#include <math.h>
#include "BasicCalculator_ids.h"
#include "BasicCalculator.h"
#include <fstream>    
#include <String.h>
#include <cstdlib>
#include <stdio.h>

using std::ostream ;
using std::ostrstream ;
using std::setprecision ;
using std::ends;

CCalculatorDialog::CCalculatorDialog() 
    : CDialog( "Calculator" )
{
   clear();
}

// clear result and entry
void CCalculatorDialog::clear()
{
   m_fResult = 0.0;
   m_opCode = NONE;

   clearEntry();
}

/** **************************************************
 * The clearEntry() method clears (number being 
 * entered in the textedit box)
 ****************************************************/
void CCalculatorDialog::clearEntry()
{
   m_szEntry[ 0 ] = '\0';
   m_nEntryLen = 0;
   m_bHavePoint = false;
}

/** **************************************************
 * Capture the character that the user enter
 ****************************************************/
void CCalculatorDialog::enter( char ch )
{
   m_szEntry[ m_nEntryLen++ ] = ch;
   m_szEntry[ m_nEntryLen ] = '\0';
   showEntry();
}

/** **************************************************
 * The HandleDigitPressed() method processes the digit 
 * button the user presses.
 **********************8******************************/
afx_msg void CCalculatorDialog::HandleDigitPressed( UINT digit )
{
   if ( m_nEntryLen < MAX_DIGITS )
   {
      // convert message id to character
      enter( digit - IDC_ZERO + '0' );
   }
}

/** **************************************************
 * The HandleDecPointPressed() method processes the 
 * decimal point button when the user presses it.
 **********************8******************************/
afx_msg void CCalculatorDialog::HandleDecPointPressed()      
{
   if ( !m_bHavePoint && m_nEntryLen < MAX_DIGITS )
   {
      m_bHavePoint = true; // allow only one point per number
      enter( '.' );
   }
}

/** **************************************************
 * The HandleClearPressed() method processes the 
 * clear button when the user presses it.
 * 1- All data being processed is cleared.
 **********************8******************************/
afx_msg void CCalculatorDialog::HandleClearPressed()      
{
   clear();
   showEntry();
}


/** **************************************************
 * The HandleClearEntryPressed() method processes the 
 * clear entry button when the user presses it.
 * 1- All data in the text editbox is cleared.
 **********************8******************************/
afx_msg void CCalculatorDialog::HandleClearEntryPressed() 
{
   clearEntry();
   showEntry();
   m_opCode = EQ;
   doOp();
}

/** **************************************************
 * The HandleMultPressed() method processes the 
 * multiplication button when the user presses it.
 **********************8******************************/
afx_msg void CCalculatorDialog::HandleMultPressed()       
{
   doOp();
   m_opCode = MPY;
}

/** **************************************************
 * The HandleDivPressed() method processes the 
 * division button when the user presses it.
 **********************8******************************/
afx_msg void CCalculatorDialog::HandleDivPressed()        
{
   doOp();
   m_opCode = DIV;
}


/** **************************************************
 * The HandleMinusPressed() method processes the 
 * Minus button when the user presses it.
 **********************8******************************/
afx_msg void CCalculatorDialog::HandleMinusPressed()      
{
   doOp() ;
   m_opCode = SUB ;
}

/** **************************************************
 * The HandlePlusPressed() method processes the 
 * Plus button when the user presses it.
 **********************8******************************/
afx_msg void CCalculatorDialog::HandlePlusPressed()       
{
   doOp() ;
   m_opCode = ADD ;
}


/** **************************************************
 * The HandlePMPressed() method processes the 
 * Plus/Minus button when the user presses it.
 **********************8******************************/
afx_msg void CCalculatorDialog::HandlePMPressed()         
{   
   m_fResult = -1.0 * m_fResult ;
   showResult();
   m_opCode = EQ;
}


/** **************************************************
 * The HandleEqualPressed() method processes the 
 * equals button when the user presses it.
 **********************8******************************/
afx_msg void CCalculatorDialog::HandleEqualPressed()         
{
   doOp();
   m_opCode = EQ;
}


/** **************************************************
 * The HandleExitPressed() method processes the 
 * exits button when the user presses it.
 **********************8******************************/
afx_msg void CCalculatorDialog::HandleExitPressed() {
   if( AfxMessageBox( "Do you really want to exit?", MB_YESNO ) == IDYES )
	   OnOK() ;
}

/** **************************************************
 * The HandleMyHelpPressed() method processes the 
 * help button when the user presses it.
 **********************8******************************/
afx_msg void CCalculatorDialog::HandleMyHelpPressed() {
   WinExec( "c:\\Program Files\\Internet Explorer\\IExplore.exe  http://sumtotalz.com/TotalAppsWorks/Calc_CPP/BasicCalculator_I_Tut.html" , SW_SHOW )   ;
} 

/** **************************************************
 * The HandleMyAboutPressed() method processes the 
 * about button when the user presses it.
 **********************8******************************/
afx_msg void CCalculatorDialog::HandleMyAboutPressed()  {
   WinExec( "c:\\Program Files\\Internet Explorer\\IExplore.exe  http://www.sumtotalz.com/" , SW_SHOW )   ;
}

/** **************************************************
 * The doOp() method processes the pending operations
 * when the user presses an operation button.
 **********************8******************************/
   void CCalculatorDialog::doOp() {
      fFirstNumber = atof( m_szEntry );
      fTemp = m_fResult ;

      switch ( m_opCode )   {
         case MPY:
            m_fResult *= fFirstNumber;
         break;

         case DIV: 
	    if( fFirstNumber == 0.0 )
	       AfxMessageBox( "You cannot divide by zero.", MB_OK )  ;
	    else {
               m_fResult /= fFirstNumber ;
            }
         break;

         case SUB:
            m_fResult -= fFirstNumber;
         break;

         case ADD:
            m_fResult += fFirstNumber;
         break;

         case EQ:
         case NONE:
            if ( m_nEntryLen > 0 )  // if user entered a new number,
               m_fResult = fFirstNumber;  // make it the left operand
      }

      m_opCode = NONE;
      clearEntry();

      showResult();
   }

/** **************************************************
 * 
 * 
 **********************8******************************/
   void CCalculatorDialog::showResult()  {
      static char m_szString[ MAX_DIGITS + 1 ];
      static ostrstream m_oStream( m_szString, MAX_DIGITS );

      m_oStream.seekp( 0 );
      m_oStream << setprecision( MAX_DIGITS );
      m_oStream << m_fResult << ends;
      CEdit *pDisplay = ( CEdit * ) GetDlgItem( IDC_DISPLAY );
      pDisplay->SetWindowText( m_szString );
   }

   
/** **************************************************
 * 
 * 
 **********************8******************************/
   void CCalculatorDialog::showEntry()   {
      CEdit *pDisplay = ( CEdit * ) GetDlgItem( IDC_DISPLAY );
      if ( pDisplay )
         pDisplay->SetWindowText( m_szEntry );
   }

   BEGIN_MESSAGE_MAP( CCalculatorDialog, CDialog )
      ON_COMMAND_RANGE( IDC_ZERO, IDC_NINE, HandleDigitPressed )
      ON_COMMAND( IDC_DECPT,   HandleDecPointPressed )
      ON_COMMAND( IDC_CE,      HandleClearEntryPressed )
      ON_COMMAND( IDC_CLR,     HandleClearPressed )
      ON_COMMAND( IDC_MULT,    HandleMultPressed )
      ON_COMMAND( IDC_DIV,     HandleDivPressed )
      ON_COMMAND( IDC_MINUS,   HandleMinusPressed )
      ON_COMMAND( IDC_PLUS,    HandlePlusPressed )
      ON_COMMAND( IDC_PM,      HandlePMPressed )
      ON_COMMAND( IDC_EQUAL,   HandleEqualPressed )
      ON_COMMAND( IDC_EXIT,    HandleExitPressed )
      ON_COMMAND( IDC_MYHELP,  HandleMyHelpPressed )
      ON_COMMAND( IDC_MYABOUT, HandleMyAboutPressed )
   END_MESSAGE_MAP()
 
   
   
/** **************************************************
 * dialog-based application entry point.
 **********************8******************************/
   class CCalculatorApp : public CWinApp {
      public:
         BOOL InitInstance()    {
            CCalculatorDialog calculatorDialog;
            calculatorDialog.DoModal();   // run dialog
            return FALSE;                 // finished
         }
   } calculator;
