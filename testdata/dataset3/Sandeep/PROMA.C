/*=========================================================*
 *SOURCE NAME	:   proma.c                                *
 *AUTHOR        :   Sandeep Ellawala                       *
 *DATE          :   29-10-2007                             *
 *PLATFORM      :   Microsoft Windows XP - SP 2.0          *
 *		    Borlan Turbo C++ 3.0                   *
 *NOTE		:   This source file contains complete code*
 *		    for a simple and classic product order *
 *		    system I presented for the programming *
 *		    project C1005.                         *
 *=========================================================*/

/*---------------------------------------------------------*
 *                   HEADER INCLUSIONS                     *
 *---------------------------------------------------------*/

# include <dos.h>
# include <stdio.h>
# include <conio.h>
# include <stdlib.h>
# include <string.h>

/*---------------------------------------------------------*
 *                 CONSTANT DEFINITIONS                    *
 *---------------------------------------------------------*/

# define ARGS_EXPECTED				1

# define PROG_NAME				0

# define NO_EXIT				0
# define IS_EXIT				1

# define NO_LOGGED				0
# define IS_LOGGED				1

# define INVALID_LOGINS				3

# define HR_CHAR			      196
# define VR_CHAR			      179
# define TL_CHAR			      218
# define TR_CHAR			      191
# define BL_CHAR			      192
# define BR_CHAR			      217

# define PROMPT_CHAR			  '\r'

# define PASSWD				"1234"

# define ORD_FILE		"ordfile.txt"
# define PRD_FILE		"prdfile.txt"
# define TMP_FILE		"tmpfile.txt"
# define TMP_FILE_X	      "tempfilex.txt"

# define REC_INVAL				0
# define REC_VALID				1

# define CODE_LENGTH				4
# define NAME_LENGTH			       15
# define DESC_LENGTH			       25

# define ESC_ASCII			       27

/*---------------------------------------------------------*
 *                   FUNCTION PROTOTYPES                   *
 *---------------------------------------------------------*/

int main(int, char**);
void prepare_screen(void);
void get_prompt(void);
void invalid_startup(char*);
void welcome_screen(void);
int login_prompt(void);
void invalid_login(void);
void main_menu(void);
void add_product(void);
void view_product(void);
void edit_product(void);
void reorder_product(void);
void place_order(void);
void cancel_order(void);
void change_order(void);
void view_order(void);
int confirm_exit(void);
void invalid_option(void);
void exit_screen(void);

/*---------------------------------------------------------*
 *                          main()                         *
 *---------------------------------------------------------*/

int main(int argc, char *argv[])
{
	char menuOpt;
	int isExit;
	int isLogged;
	int logCtr;

	/*This programe does not expect command line arguments
	 of any kind.  In case if any are passed, the following
	 block of code takes care of it.                       */

	if (argc != ARGS_EXPECTED)
	{
		invalid_startup(argv[PROG_NAME]);
		return EXIT_FAILURE;
	}

	/*If this portion of the program is reached at the run
	  time, then it is reasonable to expect that the user
	  has started the program with correct syntax.         */

	welcome_screen();

	/*Following flag assignments are done to note the state
	  of the programe at the beginning of the main loop.   */

	isLogged = NO_LOGGED;
	isExit = NO_EXIT;
	logCtr = 0;

	/*Prior to entering the main loop, a loop is used to
	  give password authentication to acess the program.   */

	while (isLogged == NO_LOGGED && isExit == NO_EXIT)
	{
		/*In the first execution of a session, this part of
		  the code is reached automatically due to the flag
		  settings done above.                             */

		isLogged = login_prompt();

		if (isLogged == NO_LOGGED)
		{
			/*A counter is used to keep track of the number
			  of attempts taken to get in to programe with
			  no authenticated password.                   */
			logCtr++;
		}

		if (logCtr == INVALID_LOGINS)
		{
			/*If the number of failed attempts to get in to
			  the system exceeds the limit allowed, then it
			  sets relevant flags to close the programe.   */
			invalid_login();
			isExit = IS_EXIT;
		}
	}

	while (isExit != IS_EXIT)
	{
		/*As the programe reaches this part of the code in
		  the run time, it is assured that the poper login
		  password is provided.                            */

		main_menu();

		fflush(stdin);
		menuOpt = getch();

		switch (menuOpt)
		{
			case '1':
				add_product();
				break;
			case '2':
				view_product();
				break;
			case '3':
				edit_product();
				break;
			case '4':
				reorder_product();
				break;
			case '5':
				place_order();
				break;
			case '6':
				cancel_order();
				break;
			case '7':
				change_order();
				break;
			case '8':
				view_order();
				break;
			case '9':
				isExit = confirm_exit();
				break;
			default:
				invalid_option();
				break;
		}
	}

	/*As the programe reaches this portion of the source
	  file, it is assured that either he has provided an
	  invalid password at the startup, or he has decided to
	  close the programe at the main menu.                 */

	exit_screen();

	return EXIT_SUCCESS;
}

/*---------------------------------------------------------*
 *                     prepare_screen()                    *
 *---------------------------------------------------------*/

void prepare_screen(void)
{
	/*This is one of the two functions that are called the
	  most through out the programe in all functions that
	  does screen out put.  It draws a box on the screen,
	  prepares the screen for out put by clearing it.      */

	int ctr;

	/*The following line assures that the screen is always
	  with 25 raws and 80 columns for a fixed out put.     */

	textmode(C80);
	textcolor(GREEN);
	clrscr();
	_setcursortype(_NOCURSOR);

	/*The following loop draws two lines representing the
	  top and the bottom of a box that margines the screen
	  out put.                                             */

	for (ctr = 2; ctr < 80; ctr++)
	{
		gotoxy(ctr, 2);
		cprintf("%c", HR_CHAR);
		gotoxy(ctr, 24);
		cprintf("%c", HR_CHAR);
	}

	/*The following loop draws two lines representing the
	  right and the left of a box that margines the screen
	  out put.                                             */

	for (ctr = 3; ctr < 24; ctr++)
	{
		gotoxy(2, ctr);
		cprintf("%c", VR_CHAR);
		gotoxy(79, ctr);
		cprintf("%c", VR_CHAR);
	}

	/*The corners of the box are drawn in the section below
	  for a margine of out put.                            */

	gotoxy(2, 2);
	cprintf("%c", TL_CHAR);
	gotoxy(79, 2);
	cprintf("%c", TR_CHAR);
	gotoxy(2, 24);
	cprintf("%c", BL_CHAR);
	gotoxy(79, 24);
	cprintf("%c", BR_CHAR);

	/*Copyright messages are displaye in the following code
	  to give more professional screen property to this
	  program.                                             */

	textcolor(LIGHTGREEN);

	gotoxy(29, 2);
	cprintf("< Phantom Software >");
	gotoxy(28, 24);
	cprintf("< Sandeep Ellawala >");

	_setcursortype(_NORMALCURSOR);
	textcolor(WHITE);
}

