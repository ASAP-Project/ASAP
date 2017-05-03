/*===================================================================*
 *NAME      :	TrainMaster                                          *
 *PURPOSE   :	This program is developed as a task of an assignment *
 *		of HND-IT of ICBT City Campus.  It is used to record *
 *		the seat reservations for a long distant train.      *
 *AUTHOR    :	Sandeep Ellawala                                     *
 *CONTACT   :   sandeep.ellawala@gmail.com                           *
 *              +94(0)774055644                                      *
 *NOTE      :   This program does not use any files or databases to  *
 *              store any kind of data.  It simply uses an arrray to *
 *              keep track of data being manipulated.  Every time the*
 *              program runs, it starts fresh.                       *
 *===================================================================*/



/*This program can be compiled only with a Turbo C compiler due to   *
 *the fact that some of the functions used in this program are only  *
 *available with Borland Turbo C compiler package.  We are to handle *
 *this before the code is compiled.                                  */
# ifndef __TURBOC__
	# error Only Turbo C compiler is compatible with this code!
# endif



/*-------------------------------------------------------------------*
 *                       INCLUDED HEADER FILES                       *
 *-------------------------------------------------------------------*/
# include <conio.h>
# include <stdio.h>
# include <stdlib.h>



/*-------------------------------------------------------------------*
 *                         DEFINED CONSTANTS                         *
 *-------------------------------------------------------------------*/
# define TRUE              1
# define FALSE             0

# define NOT_RESERVED      0 /*00000000*/
# define RESERVED          1 /*00000001*/
# define BERTH             2 /*00000010*/
# define FOOD              4 /*00000100*/

# define SEAT_COUNT       16
# define COMP_COUNT       15

# define FIRST_COUNT       3
# define SECOND_COUNT      5



/*-------------------------------------------------------------------*
 *                           TYPES DEFINED                           *
 *-------------------------------------------------------------------*/
typedef unsigned short int BOOL;

typedef unsigned short int RES_TYPE;



/*-------------------------------------------------------------------*
 *                          GLOBAL VARIABLES                         *
 *-------------------------------------------------------------------*/
RES_TYPE seatStruc[COMP_COUNT][SEAT_COUNT];



/*-------------------------------------------------------------------*
 *                        FUNCTION PROTOTYPES                        *
 *-------------------------------------------------------------------*/
int main(int, char**);
void prepareScreen(void);
void getPrompt(void);
void invalidStartup(void);
void welcomeScreen(void);
void initSeats(void);
void mainMenu(void);
void makeReservation(void);
void reservationMenu();
void firstClassReservation(void);
void secondClassReservation(void);
void thirdClassReservation(void);
void cancelReservation(void);
void clearReservations(void);
void viewReservations(void);
void invalidOption(void);
void exitMessage(void);



/*-------------------------------------------------------------------*
 *                          FUNCTION: main()                         *
 *-------------------------------------------------------------------*/
int main(int argc, char **argv) {
	char opt;
	BOOL mustContinue = TRUE;

	if (argc > 1) {
		/*This program does not accept any command line args *
		 *to function.  So it terminates the system in case  *
		 *if any such are found.                             */

		invalidStartup();
		return EXIT_FAILURE;
	}

	welcomeScreen();

	do {
		mainMenu();

		fflush(stdin);
		opt = (char)getch();

		switch (opt) {
			case 'm':
			case 'M':
				makeReservation();
				break;
			case 'd':
			case 'D':
				cancelReservation();
				break;
			case 'c':
			case 'C':
				clearReservations();
				break;
			case 'v':
			case 'V':
				viewReservations();
				break;
			case 'h':
			case 'H':
				//helpInformation();
				break;
			case 'x':
			case 'X':
				mustContinue = FALSE;
				break;
			default:
				invalidOption();
				break;
		}
	} while (mustContinue == TRUE);

	exitMessage();
	return EXIT_SUCCESS;
}



