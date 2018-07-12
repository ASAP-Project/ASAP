/*==========================================================*
 *PROGRAM NAME  : fw.c                                      *
 *AUTHOR        : Sandeep Ellawala                          *
 *                sandeep.ellawala@yahoo.com                *
 *                +94(0)114927809                           *
 *PLATFORM      : AMD Durone - 1.2 GHz / 64 MB RAM          *
 *                Microsoft Windows XP - SP 2.0             *
 *                Borland TURBO C++ 3.0                     *
 *DATE          : 04/04/2007                                *
 *NOTES         : This program code listing is for a flight *
 *                reservation system that manages both the  *
 *                flights and reservations.  This program is*
 *                not a GUI pupported and it is specifically*
 *                designed to be compiled using Borland's   *
 *                C or C++ environments only.               *
 *==========================================================*/


/*----------------------------------------------------------*
 *                  INCLUDED HEADER FILES                   *
 *----------------------------------------------------------*/

# ifndef __STDIO_H
	# include <stdio.h>
# endif

# ifndef __CONIO_H
	# include <conio.h>
# endif

# ifndef __CTYPE_H
	# include <ctype.h>
# endif

# ifndef __STDLIB_H
	# include <stdlib.h>
# endif

# ifndef __STRING_H
	# include <string.h>
# endif


/*----------------------------------------------------------*
 *                  STORAGE FILE CONSTANTS                  *
 *----------------------------------------------------------*/

# define RESERV_FILE "reserv.fwd" /*reservation master file */

# define FLIGHT_FILE "flight.fwd" /*flight master file      */

# define TEMPFL_FILE "tempfl.tmp" /*flight transaction file */

# define TEMPRE_FILE "tempre.tmp" /*reservation transaction
                                    file                    */

# define USRPWD_FILE "usrpwd.sec" /*user password file      */

# define ADMPWD_FILE "admpwd.sec" /*administrator password
                                    file                    */

# define CRYPTK_FILE "cryptk.sec" /*Encryption Key file     */

# define CANREP_FILE "canrep.rep" /*Notification of flight
                                    cancelations file       */


/*----------------------------------------------------------*
 *                    CONSTANT DEFINITIONS                  *
 *----------------------------------------------------------*/

# ifndef __cplusplus /*Supports cross-compilation between
                       C and C++ Borlan environments.       */

# define YES			1
# define NO				0

# define VALID			1
# define INVALID		0

# define TRUE			1
# define FALSE			0

typedef unsigned short int FLAG;

# else

# define YES         	     true
# define NO		    		flase

# define VALID		     	 true
# define INVALID	    	false

# define TRUE		    	 true
# define FALSE		    	false

typedef bool FLAG;

# endif


/*Defines x and y coordinates of the cursor location of user
  typing area.                                              */

# define USER_X				5
# define USER_Y		       23


/*Command line options that are consistent through out the
  program are defined here.                                 */

# define CMD_HELP           '0'
# define CMD_EXIT           '9'
# define CMD_BACK           '7'
# define CMD_LOFF           '8'


/*Cursor locations used to draw the border of the screen are
  defined here.                                             */

# define L_T_X                2
# define L_T_Y                2
# define R_T_X               79
# define R_T_Y                2
# define L_B_X                2
# define L_B_Y               24
# define R_B_X               79
# define R_B_Y               24


/*The ascii values of characters used to draw the screen
  border are defined here.                                  */

# define H_CHAR             186
# define V_CHAR             205
# define LT_CHAR            201
# define LB_CHAR            200
# define RT_CHAR            187
# define RB_CHAR            188


/*----------------------------------------------------------*
 *               GLOBAL VARIABLE DECLARATIONS               *
 *----------------------------------------------------------*/

FLAG exitF;
FLAG backF;
FLAG loggF;


/*----------------------------------------------------------*
 *                    FUNCTION PROTOTYPES                   *
 *----------------------------------------------------------*/

void adm_pwd(void);
void init_sys(void);
void user_pwd(void);
void user_menu(void);
void user_help(void);
void login_menu(void);
void login_help(void);
void user_login(void);
void add_reserv(void);
void add_flight(void);
void admin_menu(void);
void admin_help(void);
void reserv_menu(void);
void reserv_help(void);
void exit_screen(void);
void edit_reserv(void);
void view_reserv(void);
void flight_menu(void);
void flight_help(void);
void edit_flight(void);
void admin_login(void);
void upwd_change(void);
void apwd_change(void);
void cryk_change(void);
void confirm_exit(void);
void view_flights(void);
void cancel_reserv(void);
void search_reserv(void);
void cancel_flight(void);
void search_flight(void);
void get_prompt(int, int);
void welcome_screen(void);
void invalid_option(void);
void prepare_screen(void);
void confirm_logoff(void);
void reserv_process(void);
void confirm_goback(void);
void flight_process(void);
void invalid_startup(char *);


/*----------------------------------------------------------*
 *                     FUNCTION : main()                    *
 *----------------------------------------------------------*/

int main(int argc, char *argv[])
{
    char menuOpt;

    /*This program does not support command line arguments to
      be passed at the startup. It is being checked here.   */

	if(argc > 1)
	{
		invalid_startup(argv[0]);
		get_prompt(USER_X, USER_Y);
        clrscr();
        return EXIT_FAILURE;
    }

    welcome_screen();
    get_prompt(USER_X, USER_Y);

    exitF = NO;

    do
    {
    	login_menu();
        fflush(stdin);
        menuOpt = (char)getche();

        switch(menuOpt)
        {
        	case CMD_HELP:
            {
            	login_help();
                get_prompt(USER_X, USER_Y);
                break;
            }
            case '1':
            {
            	user_login();
                break;
            }
            case '2':
            {
            	admin_login();
                break;
            }
            case CMD_EXIT:
            {
            	confirm_exit();
                break;
            }
            default:
            {
            	invalid_option();
                get_prompt(USER_X, USER_Y);
            }
        }
    }while(exitF != YES);

    exit_screen();
    get_prompt(USER_X, USER_Y);
    clrscr(); /*Clears the remaining contents on the screen
                before closing.                             */
    return EXIT_SUCCESS;
}


/*----------------------------------------------------------*
 *                   FUNCTION : adm_pwd()                   *
 *----------------------------------------------------------*/
 
void adm_pwd(void)
{
	char admpwd[9]; /*real administrator password           */
    char cryptk[9]; /*Key used to encrypt the password      */
    char pwd[9]; /*password entered by the user             */

    FILE *fp;
    static int count = 0;
    unsigned int ctr;

    fp = fopen(CRYPTK_FILE, "r");
    fread(cryptk, sizeof(char), 9, fp);
    fclose(fp);

    fp = fopen(ADMPWD_FILE, "r");
    fread(admpwd, sizeof(char), 9, fp);
    fclose(fp);

	for(ctr = 0; ctr < 8; ctr++)
    {
    	admpwd[ctr] ^= cryptk[ctr];
    }

    prepare_screen();
    textcolor(BLUE);
	gotoxy(31, 7);
    cprintf("ENTER ADMIN PASSWORD");
    gotoxy(31, 8);
    cprintf("--------------------");
    gotoxy(3, 21);
    textcolor(LIGHTGRAY + BLINK);
    cprintf("Type the password and press ENTER...");
    textcolor(LIGHTGRAY);
	gotoxy(USER_X, USER_Y);
	fflush(stdin);
    gets(pwd);
    if((strncmp(admpwd, pwd, 8)) == 0)
    {
		prepare_screen();
		gotoxy(33, 12);
		textcolor(LIGHTGREEN + BLINK);
		cprintf("<ACCESS GRANTED>");
		textcolor(LIGHTGRAY);
		get_prompt(USER_X, USER_Y);
        loggF = YES;
		count = 0;
    }
    else
	{
		prepare_screen();
		gotoxy(34, 12);
		textcolor(LIGHTRED + BLINK);
		cprintf("ACCESS DENIED!");
		textcolor(LIGHTGRAY);
		get_prompt(USER_X, USER_Y);
        backF = YES;
        count++;
    }
	if(count == 3)
	{
		exitF = YES;
	}
}



/*----------------------------------------------------------*
 *                  FUNCTION : init_sys()                   *
 *----------------------------------------------------------*/

void init_sys(void)
{
	FILE *fp;

    char buf1[9], buf2[9];/*general storage buffers         */

    unsigned int ctr;

    /*If any of the files are not available, they are being
      created in the following code.                        */

    if((fp = fopen(FLIGHT_FILE, "r")) == NULL)
    {
    	fp = fopen(FLIGHT_FILE, "w");
        fclose(fp);
    }
    fclose(fp);

    if((fp = fopen(RESERV_FILE, "r")) == NULL)
    {
    	fp = fopen(RESERV_FILE, "w");
        fclose(fp);
    }
    fclose(fp);

    if((fp = fopen(USRPWD_FILE, "r")) == NULL)
    {
    	fp = fopen(USRPWD_FILE, "w");
        strcpy(buf1, "makiwara");
        strcpy(buf2, "hackervr");
        for(ctr = 0; ctr < 8; ctr++)
        {
        	buf1[ctr] ^= buf2[ctr];
        }
        fwrite(buf1, sizeof(char), 9, fp);
        fclose(fp);
        fp = fopen(ADMPWD_FILE, "w");
        fwrite(buf1, sizeof(char), 9, fp);
        fclose(fp);
        fp = fopen(CRYPTK_FILE, "w");
        fwrite(buf2, sizeof(char), 9, fp);
        fclose(fp);
    }
    fclose(fp);
    
    if((fp = fopen(ADMPWD_FILE, "r")) == NULL)
    {
    	fp = fopen(USRPWD_FILE, "w");
        strcpy(buf1, "makiwara");
        strcpy(buf2, "hackervr");
        for(ctr = 0; ctr < 8; ctr++)
        {
        	buf1[ctr] ^= buf2[ctr];
        }
        fwrite(buf1, sizeof(char), 9, fp);
        fclose(fp);
        fp = fopen(ADMPWD_FILE, "w");
        fwrite(buf1, sizeof(char), 9, fp);
        fclose(fp);
        fp = fopen(CRYPTK_FILE, "w");
        fwrite(buf2, sizeof(char), 9, fp);
        fclose(fp);
    }
    fclose(fp);
    
    if((fp = fopen(CRYPTK_FILE, "r")) == NULL)
    {
    	fp = fopen(USRPWD_FILE, "w");
        strcpy(buf1, "makiwara");
        strcpy(buf2, "hackervr");
        for(ctr = 0; ctr < 8; ctr++)
        {
        	buf1[ctr] ^= buf2[ctr];
        }
        fwrite(buf1, sizeof(char), 9, fp);
        fclose(fp);
        fp = fopen(ADMPWD_FILE, "w");
        fwrite(buf1, sizeof(char), 9, fp);
        fclose(fp);
        fp = fopen(CRYPTK_FILE, "w");
        fwrite(buf2, sizeof(char), 9, fp);
        fclose(fp);
    }
    fclose(fp);
}



/*----------------------------------------------------------*
 *                   FUNCTION : user_pwd()                  *
 *----------------------------------------------------------*/