/*---------------------------------------------------------*
 *                       get_prompt()                      *
 *---------------------------------------------------------*/

void get_prompt(void)
{
	_setcursortype(_NOCURSOR);

	while (getch() != PROMPT_CHAR)
	{
		/*looped till the proper character (ie. Enter) is
		  pressed.                                         */
		;
	}

	_setcursortype(_NORMALCURSOR);
}

/*---------------------------------------------------------*
 *                  invalid_startup()                      *
 *---------------------------------------------------------*/

void invalid_startup(char *progName)
{
	int xCoord = (40 - ((strlen(progName)) / 2) - 1);

	prepare_screen();
	textcolor(LIGHTGREEN);

	gotoxy(36, 8);
	cprintf("ERROR!");
	gotoxy(36, 9);
	cprintf("------");
	gotoxy(26, 12);
	cprintf("Programe Startup Error in,");
	gotoxy(xCoord, 14);
	cprintf("%s", progName);

	textcolor(LIGHTGREEN);

	gotoxy(69, 23);
	cprintf("[");
	gotoxy(78, 23);
	cprintf("]");

	textcolor(LIGHTGREEN + BLINK);

	gotoxy(70, 23);
	cprintf("Continue");

	textcolor(LIGHTRED + BLINK);

	gotoxy(26, 18);
	cprintf("<< PROGRAM TERMINATED! >>");

	get_prompt();

	textcolor(LIGHTGREEN);
}

/*---------------------------------------------------------*
 *                     welcome_screen()                    *
 *---------------------------------------------------------*/

void welcome_screen(void)
{
	prepare_screen();
	textcolor(LIGHTGREEN);

	gotoxy(32, 7);
	cprintf("PRODUCT MASTER");
	gotoxy(26, 10);
	cprintf("Product Reservation System");
	gotoxy(38, 13);
	cprintf("by");
	gotoxy(30, 16);
	cprintf("Sandeep Ellawala");
	gotoxy(3, 3);
	cprintf("[T3-2007]");
	gotoxy(73, 3);
	cprintf("[1.0v]");
	gotoxy(69, 23);
	cprintf("[");
	gotoxy(78, 23);
	cprintf("]");

	textcolor(LIGHTGREEN + BLINK);

	gotoxy(70, 23);
	cprintf("Continue");
	get_prompt();

	textcolor(LIGHTGREEN);
}

/*---------------------------------------------------------*
 *                      login_prompt()                     *
 *---------------------------------------------------------*/

int login_prompt(void)
{
	/*This password function can be used for any password
	  of a variable length.  It currently uses a hard coded
	  password while it can be improved to read a file for
	  the password.                                        */

	char opt;
	int ctr;
	int xCoord = (40 - ((strlen(PASSWD)) / 2) - 1);
	char *passwd = malloc(strlen(PASSWD));
	char *tmp = passwd;

	prepare_screen();
	textcolor(LIGHTGREEN);

	gotoxy(33, 8);
	cprintf("LOGIN PROMPT");
	gotoxy(33, 9);
	cprintf("------------");
	gotoxy(xCoord - 1, 14);
	cprintf("[");
	gotoxy(xCoord + strlen(PASSWD), 14);
	cprintf("]");

	textcolor(LIGHTRED);
	_setcursortype(_NOCURSOR);

	for (ctr = 0; ctr < strlen(PASSWD); ctr++)
	{
		*tmp = getch();
		tmp++;
		gotoxy(xCoord + ctr, 14);
		cprintf("*");
	}

	*tmp = '\0';

	textcolor(LIGHTGREEN);

	gotoxy(62, 23);
	cprintf("[");
	gotoxy(78, 23);
	cprintf("]");
	gotoxy(3, 23);
	cprintf("[");
	gotoxy(15, 23);
	cprintf("]");

	textcolor(LIGHTGREEN + BLINK);

	gotoxy(63, 23);
	cprintf("Enter: Continue");
	gotoxy(4, 23);
	cprintf("Esc: Cancel");

	do
	{
		opt = getch();
	} while (opt != PROMPT_CHAR && (int)opt != ESC_ASCII);

	if ((int)opt == ESC_ASCII)
	{
		return NO_LOGGED;
	}

	if ((strcmp(passwd, PASSWD)) == 0)
	{
		return IS_LOGGED;
	}

	return NO_LOGGED;
}

/*---------------------------------------------------------*
 *                     invalid_login()                     *
 *---------------------------------------------------------*/

void invalid_login(void)
{
	prepare_screen();
	textcolor(LIGHTRED);

	gotoxy(25, 12);
	cprintf("<< AUTHENTICATION  ERROR! >>");

	textcolor(LIGHTGREEN);

	gotoxy(69, 23);
	cprintf("[");
	gotoxy(78, 23);
	cprintf("]");

	textcolor(LIGHTGREEN + BLINK);

	gotoxy(70, 23);
	cprintf("Continue");
	get_prompt();
}

/*---------------------------------------------------------*
 *                        main_menu()                      *
 *---------------------------------------------------------*/

void main_menu(void)
{
	prepare_screen();
	textcolor(LIGHTGREEN);

	gotoxy(32, 4);
	cprintf("PRODUCT MASTER");
	gotoxy(34, 6);
	cprintf("Main  Menu");
	gotoxy(34, 7);
	cprintf("----------");
	gotoxy(25, 9);
	cprintf("#   Product");
	gotoxy(25, 10);
	cprintf("    1. Add Product");
	gotoxy(25, 11);
	cprintf("    2. View Products");
	gotoxy(25, 12);
	cprintf("    3. Edit Product");
	gotoxy(25, 13);
	cprintf("    4. Re-order Products");
	gotoxy(25, 15);
	cprintf("#   Orders");
	gotoxy(25, 16);
	cprintf("    5. Place Order");
	gotoxy(25, 17);
	cprintf("    6. Cancel an Order");
	gotoxy(25, 18);
	cprintf("    7. Change an Order");
	gotoxy(25, 19);
	cprintf("    8. View Orders");
	gotoxy(25, 21);
	cprintf("    9. Exit");
	gotoxy(3, 23);
	cprintf("Enter your choice[1 - 9]: ");
}

/*---------------------------------------------------------*
 *                       add_product()                     *
 *---------------------------------------------------------*/