/*-------------------------------------------------------------------*
 *                     FUNCTION: prepareScreen()                     *
 *-------------------------------------------------------------------*/
void prepareScreen(void) {
	int ctr;

	/*Set the screen mode to Text Mode with a character matrix of*
	 *80 x 25 so that the screen can be designed properly.       */
	textmode(C80);

	/*Rest of the screen properties are set here.                */
	textcolor(GREEN);
	textbackground(BLACK);
	_setcursortype(_NOCURSOR);
	clrscr();

	/*The horizontal lines of the screen are drawn here.         */
	for (ctr = 3; ctr < 79; ctr++) {
		gotoxy(ctr, 2);
		cprintf("%c", 205);

		gotoxy(ctr, 24);
		cprintf("%c", 205);

		gotoxy(ctr, 22);
		cprintf("%c", 205);
	}

	/*The verticle lines on the screen are drawn here.           */
	for (ctr = 3; ctr < 24; ctr++) {
		gotoxy(2, ctr);
		cprintf("%c", 186);

		gotoxy(79, ctr);
		cprintf("%c", 186);
	}

	/*The four corners are drawn on the screen here.             */
	gotoxy(2, 2);
	cprintf("%c", 201);

	gotoxy(2, 24);
	cprintf("%c", 200);

	gotoxy(79, 2);
	cprintf("%c", 187);

	gotoxy(79, 24);
	cprintf("%c", 188);

	/*The two connectors are drawn here.                         */
	gotoxy(2, 22);
	cprintf("%c", 204);

	gotoxy(79, 22);
	cprintf("%c", 185);

	gotoxy(3, 23);
	cprintf("CMD >>  ");

	/*The static text drawn on the screen giving credits to the  *
	 *developer are done here.                                   */
	textcolor(LIGHTGREEN);

	gotoxy(2, 1);
	cprintf("ICBT HND-32 (2009)");

	gotoxy(64, 1);
	cprintf("Sandeep Ellawala");

	gotoxy(2, 25);
	cprintf("sandeep.ellawala@gmail.com");

	gotoxy(65, 25);
	cprintf("+94(0)774055644");
}



/*-------------------------------------------------------------------*
 *                        FUNCTION: getPrompt()                      *
 *-------------------------------------------------------------------*/
void getPrompt(void) {
	fflush(stdin);

	while (getch() != '\r') {
		; /*NULL statement                                   */
	}
}



/*-------------------------------------------------------------------*
 *                    FUNCTION: invalidStartup()                     *
 *-------------------------------------------------------------------*/
void invalidStartup(void) {
	prepareScreen();

	gotoxy(27, 12);
	textcolor(LIGHTRED);
	cprintf("ERROR: System Startup Error!");

	gotoxy(3, 23);
	cprintf("                                                   ");
	textcolor(YELLOW);
	gotoxy(3, 23);
	cprintf("Press [ENTER] to exit");
	textcolor(YELLOW | BLINK);
	cprintf("... ");

	getPrompt();
}



/*-------------------------------------------------------------------*
 *                    FUNCTION: welcomeScreen()                      *
 *-------------------------------------------------------------------*/
void welcomeScreen(void) {
	prepareScreen();
	textcolor(YELLOW);

	gotoxy(37, 7);
	cprintf("WELCOME");
	gotoxy(37, 8);
	cprintf("-------");

	gotoxy(20, 11);
	cprintf("You are using TrainMaster 1.0v, a software");

	gotoxy(34, 12);
	cprintf("developped by");

	gotoxy(25, 13);
	cprintf("Sandeep Ellawala (HND Batch 32).");

	gotoxy(15, 14);
	cprintf("Please reffer to the help information if you do not");

	gotoxy(26, 15);
	cprintf("know how to use this program.");

	gotoxy(36, 16);
	cprintf("Thank You!");

	gotoxy(3, 23);
	cprintf("Press [ENTER] to continue");

	textcolor(YELLOW | BLINK);
	cprintf("... ");

	getPrompt();
}