void user_pwd(void)
{
	char usrpwd[9];/*real user password                     */
    char cryptk[9];/*key used to encrypt the password       */
    char pwd[9];/*password entered by the user              */

    FILE *fp;
    static int count = 0;
    unsigned int ctr;

    fp = fopen(CRYPTK_FILE, "r");
    fread(cryptk, sizeof(char), 9, fp);
    fclose(fp);

    fp = fopen(USRPWD_FILE, "r");
    fread(usrpwd, sizeof(char), 9, fp);
    fclose(fp);

    for(ctr = 0; ctr < 8; ctr++)
    {
    	usrpwd[ctr] ^= cryptk[ctr];
    }

    prepare_screen();
    textcolor(BLUE);
	gotoxy(31, 7);
    cprintf("ENTER USER PASSWORD");
    gotoxy(31, 8);
    cprintf("-------------------");
    gotoxy(3, 21);
    textcolor(LIGHTGRAY + BLINK);
    cprintf("Type the password and press ENTER...");
    textcolor(LIGHTGRAY);
	gotoxy(USER_X, USER_Y);
	fflush(stdin);
    gets(pwd);
    if((strncmp(usrpwd, pwd, 8)) == 0)
    {
		prepare_screen();
		gotoxy(33, 12);
		textcolor(LIGHTGREEN + BLINK);
		cprintf("<ACCESS GRANTED>");
		textcolor(LIGHTGRAY);
		get_prompt(USER_X, USER_Y);
        loggF = YES;
		count = 0;
    }
    else
	{
		prepare_screen();
		gotoxy(34, 12);
		textcolor(LIGHTRED+ BLINK);
		cprintf("ACCESS DENIED!");
		textcolor(LIGHTGRAY);
		get_prompt(USER_X, USER_Y);
        loggF = NO;
		backF = YES;
        count++;
    }
	if(count == 3)
	{
		exitF = YES;
		count = 0;
	}
}



/*----------------------------------------------------------*
 *                   FUNCTION : user_menu()                 *
 *----------------------------------------------------------*/

void user_menu(void)
{
	prepare_screen();
    textcolor(BLUE);
   	gotoxy(32, 7);
    cprintf("USER COMMAND MENU");
   	gotoxy(32, 8);
   	cprintf("-----------------");
   	gotoxy(32, 11);
    textcolor(YELLOW);
   	cprintf("[0] : Help");
   	gotoxy(32, 12);
    textcolor(BLUE);
   	cprintf("[1] : Reservations");
   	gotoxy(32, 13);
   	cprintf("[2] : Flights");
   	gotoxy(32, 14);
    textcolor(YELLOW);
   	cprintf("[8] : Log Off");
   	gotoxy(32, 15);
    textcolor(RED);
   	cprintf("[9] : Exit");
   	gotoxy(3, 21);
   	textcolor(LIGHTGRAY + BLINK);
   	cprintf("Select menu option...");
   	textcolor(LIGHTGRAY);
   	gotoxy(USER_X, USER_Y);
}



/*----------------------------------------------------------*
 *                   FUNCTION : user_help()                 *
 *----------------------------------------------------------*/

void user_help(void)
{
	prepare_screen();
    textcolor(BLUE);
   	gotoxy(39, 7);
   	cprintf("HELP");
   	gotoxy(39, 8);
   	cprintf("----");
   	gotoxy(8, 11);
   	cprintf("You must first login by entering the correct ");
   	cprintf("user password.  Once");
   	gotoxy(11, 12);
   	cprintf("you are in, you can use menu options related ");
   	cprintf("to the function");
   	gotoxy(9, 13);
   	cprintf("you want to perform.  Press \'0\' to view this");
   	cprintf(" help screen, press");
   	gotoxy(10, 14);
   	cprintf("\'8\' to log off and press \'9\' to exit while");
   	cprintf(" prompted.");
   	gotoxy(3, 21);
   	textcolor(LIGHTGRAY + BLINK);
   	cprintf("Press ENTER to go back to previous menu...");
   	textcolor(LIGHTGRAY);
   	gotoxy(USER_X, USER_Y);
}



/*----------------------------------------------------------*
 *                  FUNCTION : login_menu()                 *
 *----------------------------------------------------------*/

void login_menu(void)
{
	prepare_screen();
   	textcolor(BLUE);
   	gotoxy(36, 8);
   	cprintf("LOGIN MENU");
   	gotoxy(36, 9);
   	cprintf("----------");
   	gotoxy(33, 11);
    textcolor(YELLOW);
   	cprintf("[0] : Help");
    textcolor(BLUE);
   	gotoxy(33, 12);
   	cprintf("[1] : User Access");
   	gotoxy(33, 13);
   	cprintf("[2] : Admin Access");
   	gotoxy(33, 14);
    textcolor(RED);
   	cprintf("[9] : Exit");
   	gotoxy(3, 21);
   	textcolor(LIGHTGRAY + BLINK);
   	cprintf("Select menu option...");
   	textcolor(LIGHTGRAY);
   	gotoxy(USER_X, USER_Y);
}



/*----------------------------------------------------------*
 *                  FUNCTION : login_help()                 *
 *----------------------------------------------------------*/

void login_help(void)
{
	prepare_screen();
    textcolor(BLUE);
   	gotoxy(39, 7);
   	cprintf("HELP");
   	gotoxy(39, 8);
   	cprintf("----");
   	gotoxy(16, 12);
   	cprintf("Press 1 or 2 to get relevant access level.");
   	cprintf("  You must");
   	gotoxy(8, 13);
   	cprintf("login first, in-order to use this system.  ");
   	cprintf("Refer to the user manual ");
   	gotoxy(12, 14);
   	cprintf("for more information on access levels.  Press");
   	cprintf(" 4 to exit or");
   	gotoxy(13, 15);
   	cprintf("press 0 to view this help once you are in ");
   	cprintf("login menu.");
   	gotoxy(3, 21);
   	textcolor(LIGHTGRAY + BLINK);
   	cprintf("Press ENTER to continue...");
   	textcolor(LIGHTGRAY);
   	gotoxy(USER_X, USER_Y);
}



/*----------------------------------------------------------*
 *                  FUNCTION : user_login()                 *
 *----------------------------------------------------------*/

void user_login(void)
{
	char menuOpt;

    backF = NO;
    loggF = NO;
    exitF = NO;

    init_sys();

    do
    {
    	if(loggF == NO)
        {
        	user_pwd();
        }
        else
        {
        	user_menu();
            fflush(stdin);
            menuOpt = (char)getche();

            switch(menuOpt)
            {
            	case CMD_HELP:
                {
                	user_help();
                    get_prompt(USER_X, USER_Y);
                    break;
                }
                case '1':
                {
                	reserv_process();
                    break;
                }
                case '2':
                {
                	flight_process();
                    break;
                }
                case CMD_LOFF:
                {
                	confirm_logoff();
                    break;
                }
                case CMD_EXIT:
                {
                	confirm_exit();
                    break;
                }
                default:
                {
                	invalid_option();
                    get_prompt(USER_X, USER_Y);
                    break;
                }
            }
        }
    }while(exitF == NO && backF == NO);

    backF = NO;
}



/*----------------------------------------------------------*
 *                  FUNCTION : add_reserv()                 *
 *----------------------------------------------------------*/