void add_product(void)
{
	FILE *fp;
	char proCode[CODE_LENGTH + 1];
	char proName[NAME_LENGTH + 1];
	char proDesc[DESC_LENGTH + 1];
	float uPrice;
	int uAvailable;
	int uLevel;
	int opt;
	int isValid;
	char code[CODE_LENGTH + 1];
	char name[NAME_LENGTH + 1];
	char desc[DESC_LENGTH + 1];
	float price;
	int available;
	int level;

	prepare_screen();
	textcolor(LIGHTGREEN);

	gotoxy(31, 7);
	cprintf("Add New Product");
	gotoxy(31, 8);
	cprintf("---------------");
	gotoxy(5, 10);
	cprintf("Product Code        : ");
	gotoxy(5, 12);
	cprintf("Product Name        : ");
	gotoxy(5, 14);
	cprintf("Product Description : ");
	gotoxy(5, 16);
	cprintf("Unit Price          : ");
	gotoxy(5, 18);
	cprintf("Units Available     : ");
	gotoxy(5, 20);
	cprintf("Re-order Level      : ");
	gotoxy(27, 10);
	fflush(stdin);
	gets(code);
	gotoxy(27, 12);
	fflush(stdin);
	gets(name);
	gotoxy(27, 14);
	fflush(stdin);
	gets(desc);
	gotoxy(27, 16);
	fflush(stdin);
	scanf("%f", &price);
	gotoxy(27, 18);
	fflush(stdin);
	scanf("%i", &available);
	gotoxy(27, 20);
	fflush(stdin);
	scanf("%i", &level);

	isValid = REC_VALID;

	/*The product code of the new record is checked with
	  the records currently in the file.  No duplicate
	  product codes are allowed.                           */

	if ((fp = fopen(PRD_FILE, "r")) != NULL)
	{
		while (!(feof(fp)))
		{
			fscanf(fp, "%[^/]%*c%[^/]%*c%[^/]%*c%f %i %i%*c",
				proCode, proName, proDesc, &uPrice, &uAvailable,
				&uLevel);

			if (feof(fp))
			{
				break;
			}

			if ((strcmp(proCode, code)) == 0)
			{
				isValid = REC_INVAL;
			}
		}

		fclose(fp);
	}

	if (isValid == REC_VALID)
	{
		/*This part of the code is reached only if the new
		  record is soundly valid.                         */

		textcolor(LIGHTGREEN);

		gotoxy(62, 23);
		cprintf("[");
		gotoxy(78, 23);
		cprintf("]");
		gotoxy(3, 23);
		cprintf("[");
		gotoxy(15, 23);
		cprintf("]");

		textcolor(LIGHTGREEN + BLINK);

		gotoxy(63, 23);
		cprintf("Enter: Continue");
		gotoxy(4, 23);
		cprintf("Esc: Cancel");

		do
		{
			opt = getch();
		} while (opt != PROMPT_CHAR && (int)opt != ESC_ASCII);

		if (opt == PROMPT_CHAR)
		{
			fp = fopen(PRD_FILE, "a+");

			fprintf(fp, "%s/%s/%s/%.2f %i %i\n", code, name,
				desc, price, available, level);

			fflush(fp);
			fclose(fp);
		}
	}
	else
	{
		prepare_screen();
		textcolor(LIGHTRED);

		gotoxy(28, 12);
		cprintf("<< Invalid  Record! >>");

		textcolor(LIGHTGREEN);
		gotoxy(69, 23);
		cprintf("[");
		gotoxy(78, 23);
		cprintf("]");

		textcolor(LIGHTGREEN + BLINK);

		gotoxy(70, 23);
		cprintf("Continue");
		get_prompt();

		textcolor(LIGHTGREEN);
	}
}

/*---------------------------------------------------------*
 *                     view_product()                      *
 *---------------------------------------------------------*/

void view_product(void)
{
	FILE *fp;
	char code[CODE_LENGTH + 1];
	char name[NAME_LENGTH + 1];
	char desc[DESC_LENGTH + 1];
	float price;
	int available;
	int level;
	int ctr;
	int isValid = REC_VALID;
	int xCoord;

	if ((fp = fopen(PRD_FILE, "r")) == NULL)
	{
		isValid = REC_INVAL;
	}
	else
	{
		ctr = 0;

		while (!(feof(fp)))
		{
			fscanf(fp, "%[^/]%*c%[^/]%*c%[^/]%*c%f %i %i%*c", code,
				name, desc, &price, &available, &level);

			if (feof(fp))
			{
				break;
			}

			if (ctr == 0)
			{
				prepare_screen();
				textcolor(LIGHTGREEN);

				gotoxy(3, 3);
				cprintf("CODE");
				gotoxy(3, 4);
				cprintf("----");
				gotoxy(8, 3);
				cprintf("     NAME");
				gotoxy(8, 4);
				cprintf("---------------");
				gotoxy(74, 3);
				cprintf("LEVEL");
				gotoxy(74, 4);
				cprintf("-----");
				gotoxy(67, 3);
				cprintf("AMOUNT");
				gotoxy(67, 4);
				cprintf("------");
				gotoxy(58, 3);
				cprintf(" PRICE");
				gotoxy(58, 4);
				cprintf("-------");
				gotoxy(24, 3);
				cprintf("          DESCRIPTION");
				gotoxy(24, 4);
				cprintf("-------------------------------");
				ctr = 6;
			}

			gotoxy(3, ctr);
			cprintf("%4s", code);
			xCoord = (((15 - strlen(name)) / 2) + 8);
			gotoxy(xCoord, ctr);
			cprintf("%s", name);
			xCoord = (((32 - strlen(desc)) / 2) + 24);
			gotoxy(xCoord, ctr);
			cprintf("%s", desc);
			gotoxy(58, ctr);
			cprintf("%7.2f", price);
			gotoxy(68, ctr);
			cprintf("%04i", available);
			gotoxy(76, ctr);

			if (available < level)
			{
				cprintf("X");
			}
			else
			{
				cprintf("-");
			}

			ctr += 2;

			if (ctr > 22)
			{
				ctr = 0;

				textcolor(LIGHTGREEN);

				gotoxy(69, 23);
				cprintf("[");
				gotoxy(78, 23);
				cprintf("]");

				textcolor(LIGHTGREEN + BLINK);

				gotoxy(70, 23);
				cprintf("Continue");
				get_prompt();

				textcolor(LIGHTGREEN);
			} 
		}

		textcolor(LIGHTGREEN);

		gotoxy(69, 23);
		cprintf("[");
		gotoxy(78, 23);
		cprintf("]");

		textcolor(LIGHTGREEN + BLINK);

		gotoxy(70, 23);
		cprintf("Continue");
		get_prompt();

		textcolor(LIGHTGREEN);
	}

	if (isValid == REC_INVAL)
	{
		prepare_screen();
		textcolor(LIGHTRED);

		gotoxy(27, 10);
		cprintf("NO RECORDS ARE CURRENTLY");
		gotoxy(34, 14);
		cprintf("AVAILABLE!");

		textcolor(LIGHTGREEN);

		gotoxy(69, 23);
		cprintf("[");
		gotoxy(78, 23);
		cprintf("]");

		textcolor(LIGHTGREEN + BLINK);

		gotoxy(70, 23);
		cprintf("Continue");
		get_prompt();

		textcolor(LIGHTGREEN);
	}
}