/*-------------------------------------------------------------------*
 *                      FUNCTION: initSeats()                        *
 *-------------------------------------------------------------------*/
void initSeats(void) {
	int comp, seat;

	for (comp = 0; comp < COMP_COUNT; comp++) {
		for (seat = 0; seat < SEAT_COUNT; seat++) {
			seatStruc[comp][seat] = NOT_RESERVED;
		}
	}
}



/*-------------------------------------------------------------------*
 *                       FUNCTION: mainMenu()                        *
 *-------------------------------------------------------------------*/
void mainMenu(void) {
	prepareScreen();
	textcolor(WHITE);

	gotoxy(36, 5);
	cprintf("Main Menu");
	gotoxy(36, 6);
	cprintf("---------");

	gotoxy(27, 9);
	cprintf("[M] : Make Reservation");

	gotoxy(27, 11);
	cprintf("[D] : Cancel Reservation");

	gotoxy(27, 13);
	cprintf("[C] : Clear All Reservations");

	gotoxy(27, 15);
	cprintf("[V] : View Reservations");

	gotoxy(27, 17);
	cprintf("[H] : Help Information");

	gotoxy(27, 19);
	cprintf("[X] : Exit System");

	gotoxy(3, 23);
	cprintf("                                                   ");
	gotoxy(3, 23);
	cprintf("CMD");
	textcolor(WHITE | BLINK);
	cprintf(" >> ");
	textcolor(WHITE);
}



/*-------------------------------------------------------------------*
 *                   FUNCTION: makeReservation()                     *
 *-------------------------------------------------------------------*/
void makeReservation(void) {
	char opt;
	BOOL mustContinue = TRUE;

	do {
		reservationMenu();

		fflush(stdin);
		opt = (char)getch();

		switch (opt) {
			case '1':
				firstClassReservation();
				break;
			case '2':
				secondClassReservation();
				break;
			case '3':
				thirdClassReservation();
				break;
			case 'r':
			case 'R':
				mustContinue = FALSE;
				break;
			default:
				invalidOption();
				break;
		}
	} while (mustContinue == TRUE);
}



/*-------------------------------------------------------------------*
 *                   FUNCTION: reservationMenu()                     *
 *-------------------------------------------------------------------*/
void reservationMenu(void) {
	prepareScreen();

	textcolor(WHITE);
	gotoxy(33, 6);
	cprintf("Reservation Menu");
	gotoxy(33, 7);
	cprintf("----------------");

	gotoxy(32, 10);
	cprintf("[1] : First Class");

	gotoxy(32, 12);
	cprintf("[2] : Second Class");

	gotoxy(32, 14);
	cprintf("[3] : Third Class");

	gotoxy(32, 16);
	cprintf("[R] : Return");

	gotoxy(3, 23);
	cprintf("                                                   ");
	gotoxy(3, 23);
	cprintf("CMD ");
	textcolor(WHITE + BLINK);
	cprintf(">> ");
}



/*-------------------------------------------------------------------*
 *                 FUNCTION: firstClassReservation()                 *
 *-------------------------------------------------------------------*/
