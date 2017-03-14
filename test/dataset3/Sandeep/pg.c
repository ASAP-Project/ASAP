/*============================================================================*
 *SOURCE NAME  :    pg.c                                                      *
 *AUTHOR       :    Sandeep Ellawala                                          *
 *PURPOSE      :    This file contains the source code for a programme called *
 *                  Personality Guru.  It is used to test a person for his or *
 *                  her personality.                                          *
 *DATE         :    22.10.2008                                                *
 *PLATFORM     :    Microsoft Windows XP - SP 2.0                             *
 *                  Borland TC++ 4.5                                          *
 *                  Hardware - N/A                                            *
 *============================================================================*/




/*----------------------------------------------------------------------------*
 *                              HEADER INCLUSIONS                             *
 *----------------------------------------------------------------------------*/

# include <stdio.h>
# include <conio.h>
# include <stdlib.h>
# include <string.h>




/*----------------------------------------------------------------------------*
 *                              DEFINED CONSTANTS                             *
 *----------------------------------------------------------------------------*/

# define TRUE                         1
# define FALSE                        0

# define QUESTION_LEN               256
# define QUESTION_COUNT               5

# define ANSWER_LEN                 100
# define ANSWER_COUNT                 3

# define FILE_LEN                    20

# define DF_TEST        "default.tst\0"

# define NER_PER              "nervous"
# define NER_LIM                      4

# define MOD_PER             "moderate"
# define MOD_LIM                      8

# define DYN_PER              "dynamic"




/*----------------------------------------------------------------------------*
 *                                  DATA TYPES                                *
 *----------------------------------------------------------------------------*/


typedef unsigned short int BOOL;


typedef struct test_quest
{
    char question[QUESTION_LEN];
    char answers[ANSWER_COUNT][ANSWER_LEN];
    int marks[ANSWER_COUNT];
} TESTQ;




/*----------------------------------------------------------------------------*
 *                             FUNCTION PROTOTYPES                            *
 *----------------------------------------------------------------------------*/

void main(void);
void get_prompt(void);
void prepare_screen(void);
void invalid_start(char *);
void welcome_screen(void);
void display_menu(void);
void take_test(void);
void make_test(void);
BOOL must_exit(void);
void invalid_option(void);
void exit_screen(void);




/*----------------------------------------------------------------------------*
 *                                    main()                                  *
 *----------------------------------------------------------------------------*/

void main(void)
{
	BOOL isContinue = TRUE;
	char opt;

    	welcome_screen();

	do
	{
		/*This loop is used to give an indefinite menu to the user.*/
		display_menu();

		/*Menu option is taken from the keyboard.  The case of the letter is
		to be ignored in runtime.*/
		fflush(stdin);
		opt = (char)getch();

		switch (opt)
		{
			case 't':
		 	case 'T':    	take_test();
					break;
		 	case 'm':
		 	case 'M':	make_test();
			 		break;
		 	case 'x':
		 	case 'X':    	isContinue = must_exit();
					break;
		 	default:     	invalid_option();
					break;
		}
	} while (isContinue == TRUE);
	exit_screen();

    	/*Better to clean the screen before ending the program and returning the
      	control to the caller (OS).*/
    	clrscr();

    	return;
}




/*----------------------------------------------------------------------------*
 *                                 get_prompt()                               *
 *----------------------------------------------------------------------------*/

void get_prompt(void)
{
	/*This function provides the capability for the caller to freeze the whole
      	programe untill the user presses ENTER key of the keyboard.  All other
      	keys are ignored.*/
      	gotoxy(3, 23);
      	printf("Press [ENTER] to continue...");

    	while (getch() != '\r')
    	{
        	;
    	}
}




/*----------------------------------------------------------------------------*
 *                               prepare_screen()                             *
 *----------------------------------------------------------------------------*/

void prepare_screen(void)
{
    	/*Arranging the screen prior to performing any display bound tasks is to
      	be done here.*/
    	int ctr;
    	clrscr();

    	/*The horizontal graphics lines are drawn on the screen.*/
    	for (ctr = 2; ctr < 80; ctr++)
    	{
        	gotoxy(ctr, 4);
        	putch('*');

        	gotoxy(ctr, 24);
        	putch('*');
    	}

    	/*The vertical graphics lines are drawn on the screen.*/
    	for (ctr = 4; ctr < 25; ctr++)
    	{
        	gotoxy(2, ctr);
        	putch('*');

        	gotoxy(79, ctr);
        	putch('*');
    	}

    	/*Various text strings that remain all the time on the screen providing
      	usefull information are drawn.*/
    	gotoxy(31, 2);
    	printf("PERSONALITY GURU");

    	gotoxy(2, 2);
    	printf("1.0v");

    	/*The year of the project done.*/
    	gotoxy(76, 2);
    	printf("2008");
}




/*----------------------------------------------------------------------------*
 *                                invalid_start()                             *
 *----------------------------------------------------------------------------*/