/*---------------------------------------------------------*
 *                    reorder_product()                    *
 *---------------------------------------------------------*/

void reorder_product(void)
{
	FILE *fp;
	char code[CODE_LENGTH + 1];
	char name[NAME_LENGTH + 1];
	char desc[DESC_LENGTH + 1];
	float price;
	int available;
	int level;
	int ctr;
	int isValid = REC_VALID;
	int xCoord;

	if ((fp = fopen(PRD_FILE, "r")) == NULL)
	{
		isValid = REC_INVAL;
	}
	else
	{
		ctr = 0;

		while (!(feof(fp)))
		{
			fscanf(fp, "%[^/]%*c%[^/]%*c%[^/]%*c%f %i %i%*c", code,
				name, desc, &price, &available, &level);

			if (feof(fp))
			{
				break;
			}

			if (available < level)
			{
				if (ctr == 0)
				{
					prepare_screen();
					textcolor(LIGHTGREEN);

					gotoxy(3, 3);
					cprintf("CODE");
					gotoxy(3, 4);
					cprintf("----");
					gotoxy(8, 3);
					cprintf("     NAME");
					gotoxy(8, 4);
					cprintf("---------------");
					gotoxy(74, 3);
					cprintf("LEVEL");
					gotoxy(74, 4);
					cprintf("-----");
					gotoxy(67, 3);
					cprintf("AMOUNT");
					gotoxy(67, 4);
					cprintf("------");
					gotoxy(58, 3);
					cprintf(" PRICE");
					gotoxy(58, 4);
					cprintf("-------");
					gotoxy(24, 3);
					cprintf("          DESCRIPTION");
					gotoxy(24, 4);
					cprintf("-------------------------------");
					ctr = 6;
				}

				gotoxy(3, ctr);
				cprintf("%4s", code);
				xCoord = (((15 - strlen(name)) / 2) + 8);
				gotoxy(xCoord, ctr);
				cprintf("%s", name);
				xCoord = (((32 - strlen(desc)) / 2) + 24);
				gotoxy(xCoord, ctr);
				cprintf("%s", desc);
				gotoxy(58, ctr);
				cprintf("%7.2f", price);
				gotoxy(68, ctr);
				cprintf("%04i", available);
				gotoxy(76, ctr);
				cprintf("X");

				ctr += 2;

				if (ctr > 22)
				{
					ctr = 0;

					textcolor(LIGHTGREEN);

					gotoxy(69, 23);
					cprintf("[");
					gotoxy(78, 23);
					cprintf("]");

					textcolor(LIGHTGREEN + BLINK);

					gotoxy(70, 23);
					cprintf("Continue");
					get_prompt();

					textcolor(LIGHTGREEN);
				}
			} 
		}

		textcolor(LIGHTGREEN);

		gotoxy(69, 23);
		cprintf("[");
		gotoxy(78, 23);
		cprintf("]");

		textcolor(LIGHTGREEN + BLINK);

		gotoxy(70, 23);
		cprintf("Continue");
		get_prompt();    
	}

	if (isValid == REC_INVAL)
	{
		prepare_screen();
		textcolor(LIGHTRED);

		gotoxy(27, 10);
		cprintf("NO RECORDS ARE CURRENTLY");
		gotoxy(34, 14);
		cprintf("AVAILABLE!");

		textcolor(LIGHTGREEN);

		gotoxy(69, 23);
		cprintf("[");
		gotoxy(78, 23);
		cprintf("]");

		textcolor(LIGHTGREEN + BLINK);

		gotoxy(70, 23);
		cprintf("Continue");
		get_prompt();

		textcolor(LIGHTGREEN);
	}
}

/*---------------------------------------------------------*
 *                    edit_product()                       *
 *---------------------------------------------------------*/

void edit_product(void)
{
	FILE *fpDat;
	FILE *fpTmp;
	char edCode[CODE_LENGTH + 1];
	char code[CODE_LENGTH + 1];
	char name[NAME_LENGTH + 1];
	char desc[DESC_LENGTH + 1];
	float price;
	int available;
	int level;
	char nName[NAME_LENGTH + 1];
	char nDesc[DESC_LENGTH + 1];
	float nPrice;
	int nAvailable;
	int nLevel;
	int isValid;
	int opt;

	prepare_screen();
	textcolor(LIGHTGREEN);

	gotoxy(30, 8);
	cprintf("EDIT PRODUCT ITEM");
	gotoxy(30, 9);
	cprintf("-----------------");
	gotoxy(31, 14);
	cprintf("Enter Product Code:");
	gotoxy(51, 14);
	fflush(stdin);
	gets(edCode);

	isValid = REC_INVAL;

	if ((fpDat = fopen(PRD_FILE, "r")) != NULL)
	{
		fpTmp = fopen(TMP_FILE, "w");

		while (!(feof(fpDat)))
		{
			fscanf(fpDat, "%[^/]%*c%[^/]%*c%[^/]%*c%f %i %i%*c", code, name,
				desc, &price, &available, &level);

			if (feof(fpDat))
			{
				break;
			}

			if ((strcmp(edCode, code)) == 0)
			{
				isValid = REC_VALID;

				prepare_screen();
				textcolor(LIGHTGREEN);

				gotoxy(30, 8);
				cprintf("EDIT PRODUCT ITEM");
				gotoxy(30, 9);
				cprintf("-----------------");
				gotoxy(5, 11);
				cprintf("Product Code        :");
				gotoxy(5, 13);
				cprintf("Product Name        :");
				gotoxy(5, 15);
				cprintf("Product Description :");
				gotoxy(5, 17);
				cprintf("Unit Price          :");
				gotoxy(5, 19);
				cprintf("Units Available     :");
				gotoxy(5, 21);
				cprintf("Re-order Level      :");
				gotoxy(27, 11);
				printf("%s", code);
				gotoxy(27, 13);
				fflush(stdin);
				gets(nName);
				gotoxy(27, 15);
				fflush(stdin);
				gets(nDesc);
				gotoxy(27, 17);
				fflush(stdin);
				scanf("%f", &nPrice);
				gotoxy(27, 19);
				fflush(stdin);
				scanf("%i", &nAvailable);
				gotoxy(27, 21);
				fflush(stdin);
				scanf("%i", &nLevel);

				textcolor(LIGHTGREEN);

				gotoxy(62, 23);
				cprintf("[");
				gotoxy(78, 23);
				cprintf("]");
				gotoxy(3, 23);
				cprintf("[");
				gotoxy(15, 23);
				cprintf("]");

				textcolor(LIGHTGREEN + BLINK);

				gotoxy(63, 23);
				cprintf("Enter: Continue");
				gotoxy(4, 23);
				cprintf("Esc: Cancel");

				do
				{
					opt = getch();
				} while (opt != PROMPT_CHAR && (int)opt != ESC_ASCII);

				if (opt == PROMPT_CHAR)
				{
					fprintf(fpTmp, "%s/%s/%s/%.2f %i %i\n", 
						code, nName, nDesc, nPrice, nAvailable, nLevel);
				}
				else
				{
					fprintf(fpTmp, "%s/%s/%s/%.2f %i %i\n", 
						code, name, desc, price, available, level);
				}
			}
			else
			{
				fprintf(fpTmp, "%s/%s/%s/%.2f %i %i\n", 
						code, name, desc, price, available, level);
			}
		}

		fflush(fpTmp);
		fclose(fpTmp);
		fclose(fpDat);
	}

	if (isValid == REC_VALID)
	{
		remove(PRD_FILE);
		rename(TMP_FILE, PRD_FILE);
	}
	else
	{
		remove(TMP_FILE);

		prepare_screen();
		textcolor(LIGHTRED);

		gotoxy(28, 12);
		cprintf("<< Invalid Record! >>");

		textcolor(LIGHTGREEN);

		gotoxy(69, 23);
		cprintf("[");
		gotoxy(78, 23);
		cprintf("]");

		textcolor(LIGHTGREEN + BLINK);

		gotoxy(70, 23);
		cprintf("Continue");
		get_prompt();

		textcolor(LIGHTGREEN);
	}
}