void firstClassReservation(void) {
	char opt;
	int comp, seat;
	RES_TYPE res = NOT_RESERVED;

	prepareScreen();
	textcolor(WHITE);

	gotoxy(10, 6);
	cprintf("First Class:");
	gotoxy(10, 7);
	cprintf("------------");

	gotoxy(14, 10);
	cprintf("Make reservation            [YES]");
	res = (res | RESERVED);

	gotoxy(14, 12);
	cprintf("Sleeping berth              [YES]");
	res = (res | BERTH);

	gotoxy(14, 15);
	cprintf("Do you want food service? ");

	fflush(stdin);
	opt = (char)getch();

	if (opt == 'y' || opt == 'Y') {
		gotoxy(14, 16);
		cprintf("Food                        [YES]");
		res = (res | FOOD);
	} else {
		gotoxy(14, 16);
		cprintf("Food                         [NO]");
	}

	gotoxy(14, 18);
	cprintf("Compartment: ");
	fflush(stdin);
	scanf("%i", &comp);

	gotoxy(39, 18);
	cprintf("Seat: ");
	fflush(stdin);
	scanf("%i", &seat);

	if (comp <= FIRST_COUNT && comp >= 1) {
		if (seat <= SEAT_COUNT && seat >= 1) {
			if (seatStruc[comp - 1][seat - 1] == NOT_RESERVED) {
				seatStruc[comp - 1][seat - 1] = res;
				gotoxy(57, 21);
				textcolor(LIGHTMAGENTA);
				cprintf("Reservation completed!");
				gotoxy(3, 23);
				textcolor(WHITE);
				cprintf("                                                ");
				gotoxy(3, 23);
				cprintf("Press [ENTER] to continue");
				textcolor(WHITE | BLINK);
				cprintf("...");
				fflush(stdin);
				getPrompt();
			} else {
				gotoxy(59, 21);
				textcolor(LIGHTRED);
				cprintf("Invalid Reservation!");
				gotoxy(3, 23);
				textcolor(WHITE);
				cprintf("                                                ");
				gotoxy(3, 23);
				cprintf("Press [ENTER] to continue");
				textcolor(WHITE | BLINK);
				cprintf("...");
				fflush(stdin);
				getPrompt();
			}
		} else {
			gotoxy(59, 21);
			textcolor(LIGHTRED);
			cprintf("Invalid Reservation!");
			gotoxy(3, 23);
			textcolor(WHITE);
			cprintf("                                                ");
			gotoxy(3, 23);
			cprintf("Press [ENTER] to continue");
			textcolor(WHITE | BLINK);
			cprintf("...");
			fflush(stdin);
			getPrompt();
		}
	} else {
		gotoxy(59, 21);
		textcolor(LIGHTRED);
		cprintf("Invalid Reservation!");
		gotoxy(3, 23);
		textcolor(WHITE);
		cprintf("                                                ");
		gotoxy(3, 23);
		cprintf("Press [ENTER] to continue");
		textcolor(WHITE | BLINK);
		cprintf("...");
		fflush(stdin);
		getPrompt();
	}
}



/*-------------------------------------------------------------------*
 *               FUNCTION: secondClassReservation()                  *
 *-------------------------------------------------------------------*/
