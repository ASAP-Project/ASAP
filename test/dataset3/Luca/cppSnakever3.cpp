// Author: Luca Carlon
// Title: Snake ver3
// Version: 3

#include <windows.h>
#include <stdlib.h>
#include <stdio.h>
#include "resource.h"
#include "hDeclarations.h"
#include "hExtern.h"

LRESULT CALLBACK WndProc           (HWND, UINT, WPARAM, LPARAM);
BOOL    CALLBACK AboutDlgProc      (HWND, UINT, WPARAM, LPARAM);
BOOL    CALLBACK HelpDlgProc       (HWND, UINT, WPARAM, LPARAM);
VOID    CALLBACK TimerProc         (HWND, UINT, UINT, DWORD);

// Old coordinates of the last segment I want to delete
punto old;
// Declare the variable segment punto (point) since I need to know the two coordinates x and y
punto segment[MAX_SNAKE_LENGTH];
// Declaring the variable which will contain the coordinates of the common apple
punto apple;
// This variable will contain the coordinates of the bonus apple
punto bonus;
// Number of snake's segments
int iSegments;
// Stores the informations about the measures of the window
RECT rect;
// Handle of the window
HWND hwnd;
// Stores the current direction of the snake
// 1. Up
// 2. Down
// 3. Right
// 4. Left
unsigned short int usiDirection = 3;
// This variable indicates wether the game is in pause or not
bool bPause;
// Determines when the program should update the score
bool bUpdateScore = true;
// Drawn the borders?
bool bDrawn;
// Apples eaten
unsigned int uiEatenApples = 0;


int WINAPI WinMain (HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR szCmdLine, int iCmdShow)
{
  static TCHAR szAppName[] = TEXT ("Snake ver3 - Not playing") ;
  MSG          msg ;
  WNDCLASS     wndclass ;

  wndclass.style         = CS_HREDRAW | CS_VREDRAW;
  wndclass.lpfnWndProc   = WndProc;
  wndclass.cbClsExtra    = 0;
  wndclass.cbWndExtra    = 0;
  wndclass.hInstance     = hInstance ;
  wndclass.hIcon         = LoadIcon (hInstance, "icon");
  wndclass.hCursor       = LoadCursor (NULL, IDC_ARROW);
  wndclass.hbrBackground = CreateSolidBrush(0);
  wndclass.lpszMenuName  = "main_menu";
  wndclass.lpszClassName = szAppName;

  if (!RegisterClass (&wndclass))
  {
    MessageBox (NULL, TEXT ("This program requires Windows NT!"), 
                    szAppName, MB_ICONERROR);
    return 0 ;
  }
    
  hwnd = CreateWindow (szAppName,                  // window class name
                       szAppName,                  // window caption
                       WS_OVERLAPPEDWINDOW,        // window style
                       100,                        // initial x position
                       100,                        // initial y position
                       (SNAKE_SEGMENT_LENGTH + 1) * 50 + 12,                        // initial x size
                       (SNAKE_SEGMENT_HEIGHT + 1) * 30 + 53,                        // initial y size
                       NULL,                       // parent window handle
                       NULL,                       // window menu handle
                       hInstance,                  // program instance handle
                       NULL) ;                     // creation parameters
    
  ShowWindow (hwnd, iCmdShow) ;
  UpdateWindow (hwnd) ;
  
  while (GetMessage (&msg, NULL, 0, 0))
  {
    TranslateMessage (&msg) ;
    DispatchMessage (&msg) ;
  }
  return msg.wParam ;
}