/*---------------------------------------------------------*
 *                      place_order()                      *
 *---------------------------------------------------------*/

void place_order(void)
{
	FILE *fpPrd;
	FILE *fpOrd;
	FILE *fpTmp;
	char codeP[CODE_LENGTH + 1];
	char nameP[NAME_LENGTH + 1];
	char descP[DESC_LENGTH + 1];
	float priceP;
	int availableP;
	int levelP;
	char codeO[CODE_LENGTH + 1];
	char nameO[NAME_LENGTH + 1];
	int amountO;
	int d;
	int m;
	int y;
	int isValid;
	int opt;

	prepare_screen();
	textcolor(LIGHTGREEN);

	gotoxy(34, 6);
	cprintf("Order Form");
	gotoxy(34, 7);
	cprintf("----------");
	gotoxy(5, 9);
	cprintf("Product Code               :");
	gotoxy(5, 11);
	cprintf("Product Name               :");
	gotoxy(5, 13);
	cprintf("Quantity                   :");
	gotoxy(5, 15);
	cprintf("Date Required [dd-mm-yyyy] :");
	gotoxy(34, 9);
	fflush(stdin);
	gets(codeO);
	gotoxy(34, 11);
	fflush(stdin);
	gets(nameO);
	gotoxy(34, 13);
	scanf("%i", &amountO);
	gotoxy(34, 15);
	scanf("%i-%i-%i", &d, &m, &y);

	isValid = REC_INVAL;

	if ((fpPrd = fopen(PRD_FILE, "r")) == NULL)
	{
		isValid = REC_INVAL;
	}
	else
	{
		while (!(feof(fpPrd)))
		{
			fscanf(fpPrd, "%[^/]%*c%[^/]%*c%[^/]%*c%f %i %i%*c", codeP, nameP,
				descP, &priceP, &availableP, &levelP);

			if (feof(fpPrd))
			{
				break;
			}

			if ((strcmp(codeP, codeO)) == 0)
			{
				if ((strcmp(nameP, nameO)) == 0)
				{
					if (availableP > amountO)
					{
						isValid = REC_VALID;
						break;
					}
				}
			}
		}

		fclose(fpPrd);
	}

	if (isValid == REC_VALID)
	{	
		gotoxy(5, 19);
		cprintf("The total amount for this order is %.2f", (priceP * amountO));

		textcolor(LIGHTGREEN);

		gotoxy(62, 23);
		cprintf("[");
		gotoxy(78, 23);
		cprintf("]");
		gotoxy(3, 23);
		cprintf("[");
		gotoxy(15, 23);
		cprintf("]");

		textcolor(LIGHTGREEN + BLINK);

		gotoxy(63, 23);
		cprintf("Enter: Continue");
		gotoxy(4, 23);
		cprintf("Esc: Cancel");

		do
		{
			opt = getch();
		} while (opt != PROMPT_CHAR && (int)opt != ESC_ASCII);

		if (opt == PROMPT_CHAR)
		{
			fpOrd = fopen(ORD_FILE, "a+");
			fprintf(fpOrd, "%s/%s/%i %i %i %i\n", codeO, nameO, amountO, d, m, y);
			fflush(fpOrd);
			fclose(fpOrd);
			fpPrd = fopen(PRD_FILE, "r");
			fpTmp = fopen(TMP_FILE, "w");

			while (!(feof(fpPrd)))
			{
				fscanf(fpPrd, "%[^/]%*c%[^/]%*c%[^/]%*c%f %i %i%*c", codeP,
					nameP, descP, &priceP, &availableP, &levelP);

				if (feof(fpPrd))
				{
					break;
				}

				if ((strcmp(codeP, codeO)) == 0)
				{
					availableP -= amountO;
				}

				fprintf(fpTmp, "%s/%s/%s/%.2f %i %i\n", codeP, nameP, descP,
					priceP, availableP, levelP);
			}

			fflush(fpTmp);
			fclose(fpPrd);
			fclose(fpTmp);
			remove(PRD_FILE);
			rename(TMP_FILE, PRD_FILE);
		}
	}
	else
	{
		prepare_screen();
		textcolor(LIGHTRED);

		gotoxy(28, 12);
		cprintf("<< Invalid  Record! >>");

		textcolor(LIGHTGREEN);

		gotoxy(69, 23);
		cprintf("[");
		gotoxy(78, 23);
		cprintf("]");

		textcolor(LIGHTGREEN + BLINK);

		gotoxy(70, 23);
		cprintf("Continue");
		get_prompt();

		textcolor(LIGHTGREEN);
	}
}