void secondClassReservation(void) {
	char opt;
	int comp, seat;
	RES_TYPE res = NOT_RESERVED;

	prepareScreen();
	textcolor(WHITE);

	gotoxy(10, 4);
	cprintf("Second Class:");
	gotoxy(10, 5);
	cprintf("-------------");

	gotoxy(14, 7);
	cprintf("Make Reservation             [YES]");
	res = (res | RESERVED);

	gotoxy(14, 10);
	cprintf("Do you want to reserve a sleeping berth?");
	fflush(stdin);
	opt = (char)getch();

	if (opt == 'y' || opt == 'Y') {
		res = (res | BERTH);
		gotoxy(14, 11);
		cprintf("Sleeping Berth               [YES]");
	} else {
		gotoxy(14, 11);
		cprintf("Sleeping Berth                [NO]");
	}

	gotoxy(14, 14);
	cprintf("Do you want to reserve food?");
	fflush(stdin);
	opt = (char)getch();

	if (opt == 'y' || opt == 'Y') {
		res = (res | FOOD);
		gotoxy(14, 15);
		cprintf("Food                         [YES]");
	} else {
		gotoxy(14, 15);
		cprintf("Food                          [NO]");
	}

	gotoxy(14, 17);
	cprintf("Compartment: ");
	fflush(stdin);
	scanf("%i", &comp);

	gotoxy(39, 17);
	cprintf("Seat: ");
	fflush(stdin);
	scanf("%i", &seat);

	if (comp <= (FIRST_COUNT + SECOND_COUNT) && comp > FIRST_COUNT) {
		if (seat <= SEAT_COUNT && seat >= 1) {
			if (seatStruc[comp - 1][seat - 1] == NOT_RESERVED) {
				seatStruc[comp - 1][seat - 1] = res;
				gotoxy(57, 21);
				textcolor(LIGHTMAGENTA);
				cprintf("Reservation completed!");
				gotoxy(3, 23);
				textcolor(WHITE);
				cprintf("                                                ");
				gotoxy(3, 23);
				cprintf("Press [ENTER] to continue");
				textcolor(WHITE | BLINK);
				cprintf("...");
				fflush(stdin);
				getPrompt();
			} else {
				gotoxy(59, 21);
				textcolor(LIGHTRED);
				cprintf("Invalid Reservation!");
				gotoxy(3, 23);
				textcolor(WHITE);
				cprintf("                                                ");
				gotoxy(3, 23);
				cprintf("Press [ENTER] to continue");
				textcolor(WHITE | BLINK);
				cprintf("...");
				fflush(stdin);
				getPrompt();
			}
		} else {
			gotoxy(59, 21);
			textcolor(LIGHTRED);
			cprintf("Invalid Reservation!");
			gotoxy(3, 23);
			textcolor(WHITE);
			cprintf("                                                ");
			gotoxy(3, 23);
			cprintf("Press [ENTER] to continue");
			textcolor(WHITE | BLINK);
			cprintf("...");
			fflush(stdin);
			getPrompt();
		}
	} else {
		gotoxy(59, 21);
		textcolor(LIGHTRED);
		cprintf("Invalid Reservation!");
		gotoxy(3, 23);
		textcolor(WHITE);
		cprintf("                                                ");
		gotoxy(3, 23);
		cprintf("Press [ENTER] to continue");
		textcolor(WHITE | BLINK);
		cprintf("...");
		fflush(stdin);
		getPrompt();
	}
}



/*-------------------------------------------------------------------*
 *                 FUNCTION: thirdClassReservation()                 *
 *-------------------------------------------------------------------*/
void thirdClassReservation(void) {
	char opt;
	int comp, seat;
	RES_TYPE res = NOT_RESERVED;

	prepareScreen();
	textcolor(WHITE);

	gotoxy(10, 6);
	cprintf("Third Class:");
	gotoxy(10, 7);
	cprintf("------------");

	gotoxy(14, 10);
	cprintf("Make reservation            [YES]");
	res = (res | RESERVED);

	gotoxy(14, 12);
	cprintf("Sleeping berth               [NO]");

	gotoxy(14, 15);
	cprintf("Do you want food service? ");

	fflush(stdin);
	opt = (char)getch();

	if (opt == 'y' || opt == 'Y') {
		gotoxy(14, 16);
		cprintf("Food                        [YES]");
		res = (res | FOOD);
	} else {
		gotoxy(14, 16);
		cprintf("Food                         [NO]");
	}

	gotoxy(14, 18);
	cprintf("Compartment: ");
	fflush(stdin);
	scanf("%i", &comp);

	gotoxy(39, 18);
	cprintf("Seat: ");
	fflush(stdin);
	scanf("%i", &seat);

	if (comp <= COMP_COUNT && comp > (FIRST_COUNT + SECOND_COUNT)) {
		if (seat <= SEAT_COUNT && seat >= 1) {
			if (seatStruc[comp - 1][seat - 1] == NOT_RESERVED) {
				seatStruc[comp - 1][seat - 1] = res;
				gotoxy(57, 21);
				textcolor(LIGHTMAGENTA);
				cprintf("Reservation completed!");
				gotoxy(3, 23);
				textcolor(WHITE);
				cprintf("                                                ");
				gotoxy(3, 23);
				cprintf("Press [ENTER] to continue");
				textcolor(WHITE | BLINK);
				cprintf("...");
				fflush(stdin);
				getPrompt();
			} else {
				gotoxy(59, 21);
				textcolor(LIGHTRED);
				cprintf("Invalid Reservation!");
				gotoxy(3, 23);
				textcolor(WHITE);
				cprintf("                                                ");
				gotoxy(3, 23);
				cprintf("Press [ENTER] to continue");
				textcolor(WHITE | BLINK);
				cprintf("...");
				fflush(stdin);
				getPrompt();
			}
		} else {
			gotoxy(59, 21);
			textcolor(LIGHTRED);
			cprintf("Invalid Reservation!");
			gotoxy(3, 23);
			textcolor(WHITE);
			cprintf("                                                ");
			gotoxy(3, 23);
			cprintf("Press [ENTER] to continue");
			textcolor(WHITE | BLINK);
			cprintf("...");
			fflush(stdin);
			getPrompt();
		}
	} else {
		gotoxy(59, 21);
		textcolor(LIGHTRED);
		cprintf("Invalid Reservation!");
		gotoxy(3, 23);
		textcolor(WHITE);
		cprintf("                                                ");
		gotoxy(3, 23);
		cprintf("Press [ENTER] to continue");
		textcolor(WHITE | BLINK);
		cprintf("...");
		fflush(stdin);
		getPrompt();
	}
}