void invalid_start(char *name)
{
    /*Only invoked if the programe started in an unexpected manner.*/
    prepare_screen();

    gotoxy(31, 9);
    printf("Invalid Startup!");

    gotoxy(((strlen(name) + 6) / 2) - 1, 13);
    printf("Try > %s", name);

    get_prompt();
}




/*----------------------------------------------------------------------------*
 *                                welcome_screen()                            *
 *----------------------------------------------------------------------------*/

void welcome_screen(void)
{
    /*A simple welcome greeting is printed on the screen.*/
    prepare_screen();

    gotoxy(35, 9);
    printf("WELCOME");

    gotoxy(38, 11);
    printf("to");

    gotoxy(31, 13);
    printf("PERSONALITY GURU");

    gotoxy(38, 15);
    printf("by");

    gotoxy(30, 18);
    printf("Rajiv Weerasinghe");

    get_prompt();
}




/*----------------------------------------------------------------------------*
 *                                 display_menu()                             *
 *----------------------------------------------------------------------------*/

void display_menu(void)
{
    /*The main menu of the programe is drawn on the screen.*/
    prepare_screen();

    gotoxy(33, 7);
    printf("Command Menu");
    gotoxy(33, 8);
    printf("------------");

    gotoxy(29, 11);
    printf("[t] : Take the test");

    gotoxy(29, 13);
    printf("[m] : Make new test");

    gotoxy(29, 15);
    printf("[x] : Exit System");

    gotoxy(3, 23);
    printf("Enter a command : ");
}




/*----------------------------------------------------------------------------*
 *                                   take_test()                              *
 *----------------------------------------------------------------------------*/

void take_test(void)
{
    FILE *fp;
    char filen[FILE_LEN];
    TESTQ quest;
    int mark, ctr, qctr, y;
    char opt;

    prepare_screen();

    gotoxy(28, 7);
    printf("Personality Guru Test");
    gotoxy(28, 8);
    printf("---------------------");

    /*There is a default test available for the PG 1.0v.  But if the user wants
      he or she can specify a different customized test designed prior to
      taking the exam.*/
    gotoxy(10, 14);
    printf("Do you wish to take the default personality test [y/n]? ");
    opt = (char)getch();

    /*The case of the option is ignored.  If yes is given, the default name is
      to be used for the test data file.*/
    switch (opt)
    {
        case 'y':
        case 'Y':    strcpy(filen, DF_TEST);
                     break;
        default:     gotoxy(25, 16);
							printf("Enter test name: __________");
							gotoxy(41, 16);
                     fflush(stdin);
                     gets(filen);
                     break;
    }

    fp = fopen(filen, "r");

    if (fp == NULL)
    {
        /*The test specified does not exist.  Better to go back to the main
          menu.*/
        prepare_screen();

        gotoxy(35, 7);
        printf("ERROR!!!");
        gotoxy(35, 8);
        printf("--------");

        gotoxy(17, 14);
        printf("The test name you have specified is invalid!");

        get_prompt();
    }
    else
    {
        /*The test data file does exist.  Now to start reading the test data
          file.*/
        qctr = 0;
        mark = 0;

        while (!(feof(fp)))
        {
				fscanf(fp, "%[^/]%*c", quest.question);

            /*Using a loop allows compile time variance of the number of
              answers alloed in any question.*/
            for (ctr = 0; ctr < ANSWER_COUNT; ctr++)
            {
					 fscanf(fp, "%[^/]%*c%i%*c", quest.answers[ctr],
                    &(quest.marks[ctr]));
            }

            fscanf(fp, "%*c");

            if (feof(fp))
            {
                break;
            }

            qctr++;

            prepare_screen();

            gotoxy(3, 5);
            printf("Test: %s\t\tQuestion: %i", filen, qctr);

            gotoxy(7, 7);
            printf("%s", quest.question);

            for (ctr = 0, y = 9; ctr < ANSWER_COUNT; ctr++, y += 2)
            {
                gotoxy(10, y);
                printf("[%i] : %s", (ctr + 1), quest.answers[ctr]);
            }

            gotoxy(13, ++y);
            printf("Enter answer [1-%i]: ", ANSWER_COUNT);

            fflush(stdin);
            opt = (char)getch();

            /*The answer taken from the user should be within the range of 1
              and the number of answers allowed.  The number of answers allowed
              added to 48 gives the char value of that int.  Eg. 0 = 48, 1 = 49,
				  2 = 50, etc.*/
				if (opt >= '1' && opt <= (ANSWER_COUNT + 48))
				{
					 mark += quest.marks[opt - 49];
				}
            else
				{
                mark += 0;
            }
        }

        fclose(fp);
		  fp = NULL;

        prepare_screen();

        gotoxy(27, 7);
        printf("Personality Test Results");
        gotoxy(27, 8);
        printf("------------------------");

		  if ((mark / QUESTION_COUNT) < NER_LIM)
		  {
				gotoxy((40 - ((strlen(NER_PER) + 28) / 2) - 1), 14);
				printf("Your personality is very %s !", NER_PER);
        }
        else if ((mark / QUESTION_COUNT) < MOD_LIM)
        {
            gotoxy((40 - ((strlen(MOD_PER) + 28) / 2) - 1), 14);
            printf("Your personality is very %s !", MOD_PER);
        }
        else
		  {
				gotoxy((40 - ((strlen(DYN_PER) + 28) / 2) - 1), 14);
				printf("Your personality is very %s !", DYN_PER);
        }
	gotoxy(38, 16);
	printf("Your mark is %i", (mark / QUESTION_COUNT));

        get_prompt();
    }
}