/*---------------------------------------------------------*
 *                     cancel_order()                      *
 *---------------------------------------------------------*/

void cancel_order(void)
{
	FILE *fpPrd;
	FILE *fpOrd;
	FILE *fpTmp;
	FILE *fpTmpX;
	char code[CODE_LENGTH + 1];
	int amount;
	char codeP[CODE_LENGTH + 1];
	char nameP[NAME_LENGTH + 1];
	char descP[DESC_LENGTH + 1];
	float priceP;
	int availableP;
	int levelP;
	char codeO[CODE_LENGTH + 1];
	char nameO[NAME_LENGTH + 1];
	int amountO;
	int d;
	int m;
	int y;
	int isValid;
	int isDel;
	int opt;
	int ctr;

	prepare_screen();
	textcolor(LIGHTGREEN);

	gotoxy(33, 8);
	cprintf("Cancel Order");
	gotoxy(33, 9);
	cprintf("------------");
	gotoxy(28, 12);
	cprintf("Product Code of Order: ");
	fflush(stdin);
	gets(code);

	isValid = REC_INVAL;

	if ((fpOrd = fopen(ORD_FILE, "r")) != NULL)
	{
		fpTmp = fopen(TMP_FILE, "w");

		while (!(feof(fpOrd)))
		{
			fscanf(fpOrd, "%[^/]%*c%[^/]%*c%i %i %i %i%*c", codeO, nameO,
				&amountO, &d, &m, &y);

			if (feof(fpOrd))
			{
				break;
			}

			if ((strcmp(code, codeO)) == 0)
			{
				isValid = REC_VALID;
				fprintf(fpTmp, "%s/%s/%i %i %i %i\n", codeO, nameO, amountO,
					d, m, y);
			}
		}

		fflush(fpTmp);
		fclose(fpOrd);
		fclose(fpTmp);
	}

	if (isValid == REC_VALID)
	{
		fpTmp = fopen(TMP_FILE, "r");
		ctr = 0;

		while (!(feof(fpTmp)))
		{
			fscanf(fpTmp, "%[^/]%*c%[^/]%*c%i %i %i %i%*c", codeO, nameO, &amountO,
				&d, &m, &y);

			if (feof(fpTmp))
			{
				break;
			}

			prepare_screen();
			ctr++;
			textcolor(LIGHTGREEN);

			gotoxy(4, 4);
			cprintf("<< Record No. %02i >>", ctr);
			gotoxy(5, 9);
			cprintf("Product Code               : %s", codeO);
			gotoxy(5, 11);
			cprintf("Product Name               : %s", nameO);
			gotoxy(5, 13);
			cprintf("Quantity                   : %i", amountO);
			gotoxy(5, 15);
			cprintf("Date Required [dd-mm-yyyy] : %02i-%02i-%04i", d, m, y);
			gotoxy(69, 23);
			cprintf("[");
			gotoxy(78, 23);
			cprintf("]");

			textcolor(LIGHTGREEN + BLINK);

			gotoxy(70, 23);
			cprintf("Continue");
			get_prompt();

			textcolor(LIGHTGREEN);
		}

		fclose(fpTmp);

		prepare_screen();
		textcolor(LIGHTGREEN);

		gotoxy(25, 12);
		cprintf("Enter Record ID to Delete: ");
		fflush(stdin);
		cscanf("%i", &opt);
		fpTmp = fopen(TMP_FILE, "r");
		fpTmpX = fopen(TMP_FILE_X, "w");
		isDel = REC_INVAL;
		ctr = 0;

		while (!(feof(fpTmp)))
		{
			fscanf(fpTmp, "%[^/]%*c%[^/]%*c%i %i %i %i%*c", codeO, nameO, &amountO,
				&d, &m, &y);

			if (feof(fpTmp))
			{
				break;
			}

			ctr++;

			if (ctr != opt)
			{
				fprintf(fpTmpX, "%s/%s/%i %i %i %i\n", codeO, nameO, amountO,
					d, m, y);
			}
			else
			{
				isDel = REC_VALID;
				amount = amountO;
			}
		}

		fflush(fpTmpX);
		fclose(fpTmpX);
		fclose(fpTmp);
		remove(TMP_FILE);
		rename(TMP_FILE_X, TMP_FILE);

		if (isDel == REC_VALID)
		{
			fpOrd = fopen(ORD_FILE, "r");
			fpTmp = fopen(TMP_FILE, "a+");

			while (!(feof(fpOrd)))
			{
				fscanf(fpOrd, "%[^/]%*c%[^/]%*c%i %i %i %i%*c", codeO,
					nameO, &amountO, &d, &m, &y);

				if (feof(fpOrd))
				{
					break;
				}

				if ((strcmp(code, codeO)) != 0)
				{
					fprintf(fpTmp, "%s/%s/%i %i %i %i\n", codeO, nameO,
						amountO, d, m, y);
				}
			}

			fflush(fpTmp);
			fclose(fpTmp);
			fclose(fpOrd);
			remove(ORD_FILE);
			rename(TMP_FILE, ORD_FILE);
			fpPrd = fopen(PRD_FILE, "r");
			fpTmp = fopen(TMP_FILE, "w");

			while (!(feof(fpPrd)))
			{
				fscanf(fpPrd, "%[^/]%*c%[^/]%*c%[^/]%*c%f %i %i%*c", codeP,
					nameP, descP, &priceP, &availableP, &levelP);

				if(feof(fpPrd))
				{
					break;
				}

				if ((strcmp(codeP, code)) == 0)
				{
					availableP += amount;
				}

				fprintf(fpTmp, "%s/%s/%s/%.2f %i %i\n", codeP, nameP, descP,
					priceP, availableP, levelP);
			}

			fflush(fpTmp);
			fclose(fpTmp);
			fclose(fpPrd);
			remove(PRD_FILE);
			rename(TMP_FILE, PRD_FILE);
		}
		else
		{
			prepare_screen();
			textcolor(LIGHTRED);

			gotoxy(27, 12);
			cprintf("<< Invalid Record ID! >>");
			gotoxy(69, 23);
			cprintf("[");
			gotoxy(78, 23);
			cprintf("]");

			textcolor(LIGHTGREEN + BLINK);

			gotoxy(70, 23);
			cprintf("Continue");
			get_prompt();

			textcolor(LIGHTGREEN);
		}
	}
	else
	{
		prepare_screen();
		textcolor(LIGHTRED);

		gotoxy(26, 12);
		cprintf("<< Invalid Record Info! >>");

		textcolor(LIGHTGREEN);

		gotoxy(69, 23);
		cprintf("[");
		gotoxy(78, 23);
		cprintf("]");

		textcolor(LIGHTGREEN + BLINK);

		gotoxy(70, 23);
		cprintf("Continue");
		get_prompt();

		textcolor(LIGHTGREEN);
	}
}