LRESULT CALLBACK WndProc (HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	static HINSTANCE hInstance;


	switch(message)
	{
		case WM_CREATE:
		{
			// Set the boolean iDrawn to false since I want the borders of the ring to be created
			bDrawn = false;

			// Set the game in pause
			bPause = true;

			// I want the game to start with 2 segments of the snake
			iSegments = 1;

			// Set the first two positions of the segments
			segment[0].iPosX = 2;
			segment[0].iPosY = 2;

			// Get the measures of the window
			GetClientRect(hwnd, &rect);

			CalculateAppleCoordinates();

			return 0;
		}

		// This message is sent whenever a key is pressed
		case WM_KEYDOWN:
		{
			switch(wParam)
			{
				case VK_LEFT:
				{
					// If the snake is going right I exit the case since the snake cannot turn
					if (usiDirection == 3) break;

					// Change the direction of the snake
					if (!bPause) usiDirection = 4;

					break;
				}

				case VK_RIGHT:
				{
				
					// If the snake is going left I exit the case since the snake cannot turn
					if (usiDirection == 4) break;

					// Change the direction of the snake
					if (!bPause) usiDirection = 3;

					break;
				}

				case VK_UP:
				{
					// If the snake is going down I exit the case since the snake cannot turn
					if (usiDirection == 2) break;

					// Change the direction of the snake
					if (!bPause) usiDirection = 1;

					break;
				}

				case VK_DOWN:
				{
					// If the snake is going up I exit the case since the snake cannot turn
					if (usiDirection == 1) break;

					// Change the direction of the snake
					if (!bPause) usiDirection = 2;

					break;
				}

				case 80:
				{
					// If the game is in pause then I start it, otherwise I pause it
					if (bPause)
					{
						SetTimer(hwnd, ID_TIMER_MAIN, 60, TimerProc);

						bPause = false;
					}
					else
					{
						KillTimer(hwnd, ID_TIMER_MAIN);

						bPause = true;

						SetWindowText(hwnd, "Snake ver3 - Playing but in pause");
					}

					break;
				}
			}

			return 0;
		}

		case WM_PAINT:
		{
			// Obtaining the handle to the device context and the paintstruct variable
			PAINTSTRUCT ps;

			HDC hdc;

			hdc = BeginPaint(hwnd, &ps);

			if (!bDrawn) 
			{
				// Select the current pen which is being used to draw the borders
				SelectObject(hdc, GetStockObject(WHITE_PEN));

				// Build the two vertical lines
				MoveToEx(hdc, rect.left + 1, rect.top + 1, NULL);
				LineTo(hdc, rect.left + 1, rect.bottom - 1);

				MoveToEx(hdc, rect.right - 1, rect.top + 1, NULL);
				LineTo(hdc, rect.right - 1, rect.bottom - 1);

				// Build the two orizontal lines
				MoveToEx(hdc, rect.left + 1, rect.top + 1, NULL);
				LineTo(hdc, rect.right - 1, rect.top + 1);

				MoveToEx(hdc, rect.left + 1, rect.bottom - 1, NULL);
				LineTo(hdc, rect.right - 1, rect.bottom - 1);

				bDrawn = true;
			}

			// Select the current pen which is being used to draw the borders
			SelectObject(hdc, CreatePen(PS_SOLID, 1, GetSysColor(COLOR_WINDOWFRAME)));

			// Building the snake (draw only the new head)
			Rectangle(hdc, segment[0].iPosX, segment[0].iPosY, segment[0].iPosX + SNAKE_SEGMENT_LENGTH, segment[0].iPosY + SNAKE_SEGMENT_HEIGHT);

			// Draw the common apple
			Rectangle(hdc, apple.iPosX, apple.iPosY, apple.iPosX + SNAKE_SEGMENT_LENGTH, apple.iPosY + SNAKE_SEGMENT_HEIGHT);

			// Selecting the right brush to clear the last segment
			SelectObject(hdc, CreateSolidBrush(GetSysColor(COLOR_WINDOWFRAME)));

			// Remove the last segment of the trail
			if (!bPause) Rectangle(hdc, old.iPosX, old.iPosY, old.iPosX + SNAKE_SEGMENT_LENGTH, old.iPosY + SNAKE_SEGMENT_HEIGHT);

			// Close and release the device context since I don't need it anymore.
			EndPaint(hwnd, &ps);

			return 0;
		}

		// This message is sent whenever a button or a menu is clicked
		case WM_COMMAND:
		{
			switch(LOWORD(wParam))
			{
				// From the game menu the user clicked New
				case ID_GAME_NEW:
				{
					// Pausing the game
					bPause = true;

					GameOver();

					SetWindowText(hwnd, "Snake ver3 - Playing but paused");

					break;
				}

				// From the game menu the user clicked Exit
				case ID_GAME_EXIT:
				{
					SendMessage(hwnd, WM_DESTROY, NULL, NULL);

					break;
				}

				// From the ? menu the user clicked help
				case ID_HELP_HELP:
				{
					// Open window
					DialogBox(hInstance, MAKEINTRESOURCE(IDD_DIALOG_ABOUT), 0, AboutDlgProc);

					break;
				}

				case ID_HELP_ABOUT:
				{
					// Open the new window
					DialogBox(hInstance, MAKEINTRESOURCE(IDD_DIALOG_HELP), 0, HelpDlgProc);

					break;
				}
			}

			return 0;
		}
		
		// This message is sent to the Window procedure whenever the user wants to close the window
		case WM_DESTROY:
		{
			PostQuitMessage(0);

			return 0;
		}
	}
	return DefWindowProc(hwnd, message, wParam, lParam);
}