void add_reserv(void)
{
	FILE *fp;
    FILE *fpf;
    FILE *fpt;

    /*following variables are used to read reservation data
      from the user.                                        */

	char fid[7];
	char name[30];
	char address[70];
	char ppn[9];
	char ccn[17];
	char phone[16];

    /*following variables are used to read flight details
      from the flight storage file.                         */
      
    char tfid[7];
	char tdestin[20];
	int tseats;
	float tprice;
	int tdd, tmm, tyy;
	int tdhh, tdmm;
	int tahh, tamm;

    char xfid[7];
	char xname[30];
	char xaddress[70];
	char xppn[9];
	char xccn[17];
	char xphone[16];

    FLAG validF = NO;

    int ctr;

    prepare_screen();
    textcolor(BLUE);
   	gotoxy(33, 4);
   	cprintf("CUSTOMER DETAILS");
   	gotoxy(33, 5);
   	cprintf("----------------");
   	gotoxy(5, 7);
   	cprintf("Name            : ");
   	gotoxy(5, 9);
   	cprintf("Passport No.    : ");
   	gotoxy(5, 11);
   	cprintf("Address         : ");
   	gotoxy(5, 13);
   	cprintf("Phone No.       : ");
   	gotoxy(5, 15);
   	cprintf("Credit Card No. : ");
   	gotoxy(5, 17);
   	cprintf("Flight ID       : ");

    gotoxy(3, 21);
   	textcolor(LIGHTGRAY + BLINK);
   	cprintf("Enter customer name...");
   	textcolor(LIGHTGRAY);
   	gotoxy(USER_X, USER_Y);
   	fflush(stdin);
   	gets(name);
   	gotoxy(23, 7);
   	cprintf("                                              ");
   	gotoxy(23, 7);
    textcolor(BLUE);
   	cprintf("%s", name);

   	gotoxy(3, 21);
    cprintf("                                              ");
   	textcolor(LIGHTGRAY + BLINK);
    gotoxy(3, 21);
   	cprintf("Enter customer passport number...");
   	textcolor(LIGHTGRAY);
   	gotoxy(USER_X, USER_Y);
   	cprintf("                                              ");
   	gotoxy(USER_X, USER_Y);
   	fflush(stdin);
   	gets(ppn);
   	gotoxy(23, 9);
   	cprintf("                                              ");
   	gotoxy(23, 9);
    textcolor(BLUE);
   	cprintf("%s", ppn);
    
    gotoxy(3, 21);
    cprintf("                                              ");
   	gotoxy(3, 21);
   	textcolor(LIGHTGRAY + BLINK);
   	cprintf("Enter customer\'s address...");
   	textcolor(LIGHTGRAY);
   	gotoxy(USER_X, USER_Y);
   	cprintf("                                              ");
   	gotoxy(USER_X, USER_Y);
   	fflush(stdin);
   	gets(address);
   	gotoxy(23, 11);
   	cprintf("                                              ");
   	gotoxy(23, 11);
    textcolor(BLUE);
   	cprintf("%s", address);
    
    gotoxy(3, 21);
    cprintf("                                              ");
   	gotoxy(3, 21);
   	textcolor(LIGHTGRAY + BLINK);
   	cprintf("Enter customer\'s phone number...");
   	textcolor(LIGHTGRAY);
   	gotoxy(USER_X, USER_Y);
   	cprintf("                                              ");
   	gotoxy(USER_X, USER_Y);
   	fflush(stdin);
   	gets(phone);
   	gotoxy(23, 13);
   	cprintf("                                              ");
   	gotoxy(23, 13);
    textcolor(BLUE);
   	cprintf("%s", phone);

    gotoxy(3, 21);
    cprintf("                                              ");
   	gotoxy(3, 21);
   	textcolor(LIGHTGRAY + BLINK);
   	cprintf("Enter customer\'s credit card number...");
   	textcolor(LIGHTGRAY);
   	gotoxy(USER_X, USER_Y);
   	cprintf("                                              ");
   	gotoxy(USER_X, USER_Y);
   	fflush(stdin);
   	gets(ccn);
   	gotoxy(23, 15);
   	cprintf("                                              ");
   	gotoxy(23, 15);
    textcolor(BLUE);
   	cprintf("%s", ccn);
    
    gotoxy(3, 21);
    cprintf("                                              ");
   	gotoxy(3, 21);
   	textcolor(LIGHTGRAY + BLINK);
   	cprintf("Enter flight id...");
   	textcolor(LIGHTGRAY);
   	gotoxy(USER_X, USER_Y);
   	cprintf("                                              ");
   	gotoxy(USER_X, USER_Y);
   	fflush(stdin);
   	gets(fid);
   	gotoxy(23, 17);
   	cprintf("                                              ");
   	gotoxy(23, 17);
    textcolor(BLUE);
   	cprintf("%s", fid);

    gotoxy(3, 21);
    cprintf("                                              ");
   	gotoxy(3, 21);
   	textcolor(LIGHTGRAY + BLINK);
   	cprintf("Press ENTER to continue...");
   	textcolor(LIGHTGRAY);
   	gotoxy(USER_X, USER_Y);
   	get_prompt(USER_X, USER_Y);

    fpf = fopen(FLIGHT_FILE, "r");
    fpt = fopen(TEMPFL_FILE, "w");

    while(!feof(fpf))
    {
    	fscanf(fpf,
        	"%[^/]%*c%[^/]%*c%i %f %i %i %i %i %i %i %i%*c",
             tfid, tdestin, &tseats, &tprice, &tdd, &tmm,
              &tyy, &tdhh, &tdmm, &tahh, &tamm);
		if(feof(fpf))
		{
			break;
		}

        /*The reservation is valid only if the flight id is
          currently available in the flight file and it has
          seats remaining to be booked.                     */

		if((strcmpi(tfid, fid)) == 0)
		{
        	if(tseats > 0)
            {
            	validF = YES;
                tseats--;
            }
        }

        fprintf(fpt, "%s/%s/%i %.2f %i %i %i %i %i %i %i\n",
        	 tfid, tdestin, tseats, tprice, tdd, tmm, tyy,
             tdhh, tdmm, tahh, tamm);
    }

    fclose(fpf);
    fclose(fpt);

    if(validF == YES)
    {
    	fp = fopen(RESERV_FILE, "r");
        while(!feof(fp))
        {
        	fscanf(fp,
        "%[^!]%*c%[^!]%*c%[^!]%*c%[^!]%*c%[^!]%*c%[^!]%*c%*c",
        xname, xaddress, xphone, xppn, xccn, xfid);

			if(feof(fp))
			{
			break;
			}
        	if(strcmpi(xfid, fid) == 0)
        	{
        		if(strcmpi(xppn, ppn) == 0)
            	{
            		validF = NO;
            	}
        	}
        }
        fclose(fp);
    }
    if(validF == YES)
    {
    	if(strlen(fid) != 5)
        {
        	validF = NO;
        }
    }
    if(validF == YES)
    {
    	if(strlen(name) == 0)
        {
        	validF = NO;
        }
    }
    if(validF == YES)
    {
    	for(ctr = 0; ctr < strlen(name) - 1; ctr++)
        {
        	if(!isalpha(name[ctr]))
            {
            	validF = NO;
            }
        }
    }
    if(validF == YES)
    {
    	if(strlen(address) == 0)
        {
        	validF = NO;
        }
    }
    if(validF == YES)
    {
    	if(strlen(ppn) != 8)
        {
        	validF = NO;
        }
    }
    if(validF == YES)
    {
    	if(strlen(ccn) != 16)
        {
        	validF = NO;
        }
    }
    if(validF == YES)
    {
    	if(strlen(phone) != 15)
		{
        	validF = NO;
        }
    }

    /*If the flight is available to be reserved, then it is
      OK to add the reservation.                            */

    if(validF == YES)
    {
    	remove(FLIGHT_FILE);
        rename(TEMPFL_FILE, FLIGHT_FILE);
		fp = fopen(RESERV_FILE, "a+");
		fprintf(fp, "%s!%s!%s!%s!%s!%s!\n",
        	name, address, phone, ppn, ccn, fid);
		fflush(fp);
		fclose(fp);
    }
    else
    {
    	prepare_screen();
        gotoxy(3, 21);
        cprintf("                                          ");
        gotoxy(3, 21);
        textcolor(LIGHTRED + BLINK);
        cprintf("Invalid Record Data...");
        get_prompt(USER_X, USER_Y);
        textcolor(BLUE);
    }
}



/*----------------------------------------------------------*
 *                 FUNCTION : add_flight()                  *
 *----------------------------------------------------------*/

void add_flight(void)
{
	FILE *fp;

	char fid[7];
	char destin[20];
	int seats;
	float price;
	int dd, mm, yy;
	int dhh, dmm;
	int ahh, amm;

    prepare_screen();
    textcolor(BLUE);
   	gotoxy(34, 4);
   	cprintf("FLIGHT DETAILS");
   	gotoxy(34, 5);
   	cprintf("--------------");
   	gotoxy(5, 7);
   	cprintf("Flight ID       : ");
   	gotoxy(5, 9);
   	cprintf("Destination     : ");
   	gotoxy(5, 11);
   	cprintf("No. of Seats    : ");
   	gotoxy(5, 13);
   	cprintf("Price per Seat  : ");
   	gotoxy(5, 15);
   	cprintf("Date of dept.   : ");
   	gotoxy(5, 17);
   	cprintf("Time of dept.   : ");
   	gotoxy(5, 19);
   	cprintf("Time of arrv.   : ");

    gotoxy(3, 21);
   	textcolor(LIGHTGRAY + BLINK);
   	cprintf("Enter flight id...");
   	textcolor(LIGHTGRAY);
    gotoxy(USER_X, USER_Y);
    cprintf("                                              ");
   	gotoxy(USER_X, USER_Y);
   	fflush(stdin);
   	gets(fid);
   	gotoxy(24, 7);
   	cprintf("                                              ");
   	gotoxy(24, 7);
    textcolor(BLUE);
   	cprintf("%s", fid);

   	gotoxy(3, 21);
   	textcolor(LIGHTGRAY + BLINK);
    cprintf("                                              ");
    gotoxy(3, 21);
   	cprintf("Enter flight destination...");
   	textcolor(LIGHTGRAY);
    gotoxy(USER_X, USER_Y);
    cprintf("                                              ");
   	gotoxy(USER_X, USER_Y);
   	fflush(stdin);
   	gets(destin);
   	gotoxy(24, 9);
   	cprintf("                                              ");
   	gotoxy(24, 9);
    textcolor(BLUE);
   	cprintf("%s", destin);

   	gotoxy(3, 21);
   	textcolor(LIGHTGRAY + BLINK);
    cprintf("                                              ");
    gotoxy(3, 21);
   	cprintf("Enter number of seats...");
   	textcolor(LIGHTGRAY);
    gotoxy(USER_X, USER_Y);
    cprintf("                                              ");
   	gotoxy(USER_X, USER_Y);
   	fflush(stdin);
   	scanf("%i", &seats);
   	gotoxy(24, 11);
   	cprintf("                                              ");
   	gotoxy(24, 11);
    textcolor(BLUE);
   	cprintf("%3i", seats);

   	gotoxy(3, 21);
   	textcolor(LIGHTGRAY + BLINK);
    cprintf("                                              ");
    gotoxy(3, 21);
   	cprintf("Enter price per seat...");
   	textcolor(LIGHTGRAY);
    gotoxy(USER_X, USER_Y);
    cprintf("                                              ");
   	gotoxy(USER_X, USER_Y);
   	fflush(stdin);
   	scanf("%f", &price);
   	gotoxy(24, 13);
   	cprintf("                                              ");
    gotoxy(24, 13);
    textcolor(BLUE);
   	cprintf("%.2f", price);

   	gotoxy(3, 21);
   	textcolor(LIGHTGRAY + BLINK);
    cprintf("                                              ");
    gotoxy(3, 21);
   	cprintf("Enter date of departure [d/m/y]...");
   	textcolor(LIGHTGRAY);
    gotoxy(USER_X, USER_Y);
    cprintf("                                              ");
   	gotoxy(USER_X, USER_Y);
   	fflush(stdin);
   	scanf("%i/%i/%i", &dd, &mm, &yy);
   	gotoxy(24, 15);
   	cprintf("                                              ");
   	gotoxy(24, 15);
    textcolor(BLUE);
   	cprintf("%02i/%02i/%04i", dd, mm, yy);

   	gotoxy(3, 21);
   	textcolor(LIGHTGRAY + BLINK);
    cprintf("                                              ");
    gotoxy(3, 21);
   	cprintf("Enter time of departure [hh:mm]...");
   	textcolor(LIGHTGRAY);
    gotoxy(USER_X, USER_Y);
    cprintf("                                              ");
   	gotoxy(USER_X, USER_Y);
   	fflush(stdin);
   	scanf("%i:%i", &dhh, &dmm);
   	gotoxy(24, 17);
   	cprintf("                                              ");
   	gotoxy(24, 17);
    textcolor(BLUE);
   	cprintf("%02i:%02i", dhh, dmm);

   	gotoxy(3, 21);
   	textcolor(LIGHTGRAY + BLINK);
    cprintf("                                              ");
    gotoxy(3, 21);
   	cprintf("Enter time of arrival [hh:mm]...");
   	textcolor(LIGHTGRAY);
    gotoxy(USER_X, USER_Y);
    cprintf("                                              ");
   	gotoxy(USER_X, USER_Y);
   	fflush(stdin);
   	scanf("%i:%i", &ahh, &amm);
   	gotoxy(24, 19);
   	cprintf("                                              ");
   	gotoxy(24, 19);
    textcolor(BLUE);
   	cprintf("%02i:%02i", ahh, amm);

   	gotoxy(3, 21);
   	textcolor(LIGHTGRAY + BLINK);
    cprintf("                                              ");
    gotoxy(3, 21);
   	cprintf("Press ENTER to continue...");
   	textcolor(LIGHTGRAY);
    gotoxy(USER_X, USER_Y);
    cprintf("                                              ");
   	gotoxy(USER_X, USER_Y);
   	get_prompt(USER_X, USER_Y);
	fp = fopen(FLIGHT_FILE, "a+");
	fprintf(fp, "%s/%s/%i %.2f %i %i %i %i %i %i %i\n",
    	fid, destin, seats, price, dd, mm, yy, dhh, dmm, ahh,
        amm);

	fflush(fp);
	fclose(fp);
}



/*----------------------------------------------------------*
 *                 FUNCTION : admin_menu()                  *
 *----------------------------------------------------------*/

void admin_menu(void)
{
	prepare_screen();
    textcolor(BLUE);
   	gotoxy(32, 7);
   	cprintf("ADMIN COMMAND MENU");
   	gotoxy(32, 8);
    cprintf("------------------");
   	gotoxy(28, 11);
    textcolor(YELLOW);
   	cprintf("[0] : Help");
    textcolor(BLUE);
   	gotoxy(28, 12);
   	cprintf("[1] : Change User Password");
    gotoxy(28, 13);
    cprintf("[2] : Change Admin Password");
   	gotoxy(28, 14);
   	cprintf("[3] : Change Crypt Key");
   	gotoxy(28, 15);
    textcolor(YELLOW);
   	cprintf("[8] : Log Off");
    textcolor(RED);
   	gotoxy(28, 16);
   	cprintf("[9] : Exit");
   	gotoxy(3, 21);
   	textcolor(LIGHTGRAY + BLINK);
   	cprintf("Select menu option...");
   	textcolor(LIGHTGRAY);
   	gotoxy(USER_X, USER_Y);
}