/*----------------------------------------------------------------------------*
 *                                   make_test()                              *
 *----------------------------------------------------------------------------*/

void make_test(void)
{
    /*Creating a new customized test is done here.  I used this same function
      of the programe to create the default test for it.*/
    FILE *fp;
    TESTQ quest;
	 char filen[FILE_LEN];
    int ctr, i, y;

    prepare_screen();

    gotoxy(32, 7);
    printf("Make New Test");
    gotoxy(32, 8);
    printf("-------------");

    gotoxy(24, 13);
    printf("Enter new test ID: ___________");

    gotoxy(43, 13);
    fflush(stdin);
    gets(filen);

    /*Try is we can open the given file fro reading.  This will let us know if
      the new test name is identicle to another test in the system.  If so,
      never open it for writting.*/
    fp = fopen(filen, "r");

    if (fp != NULL)
    {
        fclose(fp);
        fp = NULL;

        prepare_screen();

        gotoxy(35, 7);
        printf("ERROR!!!");
        gotoxy(35, 8);
        printf("--------");

        gotoxy(11, 14);
        printf("The name you gave already relates to a test that exists!");

        get_prompt();
    }
    else
    {
        /*Since this new name given is qualified for using as a test name, we
          are ready to start making the new test.*/
		  fp = NULL;
		  fp = fopen(filen, "w");

		  for (ctr = 0; ctr < QUESTION_COUNT; ctr++)
        {
				prepare_screen();

            gotoxy(4, 6);
				printf("Enter Question %i:", (ctr + 1));

            gotoxy(6, 8);
            printf("> ");

            fflush(stdin);
				gets(quest.question);

				for (i = 0, y = 10; i < ANSWER_COUNT; i++, y += 2)
            {
                gotoxy(9, y);
                printf("Answer %i: ", (i + 1));

                fflush(stdin);
                gets(quest.answers[i]);

                gotoxy(12, ++y);
                printf("Marks for answer %i [1-10]: ", (i + 1));

                fflush(stdin);
					 scanf("%i", &(quest.marks[i]));

					 //error handelling for input marks

					 if (quest.marks[i] > 10)
					 {
						  quest.marks[i] = 10;
					 }
					 else if (quest.marks[i] < 1)
					 {
						  quest.marks[i] = 1;
					 }
				}

				fprintf(fp, "%s/", quest.question);

				for (i = 0; i < ANSWER_COUNT; i++)
				{
					 fprintf(fp, "%s/%i ", quest.answers[i], quest.marks[i]);
				}

				fprintf(fp, "\n");
		  }

		  fclose(fp);
		  fp = NULL;

		  prepare_screen();

		  gotoxy(26, 14);
		  printf("New Test Setup Completed!");

		  get_prompt();
	 }
}




/*----------------------------------------------------------------------------*
 *                                   must_exit()                              *
 *----------------------------------------------------------------------------*/

BOOL must_exit(void)
{
    char opt;

    prepare_screen();

    gotoxy(3, 23);
    printf("Do you wish to exit from the system [y / n]: ");

    opt = (char)getch();

    /*Any answer given other thatn y or Y are considered to be n or N.*/
    switch (opt)
    {
        case 'y':
        case 'Y':    return FALSE;
	default:     return TRUE;
    }
}




/*----------------------------------------------------------------------------*
 *                                 invalid_option()                           *
 *----------------------------------------------------------------------------*/

void invalid_option(void)
{
	prepare_screen();

	gotoxy(32, 7);
	printf("Invalid Option");
	gotoxy(32, 8);
	printf("--------------");

	gotoxy(22, 11);
	printf("The option you enterd is invalid!");

	gotoxy(30, 13);
	printf("Please try again.");

	get_prompt();
}




/*----------------------------------------------------------------------------*
 *                                  exit_screen()                             *
 *----------------------------------------------------------------------------*/

void exit_screen(void)
{
    prepare_screen();

    gotoxy(30, 8);
    printf("Terminating System");
    gotoxy(30, 9);
    printf("------------------");

    gotoxy(18, 13);
    printf("Thank you for using Personality Guru 1.0v");

    get_prompt();
}