/*-------------------------------------------------------------------*
 *                 FUNCTION: cancelReservation()                     *
 *-------------------------------------------------------------------*/
void cancelReservation(void) {
	int comp, seat;

	prepareScreen();
	textcolor(WHITE);

	gotoxy(10, 8);
	cprintf("Cancel Reservaton:");
	gotoxy(10, 9);
	cprintf("------------------");

	gotoxy(14, 12);
	cprintf("Compartment number: ");
	fflush(stdin);
	scanf("%i", &comp);

	gotoxy(14, 14);
	cprintf("       Seat number: ");
	fflush(stdin);
	scanf("%i", &seat);

	if (comp >= 1 && comp <= COMP_COUNT) {
		if (seat >= 1 && seat <= SEAT_COUNT) {
			if (seatStruc[comp - 1][seat - 1] != NOT_RESERVED) {
				seatStruc[comp - 1][seat - 1] = NOT_RESERVED;
				gotoxy(45, 21);
				textcolor(LIGHTMAGENTA);
				cprintf("Reservation Canceled Successfully!");
			} else {
				gotoxy(62, 21);
				textcolor(LIGHTRED);
				cprintf("Operation Failed!");
			}
		} else {
			gotoxy(62, 21);
			textcolor(LIGHTRED);
			cprintf("Operation failed!");
		}
	} else {
		gotoxy(62, 21);
		textcolor(LIGHTRED);
		cprintf("Operation failed!");
	}

	gotoxy(3, 23);
	cprintf("                                                   ");
	gotoxy(3, 23);
	textcolor(WHITE);
	cprintf("Press [ENTER] to continue");
	textcolor(WHITE | BLINK);
	cprintf("... ");

	getPrompt();
}



/*-------------------------------------------------------------------*
 *                   FUNCTION: clearReservations()                   *
 *-------------------------------------------------------------------*/
void clearReservations(void) {
	char opt;
	prepareScreen();

	gotoxy(12, 12);
	textcolor(LIGHTRED);
	cprintf("WARNING: Are you sure you want to cancel all reservations?");

	gotoxy(3, 23);
	cprintf("                                                   ");
	gotoxy(3, 23);
	textcolor(WHITE);
	cprintf("CMD ");
	textcolor(WHITE + BLINK);
	cprintf(">> ");

	fflush(stdin);
	opt = (char)getch();

	if (opt == 'y' || opt == 'Y') {
		initSeats();

		prepareScreen();
		gotoxy(21, 12);
		cprintf("All reservations canceled successfully!");
	}

	gotoxy(3, 23);
	cprintf("                                                   ");
	gotoxy(3, 23);
	textcolor(WHITE);
	cprintf("Press [ENTER] to continue");
	textcolor(WHITE | BLINK);
	cprintf("...");

	getPrompt();
}