/*---------------------------------------------------------*
 *                      change_order()                     *
 *---------------------------------------------------------*/

void change_order(void)
{
	FILE *fpOrd;
	FILE *fpPrd;
	FILE *fpTmp;
	FILE *fpTmpX;
	char code[CODE_LENGTH + 1];
	char codeO[CODE_LENGTH + 1];
	char nameO[NAME_LENGTH + 1];
	int amountO;
	int amount;
	int d;
	int m;
	int y;
	int diff;
	char codeP[CODE_LENGTH + 1];
	char nameP[NAME_LENGTH + 1];
	char descP[DESC_LENGTH + 1];
	float priceP;
	int availableP;
	int levelP;
	int opt;
	int ctr;
	int isValid;
	int isEd;

	prepare_screen();
	textcolor(LIGHTGREEN);

	gotoxy(30, 8);
	cprintf("Change Order Info");
	gotoxy(30, 9);
	cprintf("-----------------");
	gotoxy(26, 12);
	cprintf("Product Code of Order: ");
	fflush(stdin);
	gets(code);

	isValid = REC_INVAL;

	if ((fpOrd = fopen(ORD_FILE, "r")) != NULL)
	{
		fpTmpX = fopen(TMP_FILE_X, "w");

		while (!(feof(fpOrd)))
		{
			fscanf(fpOrd, "%[^/]%*c%[^/]%*c%i %i %i %i%*c", codeO, nameO, &amountO,
				&d, &m, &y);

			if (feof(fpOrd))
			{
				break;
			}

			if ((strcmp(codeO, code)) == 0)
			{
				fprintf(fpTmpX, "%s/%s/%i %i %i %i\n", codeO, nameO, amountO,
					d, m, y);
				isValid = REC_VALID;
			}
		}

		fflush(fpTmpX);
		fclose(fpTmpX);
		fclose(fpOrd);

		if (isValid == REC_VALID)
		{
			fpTmpX = fopen(TMP_FILE_X, "r");
			ctr = 0;

			while (!(feof(fpTmpX)))
			{
				fscanf(fpTmpX, "%[^/]%*c%[^/]%*c%i %i %i %i%*c", codeO, nameO,
					&amountO, &d, &m, &y);

				if (feof(fpTmpX))
				{
					break;
				}

				prepare_screen();
				textcolor(LIGHTGREEN);

				ctr++;
				gotoxy(4, 4);
				cprintf("<< Record ID No. %02i >>", ctr);
				gotoxy(5, 9);
				cprintf("Product Code      : %s", codeO);
				gotoxy(5, 11);
				cprintf("Product Name      : %s", nameO);
				gotoxy(5, 13);
				cprintf("Quantity          : %i", amountO);
				gotoxy(5, 15);
				cprintf("Date [dd-mm-yyyy] : %02i-%02i-%04i", d, m, y);
				gotoxy(69, 23);
				cprintf("[");
				gotoxy(78, 23);
				cprintf("]");

				textcolor(LIGHTGREEN + BLINK);

				gotoxy(70, 23);
				cprintf("Continue");
				get_prompt();

				textcolor(LIGHTGREEN);
			}

			fclose(fpTmpX);
			prepare_screen();
			textcolor(LIGHTGREEN);

			gotoxy(26, 12);
			cprintf("Enter Record ID to Change: ");
			fflush(stdin);
			scanf("%i", &opt);
			fpTmpX = fopen(TMP_FILE_X, "r");
			fpTmp = fopen(TMP_FILE, "w");
			ctr = 0;
			isEd = REC_INVAL;

			while (!(feof(fpTmpX)))
			{
				fscanf(fpTmpX, "%[^/]%*c%[^/]%*c%i %i %i %i%*c", codeO, nameO, 
					&amountO, &d, &m, &y);

				if (feof(fpTmpX))
				{
					break;
				}

				ctr++;

				if (ctr != opt)
				{
					fprintf(fpTmp, "%s/%s/%i %i %i %i\n", codeO, nameO,
						amountO, d, m, y);
				}
				else
				{
					isEd = REC_VALID;
					prepare_screen();
					textcolor(LIGHTGREEN);

					gotoxy(5, 8);
					cprintf("Product Code           : %s", codeO);
					gotoxy(5, 11);
					cprintf("Product Name           : %s", nameO);
					gotoxy(5, 14);
					cprintf("Quantity               : ");
					fflush(stdin);
					scanf("%i", &amount);
					gotoxy(5, 17);
					cprintf("Date [dd-mm-yyyy]      : ");
					fflush(stdin);
					scanf("%i-%i-%i", &d, &m, &y);
					diff = amountO - amount;
					fprintf(fpTmp, "%s/%s/%i %i %i %i\n", codeO, nameO,
						amount, d, m, y);
				}
			}

			fflush(fpTmp);
			fclose(fpTmp);
			fclose(fpTmpX);
			remove(TMP_FILE_X);

			if (isEd == REC_VALID)
			{
				fpOrd = fopen(ORD_FILE, "r");
				fpTmp = fopen(TMP_FILE, "a+");

				while (!(feof(fpOrd)))
				{
					fscanf(fpOrd, "%[^/]%*c%[^/]%*c%i %i %i %i%*c", codeO,
						nameO, &amountO, &d, &m, &y);

					if (feof(fpOrd))
					{
						break;
					}

					if ((strcmp(codeO, code)) != 0)
					{
						fprintf(fpTmp, "%s/%s/%i %i %i %i\n", codeO, nameO,
							amountO, d, m, y);
					}
				}

				fflush(fpTmp);
				fclose(fpOrd);
				fclose(fpTmp);
				remove(ORD_FILE);
				rename(TMP_FILE, ORD_FILE);
				fpPrd = fopen(PRD_FILE, "r");
				fpTmp = fopen(TMP_FILE, "w");

				while (!(feof(fpPrd)))
				{
					fscanf(fpPrd, "%[^/]%*c%[^/]%*c%[^/]%*c%f %i %i%*c",
						codeP, nameP, descP, &priceP, &availableP,
						&levelP);

					if (feof(fpPrd))
					{
						break;
					}

					if ((strcmp(codeP, code)) == 0)
					{
						availableP += diff;
					}

					fprintf(fpTmp, "%s/%s/%s/%.2f %i %i\n", codeP, nameP,
						descP, priceP, availableP, levelP);
				}

				fflush(fpTmp);
				fclose(fpPrd);
				fclose(fpTmp);
				remove(PRD_FILE);
				rename(TMP_FILE, PRD_FILE);
			}
		}
		else
		{
			isValid = REC_INVAL;
		}
	}

	if (isValid == REC_INVAL)
	{
		prepare_screen();
		textcolor(LIGHTRED);

		gotoxy(29, 12);
		cprintf("<< Invalid Record >>");

		textcolor(LIGHTGREEN);

		gotoxy(69, 23);
		cprintf("[");
		gotoxy(78, 23);
		cprintf("]");

		textcolor(LIGHTGREEN + BLINK);

		gotoxy(70, 23);
		cprintf("Continue");
		get_prompt();

		textcolor(LIGHTGREEN);
	}
}