/*----------------------------------------------------------*
 *                 FUNCTION : admin_help()                  *
 *----------------------------------------------------------*/

void admin_help(void)
{
	prepare_screen();
    textcolor(BLUE);
   	gotoxy(39, 7);
   	cprintf("HELP");
   	gotoxy(39, 8);
   	cprintf("----");
   	gotoxy(7, 11);
   	cprintf("You must first login by entering the correct ");
   	cprintf("admin password.  Once");
   	gotoxy(11, 12);
   	cprintf("you are in, you can use menu options related ");
   	cprintf("to the function");
   	gotoxy(9, 13);
   	cprintf("you want to perform.  Press \'0\' to view this");
    cprintf(" help screen, press");
   	gotoxy(10, 14);
   	cprintf("\'8\' to log off and press \'9\' to exit while");
   	cprintf(" prompted.");
   	gotoxy(3, 21);
   	textcolor(LIGHTGRAY + BLINK);
   	cprintf("Press ENTER to go back to previous menu...");
   	textcolor(LIGHTGRAY);
   	gotoxy(USER_X, USER_Y);
}



/*----------------------------------------------------------*
 *                FUNCTION : reserv_menu()                  *
 *----------------------------------------------------------*/

void reserv_menu(void)
{
	prepare_screen();
    textcolor(BLUE);
   	gotoxy(29, 7);
   	cprintf("RESERVATION COMMAND MENU");
   	gotoxy(29, 8);
   	cprintf("------------------------");
   	gotoxy(29, 10);
    textcolor(YELLOW);
   	cprintf("[0] : Help");
   	gotoxy(29, 11);
    textcolor(BLUE);
   	cprintf("[1] : Make Reservation");
   	gotoxy(29, 12);
   	cprintf("[2] : Cancel Reservation");
   	gotoxy(29, 13);
   	cprintf("[3] : Search Reservation");
   	gotoxy(29, 14);
   	cprintf("[4] : Edit Reservation");
   	gotoxy(29, 15);
   	cprintf("[5] : View Reservation");
   	gotoxy(29, 16);
    textcolor(YELLOW);
   	cprintf("[7] : Go Back");
   	gotoxy(29, 17);
    textcolor(RED);
   	cprintf("[9] : Exit");
   	gotoxy(3, 21);
   	textcolor(LIGHTGRAY + BLINK);
   	cprintf("Select an option...");
   	textcolor(LIGHTGRAY);
   	gotoxy(USER_X, USER_Y);
}



/*----------------------------------------------------------*
 *                 FUNCTION : reserv_help()                 *
 *----------------------------------------------------------*/

void reserv_help(void)
{
	prepare_screen();
    textcolor(BLUE);
   	gotoxy(39, 7);
   	cprintf("HELP");
   	gotoxy(39, 8);
   	cprintf("----");
   	gotoxy(15, 11);
   	cprintf("Press the number related to the function you ");
   	cprintf("want to");
   	gotoxy(13, 12);
   	cprintf("perform.   Press \'0\' to view this help ");
   	cprintf("screen, press \'7\'");
   	gotoxy(17, 13);
   	cprintf("to go back to the previous menu or press \'9\'");
   	cprintf(" to");
   	gotoxy(21, 14);
   	cprintf("exit the system, once you are prompted.");
   	gotoxy(3, 21);
   	textcolor(LIGHTGRAY + BLINK);
   	cprintf("Press ENTER to continue...");
   	textcolor(LIGHTGRAY);
   	gotoxy(USER_X, USER_Y);
}



/*----------------------------------------------------------*
 *                 FUNCTION : exit_screen()                 *
 *----------------------------------------------------------*/

void exit_screen(void)
{
	prepare_screen();
    textcolor(BLUE);
   	gotoxy(35, 8);
   	cprintf("FLIGHT WHIZZ");
   	gotoxy(28, 10);
   	cprintf("Flight Reservation System!");
   	gotoxy(40, 12);
   	cprintf("by");
   	gotoxy(33, 14);
   	cprintf("Sandeep Ellawala");
   	gotoxy(38, 16);
   	cprintf("[2007]");
   	gotoxy(3, 21);
   	textcolor(LIGHTGRAY+BLINK);
   	cprintf("Press ENTER to terminate program...");
   	textcolor(LIGHTGRAY);
	gotoxy(USER_X, USER_Y);
}



/*----------------------------------------------------------*
 *                 FUNCTION : edit_reserv()                 *
 *----------------------------------------------------------*/

void edit_reserv(void)
{
	char edppn[9], edfid[7];

	FILE *fpr;
	FILE *fpt;

	char fid[7];
	char name[30];
	char address[70];
	char ppn[9];
	char ccn[17];
	char phone[16];

	prepare_screen();
    textcolor(BLUE);
   	gotoxy(33, 8);
   	cprintf("EDIT RESERVATION");
   	gotoxy(32, 9);
   	cprintf("----------------");
   	gotoxy(5, 12);
   	cprintf("Passport No.      : ");
   	gotoxy(5, 15);
   	cprintf("Flight ID         : ");

    gotoxy(3, 21);
    cprintf("                                              ");
   	gotoxy(3, 21);
   	textcolor(LIGHTGRAY + BLINK);
   	cprintf("Enter customer\'s passport number...");
   	textcolor(LIGHTGRAY);
   	gotoxy(USER_X, USER_Y);
   	fflush(stdin);
   	gets(edppn);
   	gotoxy(25, 12);
    textcolor(BLUE);
   	cprintf("%s", edppn);

   	gotoxy(3, 21);
    cprintf("                                              ");
   	textcolor(LIGHTGRAY + BLINK);
   	cprintf("Enter flight id...");
   	textcolor(LIGHTGRAY);
   	gotoxy(USER_X, USER_Y);
   	cprintf("                                              ");
   	gotoxy(USER_X, USER_Y);
   	fflush(stdin);
   	gets(edfid);
   	gotoxy(25, 15);
    textcolor(BLUE);
   	cprintf("%s", edfid);

	fpr = fopen(RESERV_FILE, "r");
	fpt = fopen(TEMPRE_FILE, "w");

	while(!feof(fpr))
	{
		fscanf(fpr,
        "%[^!]%*c%[^!]%*c%[^!]%*c%[^!]%*c%[^!]%*c%[^!]%*c%*c",
        name, address, phone, ppn, ccn, fid);

		if(feof(fpr))
		{
			break;
		}
        /*One passport number can have many reservations in
          different flights but not in the same flight.  To
          edit a reservation, both passport number and the
          flight number should match.                       */

		if((strcmpi(edppn, ppn)) == 0)
		{
        	if((strcmpi(edfid, fid)) == 0)
            {
				prepare_screen();
                textcolor(BLUE);
                gotoxy(35, 5);
                cprintf("EDIT RESERVAION");
                gotoxy(35, 6);
                cprintf("---------------");
                gotoxy(5, 8);
                cprintf("Name              : %s", name);
                gotoxy(5, 10);
                cprintf("Address           : %s", address);
                gotoxy(5, 12);
                cprintf("Flight ID         : %s", fid);
                gotoxy(5, 14);
                cprintf("PP Number         : %s", ppn);
                gotoxy(5, 16);
                cprintf("CC Number         : %s", ccn);
                gotoxy(5, 18);
                cprintf("Phone             : %s", phone);

                gotoxy(3, 21);
    			textcolor(LIGHTGRAY + BLINK);
   				cprintf("Enter customer name...");
   				textcolor(LIGHTGRAY);
   				gotoxy(USER_X, USER_Y);
   				fflush(stdin);
   				gets(name);
   				gotoxy(25, 8);
   				cprintf("                                  ");
   				gotoxy(25, 8);
                textcolor(BLUE);
   				cprintf("%s", name);

                gotoxy(3, 21);
    			cprintf("                                  ");
   				gotoxy(3, 21);
   				textcolor(LIGHTGRAY + BLINK);
   				cprintf("Enter customer passport number...");
   				textcolor(LIGHTGRAY);
   				gotoxy(USER_X, USER_Y);
   				cprintf("                                  ");
   				gotoxy(USER_X, USER_Y);
   				fflush(stdin);
                gets(ppn);
   				gotoxy(25, 14);
   				cprintf("                                  ");
   				gotoxy(25, 14);
                textcolor(BLUE);
   				cprintf("%s", ppn);

                gotoxy(3, 21);
    			cprintf("                                  ");
   				gotoxy(3, 21);
   				textcolor(LIGHTGRAY + BLINK);
   				cprintf("Enter customer\'s address...");
   				textcolor(LIGHTGRAY);
   				gotoxy(USER_X, USER_Y);
   				cprintf("                                  ");
   				gotoxy(USER_X, USER_Y);
   				fflush(stdin);
   				gets(address);
   				gotoxy(25, 10);
   				cprintf("                                  ");
   				gotoxy(25, 10);
                textcolor(BLUE);
   				cprintf("%s", address);

                gotoxy(3, 21);
    			cprintf("                                  ");
   				gotoxy(3, 21);
   				textcolor(LIGHTGRAY + BLINK);
   				cprintf("Enter customer\'s phone number...");
   				textcolor(LIGHTGRAY);
   				gotoxy(USER_X, USER_Y);
   				cprintf("                                  ");
   				gotoxy(USER_X, USER_Y);
   				fflush(stdin);
   				gets(phone);
   				gotoxy(25, 18);
   				cprintf("                                  ");
   				gotoxy(25, 18);
                textcolor(BLUE);
   				cprintf("%s", phone);

                gotoxy(3, 21);
    			cprintf("                                  ");
   				gotoxy(3, 21);
   				textcolor(LIGHTGRAY + BLINK);
   				cprintf("Enter customer\'s credit card \
                								  number...");
   				textcolor(LIGHTGRAY);
   	 			gotoxy(USER_X, USER_Y);
   				cprintf("                                  ");
   				gotoxy(USER_X, USER_Y);
   				fflush(stdin);
   				gets(ccn);
   				gotoxy(25, 16);
   				cprintf("                                  ");
   				gotoxy(25, 16);
                textcolor(BLUE);
   				cprintf("%s", ccn);

                gotoxy(3, 21);
    			cprintf("                                  ");
   				textcolor(LIGHTGRAY + BLINK);
   				cprintf("Enter flight id...");
   				textcolor(LIGHTGRAY);
   				gotoxy(USER_X, USER_Y);
   				cprintf("                                  ");
   				gotoxy(USER_X, USER_Y);
   				fflush(stdin);
   				gets(fid);
   				gotoxy(25, 12);
   				cprintf("                                  ");
   				gotoxy(25, 12);
                textcolor(BLUE);
   				cprintf("%s", fid);

                gotoxy(3, 21);
    			cprintf("                                  ");
   				gotoxy(3, 21);
   				textcolor(LIGHTGRAY + BLINK);
   				cprintf("Press ENTER to continue...");
   				textcolor(LIGHTGRAY);
   				gotoxy(USER_X, USER_Y);
   				get_prompt(USER_X, USER_Y);
            }
		}
		fprintf(fpt, "%s!%s!%s!%s!%s!%s!\n", name, address,
        							    phone, ppn, ccn, fid);
	}

	fflush(fpt);
	fclose(fpr);
	fclose(fpt);

	remove(RESERV_FILE);
	rename(TEMPRE_FILE, RESERV_FILE);
}