// Timer procedure
VOID CALLBACK TimerProc(HWND hwnd, UINT message, UINT iTimerID, DWORD dwTime)
{

	// Termporary structure
	punto tmpSegment[MAX_SNAKE_LENGTH];

	// Last segment (to be cleared)
	old.iPosX = segment[iSegments - 1].iPosX;
	old.iPosY = segment[iSegments - 1].iPosY;
	
	// Insert the new head in the first element of the structure
	switch(usiDirection)
	{
		case 1:
		{
			// The snake is heading up
			tmpSegment[0].iPosX = segment[0].iPosX;
			tmpSegment[0].iPosY = segment[0].iPosY - SNAKE_SEGMENT_HEIGHT - 1;
			break;
		}

		case 2:
		{
			// The snake is heading down
			tmpSegment[0].iPosX = segment[0].iPosX;
			tmpSegment[0].iPosY = segment[0].iPosY + SNAKE_SEGMENT_HEIGHT + 1;

			break;
		}

		case 3:
		{
			// The snake is heading right
			tmpSegment[0].iPosX = segment[0].iPosX + SNAKE_SEGMENT_LENGTH + 1;
			tmpSegment[0].iPosY = segment[0].iPosY;

			break;
		}

		case 4:
		{
			// The snake is heading left
			tmpSegment[0].iPosX = segment[0].iPosX - SNAKE_SEGMENT_LENGTH - 1;
			tmpSegment[0].iPosY = segment[0].iPosY;

			break;
		}
	}

	// The snake has crashed against the vertical borders
	if (tmpSegment[0].iPosX <= 1 || tmpSegment[0].iPosX + SNAKE_SEGMENT_LENGTH >= rect.right)
	{
		KillTimer(hwnd, ID_TIMER_MAIN);
		MessageBox(hwnd, "Game over", "Game informations", NULL);

		GameOver();

		return;
	}

	// The snake has crashed against the orizontal borders
	if (tmpSegment[0].iPosY <= 1 || tmpSegment[0].iPosY +	SNAKE_SEGMENT_HEIGHT >= rect.bottom)
	{
		KillTimer(hwnd, ID_TIMER_MAIN);
		MessageBox(hwnd, "Game over", "Game informations", NULL);

		GameOver();

		return;
	}

	// Copy the whole structure segment into tmpSegment from the element 0 to the element (iSegments - 1)
	for (int a = 0; a < iSegments - 1; a++)
	{
		tmpSegment[a + 1].iPosX = segment[a].iPosX;
		tmpSegment[a + 1].iPosY = segment[a].iPosY;
	}

	// The snake has eaten the apple
	if (tmpSegment[0].iPosX == apple.iPosX && tmpSegment[0].iPosY == apple.iPosY)
	{
		// Change apple coordinates
		CalculateAppleCoordinates();

		if (iSegments < 31)
		{
			// Leave the last segment since the trail must be longer
			tmpSegment[iSegments].iPosX = segment[iSegments - 1].iPosX;
			tmpSegment[iSegments].iPosY = segment[iSegments - 1].iPosY;
		}

		// When an apple is eaten the snake has to grow
		iSegments++;

		// Recalculate eaten apples
		uiEatenApples++;
	}

	// TODO: Check if the snake has eaten his own trail

	// Copy all in the permanent structure
	for (a = 0; a < iSegments; a++)
	{
		segment[a].iPosX = tmpSegment[a].iPosX;
		segment[a].iPosY = tmpSegment[a].iPosY;
	}

	// Check if the snake has eaten his own trail
	for (a = 1; a < iSegments; a++)
	{
		if (segment[0].iPosX == segment[a].iPosX && segment[0].iPosY == segment[a].iPosY)
		{
			KillTimer(hwnd, ID_TIMER_MAIN);
			MessageBox(hwnd, "Game over", "Game informations", NULL);

			GameOver();
		}
	}

	InvalidateRect(hwnd, &rect, FALSE);

	// This variable will contain the string with the score and the apples eaten
	char szWindowCaption[100];

	// Create the string with the score
	sprintf(szWindowCaption, "Score: %i - Apples eaten: %i", uiEatenApples * POINTS_PER_APPLE, uiEatenApples);

	// Set the string as title of the window
	SetWindowText(hwnd, szWindowCaption);
}

BOOL CALLBACK AboutDlgProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch(message)
	{
		case WM_CLOSE:
		{
			EndDialog(hwnd, 0);
			break;
		}

		case WM_COMMAND:
		{
			EndDialog(hwnd, 0);
			break;
		}
	}
	return FALSE;
}

BOOL CALLBACK HelpDlgProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch(message)
	{
		case WM_CLOSE:
		{
			EndDialog(hwnd, 0);
			break;
		}

		case WM_COMMAND:
		{
			EndDialog(hwnd, 0);
			break;
		}
	}
	return FALSE;
}