/*---------------------------------------------------------*
 *                       view_order()                      *
 *---------------------------------------------------------*/

void view_order(void)
{
	FILE *fpOrd;
	char codeO[CODE_LENGTH + 1];
	char nameO[NAME_LENGTH + 1];
	int amountO;
	int d;
	int m;
	int y;
	int month;
	int year;

	prepare_screen();
	textcolor(LIGHTGREEN);

	gotoxy(24, 12);
	cprintf("Month of Records [mm-yyyy] : ");
	scanf("%i-%i", &month, &year);

	if ((fpOrd = fopen(ORD_FILE, "r")) != NULL)
	{
		while (!(feof(fpOrd)))
		{
			fscanf(fpOrd, "%[^/]%*c%[^/]%*c%i %i %i %i%*c", codeO, nameO, &amountO,
				&d, &m, &y);

			if (feof(fpOrd))
			{
				break;
			}

			if ((month == m) && (year == y))
			{
				prepare_screen();
				textcolor(LIGHTGREEN);

				gotoxy(34, 6);
				cprintf("ORDER INFO");
				gotoxy(34, 7);
				cprintf("----------");
				gotoxy(3, 9);
				cprintf("Month : %02i", month);
				gotoxy(5, 12);
				cprintf("Product Code         : %s", codeO);
				gotoxy(5, 14);
				cprintf("Product Name         : %s", nameO);
				gotoxy(5, 16);
				cprintf("Quantity             : %i", amountO);
				gotoxy(5, 18);
				cprintf("Date [dd-mm-yyyy]    : %02i-%02i-%04i", d, m, y);
				gotoxy(69, 23);
				cprintf("[");
				gotoxy(78, 23);
				cprintf("]");

				textcolor(LIGHTGREEN + BLINK);

				gotoxy(70, 23);
				cprintf("Continue");
				get_prompt();

				textcolor(LIGHTGREEN);
			}
		}
	}
	else
	{
		prepare_screen();
		textcolor(LIGHTRED);

		gotoxy(29, 12);
		cprintf("<< Invalid Record >>");

		textcolor(LIGHTGREEN);

		gotoxy(69, 23);
		cprintf("[");
		gotoxy(78, 23);
		cprintf("]");

		textcolor(LIGHTGREEN + BLINK);

		gotoxy(70, 23);
		cprintf("Continue");
		get_prompt();

		textcolor(LIGHTGREEN);
	}
}

/*---------------------------------------------------------*
 *                      confirm_exit()                     *
 *---------------------------------------------------------*/

int confirm_exit(void)
{
	int opt;

	prepare_screen();
	textcolor(LIGHTRED);

	gotoxy(33, 8);
	cprintf("CONFIRM EXIT");
	gotoxy(33, 9);
	cprintf("------------");
	gotoxy(24, 15);
	cprintf("Are You Sure You Want to Exit?");

	textcolor(LIGHTGREEN);

	gotoxy(62, 23);
	cprintf("[");
	gotoxy(78, 23);
	cprintf("]");
	gotoxy(3, 23);
	cprintf("[");
	gotoxy(15, 23);
	cprintf("]");

	textcolor(LIGHTGREEN + BLINK);

	gotoxy(63, 23);
	cprintf("Enter: Continue");
	gotoxy(4, 23);
	cprintf("Esc: Cancel");

	do
	{
		opt = getch();
	} while (opt != PROMPT_CHAR && (int)opt != ESC_ASCII);

	if ((int)opt == ESC_ASCII)
	{
		return NO_EXIT;
	}

	return IS_EXIT;
}

/*---------------------------------------------------------*
 *                    invalid_option()                     *
 *---------------------------------------------------------*/

void invalid_option(void)
{
	prepare_screen();
	textcolor(LIGHTRED + BLINK);

	gotoxy(29, 12);
	cprintf("<< Invalid Option >>");

	textcolor(LIGHTGREEN);

	gotoxy(69, 23);
	cprintf("[");
	gotoxy(78, 23);
	cprintf("]");

	textcolor(LIGHTGREEN + BLINK);

	gotoxy(70, 23);
	cprintf("Continue");
	get_prompt();

	textcolor(LIGHTGREEN);
}

/*---------------------------------------------------------*
 *                      exit_screen()                      *
 *---------------------------------------------------------*/

void exit_screen(void)
{
	int ctr;

	prepare_screen();
	textcolor(LIGHTGREEN);

	gotoxy(32, 5);
	cprintf("SPECIAL THANKS");
	gotoxy(32, 6);
	cprintf("--------------");
	gotoxy(28, 10);
	cprintf("Digital Phantom");
	gotoxy(28, 13);
	cprintf("Digital Phantom");
	gotoxy(28, 14);
	cprintf("Dilrukshan Hettiaarachchi");
	gotoxy(28, 17);
	cprintf("Dilrukshan Hettiaarachchi");
	gotoxy(28, 18);
	cprintf("Tyronne Thomas");

	textcolor(YELLOW);

	gotoxy(23, 9);
	cprintf("#  Programming Assistance:");
	gotoxy(23, 12);
	cprintf("#  Design Assistance:");
	gotoxy(23, 16);
	cprintf("#  Documentaiton Assistance:");

	_setcursortype(_NOCURSOR);
	textcolor(LIGHTGREEN);

	gotoxy(3, 22);
	cprintf("Finalizing.");

	for(ctr = 0; ctr < 10; ctr++)
	{
		delay(500);
		cprintf(".");
		delay(500);
		cprintf(".");
	}

	gotoxy(3, 23);
	cprintf("Ending Program.");

	for(ctr = 0; ctr < 10; ctr++)
	{
		sleep(1);
		cprintf(".");
	}

	fflush(stdin);
	gotoxy(69, 23);
	cprintf("[");
	gotoxy(78, 23);
	cprintf("]");

	textcolor(LIGHTGREEN + BLINK);

	gotoxy(70, 23);
	cprintf("Continue");

	textcolor(LIGHTGREEN);

	get_prompt();
}