/*----------------------------------------------------------*
 *                  FUNCTION : view_reserv()                *
 *----------------------------------------------------------*/

void view_reserv(void)
{
	FILE *fp;

	char fid[7];
	char name[30];
	char address[70];
	char ppn[9];
	char ccn[17];
	char phone[16];

	if((fp = fopen(RESERV_FILE, "r")) == NULL)
	{
		fp = fopen(RESERV_FILE, "w");
		fclose(fp);
	}
	else
	{
		while(!feof(fp))
		{
			fscanf(fp,
        "%[^!]%*c%[^!]%*c%[^!]%*c%[^!]%*c%[^!]%*c%[^!]%*c%*c",
        name, address, phone, ppn, ccn, fid);
			if(feof(fp))
			{
				break;
			}
			prepare_screen();
            textcolor(BLUE);
      		gotoxy(32, 4);
      		cprintf("VIEW RESERVATIONS");
            gotoxy(32, 5);
            cprintf("-----------------");
      		gotoxy(5, 7);
      		cprintf("Name              : %s", name);
      		gotoxy(5, 9);
      		cprintf("Passport No.      : %s", ppn);
      		gotoxy(5, 11);
      		cprintf("Address           : %s", address);
      		gotoxy(5, 13);
      		cprintf("Phone No.         : %s", phone);
      		gotoxy(5, 15);
      		cprintf("Credit Card No.   : %s", ccn);
      		gotoxy(5, 17);
      		cprintf("Flight ID         : %s", fid);
      		gotoxy(3, 21);
      		textcolor(LIGHTGRAY + BLINK);
      		cprintf("Press ENTER to continue...");
      		textcolor(LIGHTGRAY);
      		get_prompt(USER_X, USER_Y);
		}
	}
	fclose(fp);
}



/*----------------------------------------------------------*
 *                 FUNCTION : flight_menu()                 *
 *----------------------------------------------------------*/

void flight_menu(void)
{
	prepare_screen();
    textcolor(BLUE);
	gotoxy(30, 6);
   	cprintf("FLIGHT COMMAND MENU");
   	gotoxy(30, 7);
   	cprintf("-------------------");
   	gotoxy(28, 10);
    textcolor(YELLOW);
   	cprintf("[0] : Help");
   	gotoxy(28, 11);
    textcolor(BLUE);
   	cprintf("[1] : Add New Flight");
   	gotoxy(28, 12);
   	cprintf("[2] : Cancel Flight");
   	gotoxy(28, 13);
    cprintf("[3] : Search Flight");
   	gotoxy(28, 14);
   	cprintf("[4] : Edit Flight Details");
   	gotoxy(28, 15);
   	cprintf("[5] : View Flights");
   	gotoxy(28, 16);
    textcolor(YELLOW);
   	cprintf("[7] : Go Back");
   	gotoxy(28, 17);
    textcolor(RED);
   	cprintf("[9] : Exit");
   	gotoxy(3, 21);
   	textcolor(LIGHTGRAY + BLINK);
   	cprintf("Select an option...");
   	textcolor(LIGHTGRAY);
   	gotoxy(USER_X, USER_Y);
}



/*----------------------------------------------------------*
 *                 FUNCTION : flight_help()                 *
 *----------------------------------------------------------*/

void flight_help(void)
{
	prepare_screen();
    textcolor(BLUE);
   	gotoxy(39, 7);
  	cprintf("HELP");
   	gotoxy(39, 8);
   	cprintf("----");
   	gotoxy(15, 11);
   	cprintf("Press the number related to the function you ");
   	cprintf("want to");
   	gotoxy(13, 12);
   	cprintf("perform.   Press \'0\' to view this help ");
   	cprintf("screen, press \'7\'");
   	gotoxy(17, 13);
   	cprintf("to go back to the previous menu or press \'9\'");
   	cprintf(" to");
   	gotoxy(21, 14);
   	cprintf("exit the system, once you are prompted.");
   	gotoxy(3, 21);
   	textcolor(LIGHTGRAY + BLINK);
   	cprintf("Press ENTER to continue...");
   	textcolor(LIGHTGRAY);
   	gotoxy(USER_X, USER_Y);
}



/*----------------------------------------------------------*
 *                FUNCTION : edit_flight()                  *
 *----------------------------------------------------------*/

void edit_flight(void)
{
	char edid[7];

	FILE *fpf;
	FILE *fpt;

	char fid[7];
	char destin[20];
	int seats;
	float price;
	int dd, mm, yy;
	int dhh, dmm;
	int ahh, amm;

    prepare_screen();
	gotoxy(3, 21);
   	textcolor(LIGHTGRAY + BLINK);
   	cprintf("Enter flight id to edit...");
   	textcolor(LIGHTGRAY);
   	gotoxy(USER_X, USER_Y);
   	fflush(stdin);
   	gets(edid);

	fpf = fopen(FLIGHT_FILE, "r");
	fpt = fopen(TEMPFL_FILE, "w");

	while(!feof(fpf))
	{
		fscanf(fpf,
        	"%[^/]%*c%[^/]%*c%i %f %i %i %i %i %i %i %i%*c",
            fid, destin, &seats, &price, &dd, &mm, &yy, &dhh,
            &dmm, &ahh, &amm);
		if(feof(fpf))
		{
			break;
		}
		if((strcmpi(edid, fid)) == 0)
		{
			prepare_screen();
            textcolor(BLUE);
            gotoxy(35, 3);
            cprintf("EDIT RESERVATION");
            gotoxy(35, 4);
            cprintf("----------------");
            gotoxy(5, 6);
			cprintf("Flight ID             : %s", fid);
            gotoxy(5, 7);
			cprintf("Destination           : %s", destin);
            gotoxy(5, 8);
			cprintf("Seats                 : %i", seats);
            gotoxy(5, 9);
			cprintf("Price                 : %5.2f", price);
            gotoxy(5, 10);
			cprintf("Date                  : %02i/%02i/%04i",
            									  dd, mm, yy);
            gotoxy(5, 11);
			cprintf("Dep                   : %02i:%02i", dhh,
            											 dmm);
            gotoxy(5, 12);
			cprintf("Arr                   : %02i:%02i", ahh,
            											 amm);
			get_prompt(USER_X, USER_Y);

            gotoxy(5, 15);
			cprintf("Price                 : ");
			fflush(stdin);
			scanf("%f", &price);
            gotoxy(5, 16);
			printf("Date [d/m/y]           : ");
			fflush(stdin);
			scanf("%i/%i/%i", &dd, &mm, &yy);
            gotoxy(5, 17);
			cprintf("Dep [h:m]             : ");
			fflush(stdin);
			scanf("%i:%i", &dhh, &dmm);
            gotoxy(5, 18);
			cprintf("Arr [h:m]             : ");
			fflush(stdin);
			scanf("%i:%i", &ahh, &amm);
		}
		fprintf(fpt, "%s/%s/%i %.2f %i %i %i %i %i %i %i\n",
        	fid, destin, seats, price, dd, mm, yy, dhh, dmm,
            ahh, amm);
	}

	fflush(fpt);
	fclose(fpf);
	fclose(fpt);
    
	remove(FLIGHT_FILE);
	rename(TEMPFL_FILE, FLIGHT_FILE);
}



/*----------------------------------------------------------*
 *                FUNCTION : admin_login()                  *
 *----------------------------------------------------------*/

void admin_login(void)
{
	char menuOpt;

    exitF = NO;
    loggF = NO;
    backF = NO;

    init_sys();

    do
    {
    	if(loggF == NO)
        {
        	adm_pwd();
        }
        else
        {
        	admin_menu();
            fflush(stdin);
            menuOpt = (char)getche();
            switch(menuOpt)
            {
            	case CMD_HELP:
                {
                	admin_help();
                    get_prompt(USER_X, USER_Y);
                    break;
                }
                case '1':
                {
                	upwd_change();
                    break;
                }
                case '2':
                {
                	apwd_change();
                    break;
                }
                case '3':
                {
                	cryk_change();
                    break;
                }
                case CMD_LOFF:
                {
                	confirm_logoff();
                    break;
                }
                case CMD_EXIT:
                {
                	confirm_exit();
                    break;
                }
                default:
                {
                	invalid_option();
                    get_prompt(USER_X, USER_Y);
                    break;
                }
            }
        }
    }while(exitF == NO && backF == NO);
    backF = NO;
}



/*----------------------------------------------------------*
 *                 FUNCTION : upwd_change()                 *
 *----------------------------------------------------------*/

void upwd_change(void)
{
	char upwd[9], confirm[9], cryptK[9];

    FILE *fp;

    unsigned int ctr;
    FLAG validF;

    fp = fopen(CRYPTK_FILE, "r");
    fread(cryptK, sizeof(char), 9, fp);
    fclose(fp);

    prepare_screen();
    gotoxy(3, 21);
    textcolor(LIGHTGRAY + BLINK);
    cprintf("Enter the new password...");
    textcolor(LIGHTGRAY);
    gotoxy(USER_X, USER_Y);
    fflush(stdin);
    gets(upwd);

    prepare_screen();
    gotoxy(3, 21);
    textcolor(LIGHTGRAY + BLINK);
    cprintf("Enter the new password to confirm...");
    textcolor(LIGHTGRAY);
    gotoxy(USER_X, USER_Y);
    fflush(stdin);
    gets(confirm);
    if((strncmp(upwd, confirm, 8)) == 0)
    {
    	validF = YES;
    }
    if(validF == YES)
    {
    	for(ctr = 0; ctr < 8; ctr++)
    	{
    		upwd[ctr] ^= cryptK[ctr];
    	}
        prepare_screen();
        textcolor(LIGHTGREEN + BLINK);
        gotoxy(3, 21);
        cprintf("Password changed successfully...");
        textcolor(LIGHTGRAY);
        get_prompt(USER_X, USER_Y);
    	fp = fopen(USRPWD_FILE, "w");
        fwrite(upwd, sizeof(char), 9, fp);
    	fclose(fp);
    }
    else
    {
    	prepare_screen();
        gotoxy(3, 21);
        textcolor(LIGHTRED + BLINK);
        cprintf("Invalid password change...");
        textcolor(LIGHTGRAY);
        get_prompt(USER_X, USER_Y);
    }
}



/*----------------------------------------------------------*
 *                 FUNCTION : apwd_change()                 *
 *----------------------------------------------------------*/