/*-------------------------------------------------------------------*
 *                   FUNCTION: viewReservations()                    *
 *-------------------------------------------------------------------*/
void viewReservations(void) {
	int x, y, ctr;

	prepareScreen();
	gotoxy(14, 3);
	textcolor(LIGHTGREEN);
	cprintf("1st Class -> ");
	textcolor(LIGHTCYAN);
	cprintf("%c", 219);

	textcolor(LIGHTGREEN);
	cprintf("      2nd Class -> ");
	textcolor(YELLOW);
	cprintf("%c", 219);

	textcolor(LIGHTGREEN);
	cprintf("      3rd Class -> ");
	textcolor(WHITE);
	cprintf("%c", 219);

	textcolor(LIGHTGREEN);
	gotoxy(12, 4);
	cprintf("[-] Not Reserved      [X] Reserved      [*] Reserved+");
	cprintf("Berth");
	gotoxy(18, 5);
	cprintf("[#] Reserved+Food     [$] Reserved+Food");
	cprintf("+Berth");

	textcolor(LIGHTRED);

	for (y = 0; y < COMP_COUNT; y++) {
		gotoxy(15, y + 7);
		cprintf("%02i", y + 1);
	}

	for (x = 18, ctr = 0; ctr < SEAT_COUNT; ctr++, x += 3) {
		gotoxy(x, 6);
		cprintf("%02i", ctr + 1);
	}

	for (y= 0; y < COMP_COUNT; y++) {
		if (y < FIRST_COUNT) {
			textcolor(LIGHTCYAN);
		} else if (y < (FIRST_COUNT + SECOND_COUNT)) {
			textcolor(YELLOW);
		} else {
			textcolor(WHITE);
		}

		for (ctr = 0, x = 19; ctr < SEAT_COUNT; ctr++, x+= 3) {
			gotoxy(x, y+ 7);
			switch (seatStruc[y][ctr]) {
				case (NOT_RESERVED):
					cprintf("-");
					break;
				case (RESERVED):
					cprintf("x");
					break;
				case (RESERVED | BERTH):
					cprintf("*");
					break;
				case (RESERVED | FOOD):
					cprintf("#");
					break;
				case (RESERVED | BERTH | FOOD):
					cprintf("$");
					break;
			}
		}
	}

	textcolor(YELLOW);
	gotoxy(3, 23);
	cprintf("Press [ENTER] to continue");
	textcolor(YELLOW | BLINK);
	cprintf("...");

	getPrompt();
}



/*-------------------------------------------------------------------*
 *                     FUNCTION: invalidOption()                     *
 *-------------------------------------------------------------------*/
void invalidOption(void) {
	prepareScreen();

	textcolor(LIGHTRED);
	gotoxy(30, 12);
	cprintf("ERROR: Invalid Option!");

	textcolor(YELLOW);
	gotoxy(3, 23);
	cprintf("                                                    ");
	gotoxy(3, 23);
	cprintf("Press [ENTER] to continue");

	textcolor(YELLOW + BLINK);
	cprintf("...");

	getPrompt();
}



/*-------------------------------------------------------------------*
 *                      FUNCTION: exitMessage()                      *
 *-------------------------------------------------------------------*/
void exitMessage(void) {
	prepareScreen();

	textcolor(YELLOW);
	gotoxy(22, 12);
	cprintf("Thank you for using TrainMaster 1.0v!");

	gotoxy(3, 23);
	cprintf("                                                   ");
	gotoxy(3, 23);
	cprintf("Press [ENTER] to exit");
	textcolor(YELLOW | BLINK);
	cprintf("...");

	getPrompt();
}