void apwd_change(void)
{
	char apwd[9];
    char confirm[9];
    char cryptK[9];

    FILE *fp;

    unsigned int ctr;
    FLAG validF;

    fp = fopen(CRYPTK_FILE, "r");
    fread(cryptK, sizeof(char), 9, fp);
    fclose(fp);

    prepare_screen();
    gotoxy(3, 21);
    textcolor(LIGHTGRAY + BLINK);
    cprintf("Enter the new password...");
    textcolor(LIGHTGRAY);
    gotoxy(USER_X, USER_Y);
    fflush(stdin);
    gets(apwd);

    prepare_screen();
    gotoxy(3, 21);
    textcolor(LIGHTGRAY + BLINK);
    cprintf("Enter the new password to confirm...");
    textcolor(LIGHTGRAY);
    gotoxy(USER_X, USER_Y);
    fflush(stdin);
    gets(confirm);

    if((strncmp(apwd, confirm, 8)) == 0)
    {
       	validF = YES;
    }
    if(validF == YES)
    {
    	for(ctr = 0; ctr < 8; ctr++)
    	{
		apwd[ctr] ^= cryptK[ctr];
    	}
        prepare_screen();
        textcolor(LIGHTGREEN + BLINK);
        gotoxy(3, 21);
        cprintf("Password changed successfully...");
        get_prompt(USER_X, USER_Y);

    	fp = fopen(ADMPWD_FILE, "w");
        fwrite(apwd, sizeof(char), 9, fp);
    	fclose(fp);
    }
    else
    {
    	prepare_screen();
        gotoxy(3, 21);
        textcolor(LIGHTRED + BLINK);
        cprintf("Invalid password change...");
        textcolor(LIGHTGRAY);
        get_prompt(USER_X, USER_Y);
    }
}



/*----------------------------------------------------------*
 *                 FUNCTION : cryk_change()                 *
 *----------------------------------------------------------*/

void cryk_change(void)
{
	FILE *fp;

    FLAG validF = NO;
    char buf[9], cryptK[9];
    unsigned int ctr;

    prepare_screen();
    gotoxy(3, 21);
    textcolor(LIGHTGRAY + BLINK);
    cprintf("Enter new crypt key...");
    textcolor(LIGHTGRAY);
    gotoxy(USER_X, USER_Y);
    fflush(stdin);
    gets(cryptK);


    strcpy(buf, "makiwara");

    if((strlen(cryptK)) == (strlen(buf)))
    {
    	validF = YES;
    }

    if(validF == YES)
    {
    	fp = fopen(CRYPTK_FILE, "w");
    	fwrite(cryptK, sizeof(char), 9, fp);
        fclose(fp);
        for(ctr = 0; ctr < 8; ctr++)
        {
        	buf[ctr] ^= cryptK[ctr];
        }
        prepare_screen();
        textcolor(LIGHTGREEN + BLINK);
        gotoxy(3, 21);
        cprintf("Encryption key changed successfully...");
        get_prompt(USER_X, USER_Y);
        fp = fopen(ADMPWD_FILE, "w");
        fwrite(buf, sizeof(char), 9, fp);
        fclose(fp);
        fp = fopen(USRPWD_FILE, "w");
        fwrite(buf, sizeof(char), 9, fp);
        fclose(fp);
    }
    else
    {
    	prepare_screen();
        gotoxy(3, 21);
        textcolor(LIGHTRED + BLINK);
        cprintf("Invalid change of crypt key...");
        textcolor(LIGHTGRAY);
        get_prompt(USER_X, USER_Y);
    }
}



/*----------------------------------------------------------*
 *                FUNCTION : confirm_exit()                 *
 *----------------------------------------------------------*/

void confirm_exit(void)
{
   	char option;

	prepare_screen();
    textcolor(RED);
   	gotoxy(37, 9);
   	cprintf("WARNING!");
   	gotoxy(37, 10);
   	cprintf("--------");
   	gotoxy(12, 13);
   	cprintf("Are you sure you want to exit from the program");
   	cprintf(" : [Y / N]");
   	gotoxy(3, 21);
   	textcolor(LIGHTGRAY + BLINK);
   	cprintf("Select option...");
   	textcolor(LIGHTGRAY);
   	gotoxy(USER_X, USER_Y);
   	fflush(stdin);
   	option = (char)getche();
   	switch(option)
   	{
   		case 'Y': //falls through
      	case 'y':
      	{
      		exitF = YES;
         	break;
      	}
      	case 'N': //falls through
      	case 'n':
      	{
      		exitF = NO;
         	break;
      	}
      	default:
      	{
      		invalid_option();
         	get_prompt(USER_X, USER_Y);
         	exitF = NO;
         	break;
      	}
   	}
}




/*----------------------------------------------------------*
 *                FUNCTION : view_flights()                 *
 *----------------------------------------------------------*/

void view_flights(void)
{
	FILE *fp;

	char fid[7];
	char destin[20];
	int seats;
	float price;
	int dd, mm, yy;
	int dhh, dmm;
	int ahh, amm;
    int loc;
    int line = 19;

	if((fp = fopen(FLIGHT_FILE, "r")) == NULL)
	{
		fp = fopen(FLIGHT_FILE, "w");
		fclose(fp);
	}
	else
	{
    	prepare_screen();

		while(!feof(fp))
		{
			fscanf(fp,
            "%[^/]%*c%[^/]%*c%i %f %i %i %i %i %i %i %i%*c",
            fid, destin, &seats, &price, &dd, &mm, &yy, &dhh,
            &dmm, &ahh, &amm);
			if(feof(fp))
			{
				break;
			}
            if(line > 18)
      		{
      			gotoxy(3, 21);
         		textcolor(LIGHTGRAY + BLINK);
         		cprintf("Press ENTER to continue...");
         		textcolor(LIGHTGRAY);
         		gotoxy(USER_X, USER_Y);
         		get_prompt(USER_X, USER_Y);
         		line = 6;

         		prepare_screen();
                textcolor(YELLOW);
         		gotoxy(7, 3);
         		cprintf("FID");
         		gotoxy(7, 4);
         		cprintf("---");
         		gotoxy(14, 3);
         		cprintf("DESTINATION");
         		gotoxy(14, 4);
         		cprintf("-----------");
         		gotoxy(28, 3);
         		cprintf("SEATS");
         		gotoxy(28, 4);
         		cprintf("-----");
         		gotoxy(36, 3);
         		cprintf("PRICE");
         		gotoxy(36, 4);
         		cprintf("-----");
         		gotoxy(46, 3);
         		cprintf("DATE");
         		gotoxy(46, 4);
         		cprintf("----");
         		gotoxy(55, 3);
         		cprintf("DEPARTURE");
         		gotoxy(55, 4);
         		cprintf("---------");
         		gotoxy(67, 3);
         		cprintf("ARRIVAL");
         		gotoxy(67, 4);
         		cprintf("-------");
      		}
      		if(seats > 0)
            {
            	textcolor(BLUE); /*All the valid flights are
                                   displayed in blue.       */
            }
            else
            {
            	textcolor(LIGHTGRAY);/*All the invalid flight
                                       details are displayed
                                       in gray.             */
            }
            gotoxy(6, line);
            cprintf("%s", fid);

            /*Destination is being centered using the values
              calculated by the following code.             */
            loc = (int)(strlen(destin) / 2);
            loc = 8 - loc;
            loc += 11;

            gotoxy(loc, line);
            cprintf("%s", destin);
            gotoxy(29, line);
            cprintf("%03i", seats);
            gotoxy(35, line);
            cprintf("%.2f", price);
            gotoxy(44, line);
            cprintf("%02i/%02i/%04i", dd, mm, yy);
            gotoxy(57, line);
            cprintf("%02i:%02i", dhh, dmm);
            gotoxy(68, line);
            cprintf("%02i:%02i", ahh, amm);

            /*Printing is done skipping a line per a record
              being printed.                                */
            line += 2;
        }
        gotoxy(3, 21);
   		textcolor(LIGHTGRAY + BLINK);
   		cprintf("Press ENTER to go back to previous menu...");
   		textcolor(LIGHTGRAY);
   		gotoxy(USER_X, USER_Y);
   		get_prompt(USER_X, USER_Y);
    }

	fclose(fp);
}



/*----------------------------------------------------------*
 *                FUNCTION : cancel_reserv()                *
 *----------------------------------------------------------*/

void cancel_reserv(void)
{
	char delppn[9], delfid[7];

	FILE *fpr;
	FILE *fpt;
    FILE *fpf;

    /*These variables are used to read the data from the
      reservations master file.                             */

	char fid[7];
	char name[30];
	char address[70];
	char ppn[9];
	char ccn[17];
	char phone[16];

    /*These variables are used to read the data from the
      flight master file.                                   */

    char tfid[7];
	char tdestin[20];
	int tseats;
	float tprice;
	int tdd, tmm, tyy;
	int tdhh, tdmm;
	int tahh, tamm;

    FLAG validF = NO;

	fpr = fopen(RESERV_FILE, "r");
	fpt = fopen(TEMPRE_FILE, "w");

	prepare_screen();
    textcolor(BLUE);
   	gotoxy(32, 8);
   	cprintf("CANCEL RESERVATION");
   	gotoxy(32, 9);
   	cprintf("------------------");
   	gotoxy(5, 12);
   	cprintf("Passport No.      : ");
   	gotoxy(5, 15);
   	cprintf("Flight ID         : ");

   	gotoxy(3, 21);
   	textcolor(LIGHTGRAY + BLINK);
   	cprintf("Enter customer\'s passport number...");
   	textcolor(LIGHTGRAY);
   	gotoxy(USER_X, USER_Y);
   	fflush(stdin);
   	gets(delppn);
   	gotoxy(25, 12);
    textcolor(BLUE);
   	cprintf("%s", delppn);

   	gotoxy(3, 21);
   	textcolor(LIGHTGRAY + BLINK);
   	cprintf("Enter flight id...");
   	textcolor(LIGHTGRAY);
   	gotoxy(USER_X, USER_Y);
   	cprintf("                                              ");
   	gotoxy(USER_X, USER_Y);
   	fflush(stdin);
   	gets(delfid);
   	gotoxy(25, 15);
    textcolor(BLUE);
   	cprintf("%s", fid);

	while(!feof(fpr))
	{
		fscanf(fpr,
        "%[^!]%*c%[^!]%*c%[^!]%*c%[^!]%*c%[^!]%*c%[^!]%*c%*c",
        name, address, phone, ppn, ccn, fid);

		if(feof(fpr))
		{
			break;
		}

		if((strncmpi(delppn, ppn, strlen(delppn) - 1)) != 0)
		{
			fprintf(fpt, "%s!%s!%s!%s!%s!%s!\n", name,
            address, phone, ppn, ccn, fid);
		}
        else
        {
        	if((strncmpi(delfid, fid,
            						strlen(delfid) - 1)) != 0)
            {
            	fprintf(fpt, "%s!%s!%s!%s!%s!%s!\n", name,
                address, phone, ppn, ccn, fid);
            }
            else
            {
            	validF = YES;
            }
        }
	}

	fflush(fpt);
	fclose(fpr);
	fclose(fpt);

    /*If a particular passport number is used to reserv a
      seat in a flight, that one can only be deleted if both
      the passport number and the flight id match.          */

    if(validF == YES)
    {
		remove(RESERV_FILE);
		rename(TEMPRE_FILE, RESERV_FILE);

        fpf = fopen(FLIGHT_FILE, "r");
        fpt = fopen(TEMPFL_FILE, "w");

        while(!feof(fpf))
    	{
    		fscanf(fpf,
            "%[^/]%*c%[^/]%*c%i %f %i %i %i %i %i %i %i%*c",
            tfid, tdestin, &tseats, &tprice, &tdd, &tmm, &tyy,
            &tdhh, &tdmm, &tahh, &tamm);
			if(feof(fpf))
			{
				break;
			}
			if((strcmpi(tfid, delfid)) == 0)
			{
               	tseats++;
        	}
        	fprintf(fpt,
            "%s/%s/%i %.2f %i %i %i %i %i %i %i\n", tfid,
            tdestin, tseats, tprice, tdd, tmm, tyy, tdhh,
            tdmm, tahh, tamm);
    	}

        fclose(fpt);
        fclose(fpf);

        remove(FLIGHT_FILE);
        rename(TEMPFL_FILE, FLIGHT_FILE);
    }
    else
    {
    	prepare_screen();
        textcolor(LIGHTRED + BLINK);
        cprintf("Unable to locate the record...");
        textcolor(LIGHTGRAY);
        get_prompt(USER_X, USER_Y);
    }
}




/*----------------------------------------------------------*
 *                FUNCTION : search_reserv()                *
 *----------------------------------------------------------*/

void search_reserv(void)
{
	char seappn[9];

	FILE *fpr;
	FILE *fpt;

	char fid[7];
	char name[30];
	char address[70];
	char ppn[9];
	char ccn[17];
	char phone[16];

	FLAG foundF = NO;

	fpr = fopen(RESERV_FILE, "r");
	fpt = fopen(TEMPRE_FILE, "w");



	prepare_screen();
    textcolor(BLUE);
    gotoxy(32, 7);
    cprintf("SEARCH RESERVATIONS");
    gotoxy(32, 8);
    cprintf("-------------------");
    gotoxy(3, 21);
    textcolor(LIGHTGRAY + BLINK);
	printf("Enter the search PP Number  : ");
    textcolor(LIGHTGRAY);
	fflush(stdin);
    gotoxy(USER_X, USER_Y);
	gets(seappn);

	while(!feof(fpr))
	{
		fscanf(fpr,
        "%[^!]%*c%[^!]%*c%[^!]%*c%[^!]%*c%[^!]%*c%[^!]%*c%*c",
        name, address, phone, ppn, ccn, fid);

		if(feof(fpr))
		{
			break;
		}

		if((strcmpi(seappn, ppn)) == 0)
		{
			fprintf(fpt, "%s!%s!%s!%s!%s!%s!\n", name,
            address, phone, ppn, ccn, fid);
            foundF = YES;
		}
	}

	fflush(fpt);
	fclose(fpr);
	fclose(fpt);

	fpt = fopen(TEMPRE_FILE, "r");

	while(!feof(fpt))
	{
		fscanf(fpt,
        "%[^!]%*c%[^!]%*c%[^!]%*c%[^!]%*c%[^!]%*c%[^!]%*c%*c",
        name, address, phone, ppn, ccn, fid);

		if(feof(fpt))
		{
			break;
		}

		prepare_screen();
        textcolor(BLUE);
      	gotoxy(32, 4);
      	cprintf("SEARCH RESERVATIONS");
        gotoxy(32, 5);
        cprintf("-------------------");
      	gotoxy(5, 7);
      	cprintf("Name              : %s", name);
      	gotoxy(5, 9);
      	cprintf("Passport No.      : %s", ppn);
      	gotoxy(5, 11);
      	cprintf("Address           : %s", address);
      	gotoxy(5, 13);
      	cprintf("Phone No.         : %s", phone);
      	gotoxy(5, 15);
      	cprintf("Credit Card No.   : %s", ccn);
      	gotoxy(5, 17);
      	cprintf("Flight ID         : %s", fid);
      	gotoxy(3, 21);
      	textcolor(LIGHTGRAY + BLINK);
      	cprintf("Press ENTER to continue...");
      	textcolor(LIGHTGRAY);
      	get_prompt(USER_X, USER_Y);
	}

    if(foundF == NO)
    {
    	prepare_screen();
        textcolor(LIGHTRED + BLINK);
        cprintf("Record can not be located...");
        textcolor(LIGHTGRAY);
        get_prompt(USER_X, USER_Y);
    }
    else
    {
		fclose(fpt);
    	gotoxy(3, 21);
   		textcolor(LIGHTGRAY + BLINK);
   		cprintf("Press ENTER to go back to previous menu...");
   		textcolor(LIGHTGRAY);
   		gotoxy(USER_X, USER_Y);
   		get_prompt(USER_X, USER_Y);
    }
}



/*----------------------------------------------------------*
 *                FUNCTION : cancel_flight()                *
 *----------------------------------------------------------*/

void cancel_flight(void)
{
	char delid[7];

	FILE *fpf;
	FILE *fpt;
    FILE *fprp;
    FILE *fpr;

    /*These variables are used to read data from the flight
      file.                                                 */

	char fid[7];
	char destin[20];
	int seats;
	float price;
	int dd, mm, yy;
	int dhh, dmm;
	int ahh, amm;

    /*These variables are used to read from the reservation
      file.                                                 */

    char tfid[7];
	char tname[30];
	char taddress[70];
	char tppn[9];
	char tccn[17];
	char tphone[16];

    FLAG foundF = NO;

	fpf = fopen(FLIGHT_FILE, "r");
	fpt = fopen(TEMPFL_FILE, "w");

	prepare_screen();
    textcolor(BLUE);
   	gotoxy(34, 7);
   	cprintf("CANCEL FLIGHT");
   	gotoxy(34, 8);
   	cprintf("-------------");
   	gotoxy(32, 13);
   	cprintf("Flight ID : ");
   	gotoxy(3, 21);
   	textcolor(LIGHTGRAY + BLINK);
   	cprintf("Enter flight id...");
   	textcolor(LIGHTGRAY);
   	gotoxy(USER_X, USER_Y);
   	fflush(stdin);
   	gets(delid);
   	gotoxy(44, 13);
    textcolor(BLUE);
   	cprintf("%s", delid);
   	gotoxy(3, 21);
   	textcolor(LIGHTGRAY + BLINK);
   	cprintf("Press ENTER to continue...");
   	textcolor(LIGHTGRAY);
   	get_prompt(USER_X, USER_Y);

	while(!feof(fpf))
	{
		fscanf(fpf,
        "%[^/]%*c%[^/]%*c%i %f %i %i %i %i %i %i %i%*c", fid,
        destin, &seats, &price, &dd, &mm, &yy, &dhh, &dmm,
        &ahh, &amm);

		if(feof(fpf))
		{
			break;
		}

		if((strcmpi(delid, fid)) != 0)
		{
			fprintf(fpt,
            "%s/%s/%i %.2f %i %i %i %i %i %i %i\n", fid,
            destin, seats, price, dd, mm, yy, dhh, dmm, ahh,
            amm);
            foundF = YES;
		}
	}

	fflush(fpt);
	fclose(fpf);
	fclose(fpt);

    if(foundF == YES)
    {
		remove(FLIGHT_FILE);
		rename(TEMPFL_FILE, FLIGHT_FILE);

        fpr = fopen(RESERV_FILE, "r");
        fprp = fopen(CANREP_FILE, "a+");
        fpt = fopen(TEMPRE_FILE, "w");

        while(!feof(fpr))
        {
        	fscanf(fpr,
        "%[^!]%*c%[^!]%*c%[^!]%*c%[^!]%*c%[^!]%*c%[^!]%*c%*c",
        tname, taddress, tphone, tppn, tccn, tfid);

        	if(feof(fpr))
            {
            	break;
            }

	    if((strcmpi(delid, tfid)) == 0)
            {
            	fprintf(fprp, "%s!%s!%s!%s!%s!%s!\n", tname,
                		  taddress, tphone, tppn, tccn, tfid);
            }
            else
            {
            	fprintf(fpt, "%s!%s!%s!%s!%s!%s!\n", tname,
            			  taddress, tphone, tppn, tccn, tfid);
            }
        }
        fclose(fpr);
        fclose(fpt);
        fclose(fprp);

        remove(RESERV_FILE);
        rename(TEMPRE_FILE, RESERV_FILE);
    }
    else
    {
    	prepare_screen();
        gotoxy(3, 21);
        textcolor(LIGHTRED + BLINK);
        cprintf("Unable to locate record...");
        textcolor(LIGHTGRAY);
        get_prompt(USER_X, USER_Y);
    }
}




/*----------------------------------------------------------*
 *                FUNCTION : search_flight()                *
 *----------------------------------------------------------*/

void search_flight(void)
{
	char seadest[20];

	FILE *fpf;
	FILE *fpt;
	char fid[7];
	char destin[20];
	int seats;
	float price;
	int dd, mm, yy;
	int dhh, dmm;
	int ahh, amm;
    int line = 19, loc;

    FLAG foundF = NO;

	fpf = fopen(FLIGHT_FILE, "r");
	fpt = fopen(TEMPFL_FILE, "w");
    
	prepare_screen();
   	gotoxy(3, 21);
   	textcolor(LIGHTGRAY + BLINK);
   	cprintf("Enter destination...");
   	textcolor(LIGHTGRAY);
   	gotoxy(USER_X, USER_Y);
   	fflush(stdin);
   	gets(seadest);

	while(!feof(fpf))
	{
		fscanf(fpf,
        "%[^/]%*c%[^/]%*c%i %f %i %i %i %i %i %i %i%*c", fid,
        destin, &seats, &price, &dd, &mm, &yy, &dhh, &dmm,
        &ahh, &amm);

		if(feof(fpf))
		{
			break;
		}

		if((strcmpi(seadest, destin)) == 0)
		{
			fprintf(fpt,
            "%s/%s/%i %.2f %i %i %i %i %i %i %i\n", fid,
            destin, seats, price, dd, mm, yy, dhh, dmm, ahh,
            amm);
            foundF = YES;
		}
	}
	fflush(fpt);
	fclose(fpf);
	fclose(fpt);

	fpt = fopen(TEMPFL_FILE, "r");
	while(!feof(fpt))
	{
		fscanf(fpt,
        "%[^/]%*c%[^/]%*c%i %f %i %i %i %i %i %i %i%*c", fid,
        destin, &seats, &price, &dd, &mm, &yy, &dhh, &dmm,
        &ahh, &amm);

		if(feof(fpt))
		{
			break;
		}

        if(line > 18)
        {
        	gotoxy(3, 21);
            textcolor(LIGHTGRAY + BLINK);
            cprintf("Press ENTER to continue...");
        	textcolor(LIGHTGRAY);
            gotoxy(USER_X, USER_Y);
            get_prompt(USER_X, USER_Y);
            line = 6;

            prepare_screen();
            textcolor(YELLOW);
            gotoxy(7, 3);
            cprintf("FID");
            gotoxy(7, 4);
            cprintf("---");
            gotoxy(14, 3);
            cprintf("DESTINATION");
            gotoxy(14, 4);
            cprintf("-----------");
            gotoxy(28, 3);
            cprintf("SEATS");
            gotoxy(28, 4);
            cprintf("-----");
            gotoxy(36, 3);
            cprintf("PRICE");
            gotoxy(36, 4);
            cprintf("-----");
            gotoxy(46, 3);
            cprintf("DATE");
            gotoxy(46, 4);
            cprintf("----");
            gotoxy(55, 3);
            cprintf("DEPARTURE");
            gotoxy(55, 4);
            cprintf("---------");
            gotoxy(67, 3);
            cprintf("ARRIVAL");
            gotoxy(67, 4);
            cprintf("-------");
        }

        /*The flights that are currently available for the
          reservations are displayed in blue.               */

        if(seats > 0)
        {
        	textcolor(BLUE);
        }

        /*The flights that are out of seats are displayed in
          light gray.                                       */
          
        else
        {
        	textcolor(LIGHTGRAY);
        }

        gotoxy(6, line);
        cprintf("%s", fid);
        loc = (int)(strlen(destin) / 2);
        loc = 8 - loc;
        loc += 11;
        gotoxy(loc, line);
        cprintf("%s", destin);
        gotoxy(29, line);
        cprintf("%03i", seats);
        gotoxy(35, line);
        cprintf("%05.2f", price);
        gotoxy(44, line);
        cprintf("%02i/%02i/%04i", dd, mm, yy);
        gotoxy(57, line);
        cprintf("%02i:%02i", dhh, dmm);
        gotoxy(68, line);
        cprintf("%02i:%02i", ahh, amm);

        /*Used to skipp a line when printing to the screen
          one record after another.                         */

        line += 2;
    }
   	gotoxy(3, 21);
   	textcolor(LIGHTGRAY + BLINK);
   	cprintf("Press ENTER to go back to previous menu...");
   	textcolor(LIGHTGRAY);
   	gotoxy(USER_X, USER_Y);
   	get_prompt(USER_X, USER_Y);
    
	fclose(fpt);
}




/*----------------------------------------------------------*
 *                 FUNCTION : get_prompt()                  *
 *----------------------------------------------------------*/

void get_prompt(int x, int y)
{
    /*holds the execution of the program until ENTER key is
      pressed.  But it will not allow other characters to be
      pressed instead.                                      */
	do
   	{
   		gotoxy(x, y);
      	fflush(stdin);
   	}while((getch()) != '\r');
}




/*----------------------------------------------------------*
 *               FUNCTION : welcome_screen()                *
 *----------------------------------------------------------*/

void welcome_screen(void)
{
	prepare_screen();
    textcolor(BLUE);
   	gotoxy(35, 8);
   	cprintf("FLIGHT WHIZZ");
   	gotoxy(28, 10);
   	cprintf("Flight Reservation System!");
   	gotoxy(40, 12);
   	cprintf("by");
   	gotoxy(33, 14);
   	cprintf("Sandeep Ellawala");
   	gotoxy(38, 16);
   	cprintf("[2007]");
   	gotoxy(3, 21);
   	textcolor(LIGHTGRAY+BLINK);
   	cprintf("Press ENTER to continue...");
   	textcolor(LIGHTGRAY);
   	gotoxy(USER_X, USER_Y);
}



/*----------------------------------------------------------*
 *                FUNCTION : invalid_option()               *
 *----------------------------------------------------------*/

void invalid_option(void)
{
	prepare_screen();
    textcolor(RED);
   	gotoxy(37, 9);
   	cprintf("WARNING!");
	gotoxy(37, 10);
   	cprintf("--------");
   	gotoxy(21, 13);
   	cprintf("The menu option you entered is invalid!");
   	gotoxy(3, 21);
   	textcolor(LIGHTGRAY + BLINK);
   	cprintf("Press ENTER to continue...");
   	textcolor(LIGHTGRAY);
   	gotoxy(USER_X, USER_Y);
}



/*----------------------------------------------------------*
 *               FUNCTION : prepare_screen()                *
 *----------------------------------------------------------*/

void prepare_screen(void)
{
	int ctr;

   	clrscr();
   	textmode(C80);
   	textcolor(GREEN);

    /*Top left corner is set.                               */
   	gotoxy(L_T_X, L_T_Y);
   	putch(LT_CHAR);

    /*Top right corner is set.                              */
   	gotoxy(R_T_X, R_T_Y);
   	putch(RT_CHAR);

	/*Bottom left corner is set.                            */
   	gotoxy(L_B_X, L_B_Y);
   	putch(LB_CHAR);

	/*Bottom right corner is set.                           */
   	gotoxy(R_B_X, R_B_Y);
   	putch(RB_CHAR);

    /*Horizontal lines are set.                             */
   	for(ctr = 3; ctr < 24; ctr++)
   	{
      	gotoxy(2, ctr);
      	putch(H_CHAR);
      	gotoxy(79, ctr);
      	putch(H_CHAR);
   	}

    /*Vertival lines are set.                               */
   	for(ctr = 3; ctr < 79; ctr++)
   	{
      	gotoxy(ctr, 2);
      	putch(V_CHAR);
      	gotoxy(ctr, 22);
      	putch(V_CHAR);
      	gotoxy(ctr, 24);
      	putch(V_CHAR);
   	}

   	textcolor(WHITE);
   	gotoxy(2, 1);
   	cprintf("E-Mail : sandeep.ellawala@yahoo.com");
   	gotoxy(60, 1);
   	cprintf("TP : +94(0)114927809");
   	gotoxy(2, 25);
   	cprintf("Version : 1.0v - beta");
   	gotoxy(74, 25);
   	cprintf("[2007]");

    /*prompt character is displayed.                        */
   	textcolor(GREEN);
   	gotoxy((USER_X - 2), USER_Y);
   	putch('>');
    gotoxy(USER_X, USER_Y);
    textcolor(LIGHTGRAY);
}



/*----------------------------------------------------------*
 *               FUNCTION : confirm_logoff()                *
 *----------------------------------------------------------*/

void confirm_logoff(void)
{
	char option;

   	prepare_screen();
    textcolor(RED);
   	gotoxy(37, 7);
   	cprintf("WARNING!");
   	gotoxy(37, 8);
   	cprintf("--------");
   	gotoxy(20, 13);
   	cprintf("Are you sure you want to log off : [Y / N]");
   	gotoxy(3, 21);
   	textcolor(LIGHTGRAY + BLINK);
   	cprintf("Select an option...");

   	textcolor(LIGHTGRAY);
   	gotoxy(USER_X, USER_Y);
   	fflush(stdin);
   	option = (char)getche();

   	switch(option)
   	{
   		case 'y': //falls through
      	case 'Y':
      	{
            backF = YES;
         	break;
      	}
        case 'n'://falls through
        case 'N':
        {
        	break;
        }
      	default:
      	{
      		invalid_option();
            get_prompt(USER_X, USER_Y);
         	break;
      	}
   	}
}



/*----------------------------------------------------------*
 *                FUNCTION : reserv_process()               *
 *----------------------------------------------------------*/

void reserv_process(void)
{
	char menuOpt;

    exitF = NO;
    backF = NO;

    do
    {
    	reserv_menu();
        fflush(stdin);
        menuOpt = (char)getche();

        switch(menuOpt)
        {
        	case CMD_HELP:
            {
            	reserv_help();
                get_prompt(USER_X, USER_Y);
                break;
            }
            case '1':
            {
            	add_reserv();
                break;
            }
            case '2':
            {
            	cancel_reserv();
                break;
            }
            case '3':
            {
            	search_reserv();
                break;
            }
            case '4':
            {
            	edit_reserv();
                break;
            }
            case '5':
            {
            	view_reserv();
                break;
            }
            case CMD_BACK:
            {
            	confirm_goback();
                break;
            }
            case CMD_EXIT:
            {
            	confirm_exit();
                break;
            }
            default:
            {
            	invalid_option();
                get_prompt(USER_X, USER_Y);
                break;
            }
        }
    }while(exitF == NO && backF == NO);

    backF = NO;
}



/*----------------------------------------------------------*
 *                FUNCTION : confirm_goback()               *
 *----------------------------------------------------------*/

void confirm_goback(void)
{
	char option;

    prepare_screen();
    textcolor(RED);
   	gotoxy(37, 7);
   	cprintf("WARNING!");
   	gotoxy(37, 8);
   	cprintf("--------");
   	gotoxy(20, 12);
   	cprintf("Are you sure you want to go back : [Y / N]");
   	gotoxy(3, 21);
   	textcolor(LIGHTGRAY + BLINK);
   	cprintf("Select an option...");

   	textcolor(LIGHTGRAY);
   	gotoxy(USER_X, USER_Y);
   	fflush(stdin);
   	option = (char)getche();

   	switch(option)
   	{
   		case 'y': //falls through
      	case 'Y':
      	{
      		backF = YES;
      		break;
      	}
      	case 'n': //falls through
      	case 'N':
      	{
      		backF = NO;
         	break;
      	}
      	default:
      	{
		invalid_option();
		get_prompt(USER_X, USER_Y);
         	break;
      	}
   	}
}



/*----------------------------------------------------------*
 *               FUNCTION : flight_process()                *
 *----------------------------------------------------------*/

void flight_process(void)
{
	char menuOpt;

    exitF = NO;
    backF = NO;

    do
    {
    	flight_menu();
        fflush(stdin);
        menuOpt = (char)getche();

        switch(menuOpt)
        {
        	case CMD_HELP:
            {
            	flight_help();
                get_prompt(USER_X, USER_Y);
                break;
            }
            case '1':
            {
            	add_flight();
                break;
            }
            case '2':
            {
            	cancel_flight();
                break;
            }
            case '3':
            {
            	search_flight();
                break;
            }
            case '4':
            {
            	edit_flight();
                break;
            }
            case '5':
            {
            	view_flights();
                break;
            }
            case CMD_BACK:
            {
            	confirm_goback();
                break;
            }
            case CMD_EXIT:
            {
            	confirm_exit();
                break;
            }
            default:
            {
            	invalid_option();
                get_prompt(USER_X, USER_Y);
                break;
            }
        }
    }while(exitF == NO && backF == NO);

    backF = NO;
}



/*----------------------------------------------------------*
 *               FUNCTION : invalid_startup()               *
 *----------------------------------------------------------*/

void invalid_startup(char *progName)
{
   	int cursorLoc;

	prepare_screen();

    /*Following calculation is used to center the program
      name on the screen.                                   */

   	cursorLoc = (40 - ((strlen(progName)) / 2)) - 2;

   	gotoxy(37, 7);
    textcolor(RED);
   	cprintf("ERROR!!!");
   	gotoxy(37, 8);
   	cprintf("--------");
   	gotoxy(32, 11);
   	cprintf("Invalid startup of");
   	gotoxy(cursorLoc, 12);
   	cprintf("%s.exe", progName);
   	gotoxy(18, 14);
   	cprintf("The correct format to startup this program in");
   	gotoxy(29, 15);
   	cprintf("command line interface : ");
   	gotoxy(cursorLoc - 4, 17);
    textcolor(LIGHTBLUE);
   	cprintf("> %s [ENTER]", progName);
   	gotoxy(3, 21);
   	textcolor(LIGHTGRAY+BLINK);
   	cprintf("Press ENTER to terminate...");
   	textcolor(LIGHTGRAY);
   	gotoxy(USER_X, USER_Y);
}

