/*
  Author: Luca Carlon
  Date: 07.01.2002
  Purpose: Evaluate expressions with various mathematical functions.
*/

#include <iostream.h>
#include <math.h>
#include <stdio.h>
#include <string.h>
// Header per la gestione delle funzioni trigonometriche
#include "trigonometric.h"
// Header con le dichiarazioni delle varie costanti necessarie nel programma
#include "constants.h"
// Rimuove gli spazi dall'espressione
#include "spaces.h"

// Declaring the needed prototipes
void         find_first_second_operator(char[], int, double&, double&);
void         sostituisci(int, int, double);
unsigned int calcola_numero_cifre(double numero);
void         sostituisci_parentesi(int, int, double);
int          CheckExpression(char expression[]);
void         aggiorna_posizioni();
// Inserisce le parentesi che comprendono l'intera espressione
void         parentesizza();

// Building the structure
struct parentesys
{
  int pos_open;
  int pos_close;
  int level;
};

parentesys par[100];
// Numero di record presenti nella struttura par
int max_record_number = 0;

char stringa_finale[DIM_STRINGA_FINALE];
char splittedExpression[20][200];

// Espressione intera inserita dall'utente
char expression[300];
char string[200];

void main()
{
  bool riesegui = false;

  do
  {
    // Letting the user insert a string
    cout << "Insert a string down here:\n";

    // Catching the string
    cin.getline(expression, 300);

    // Rimuovo gli spazi
    remove_spaces(expression);

    // Checking expression
    if (!CheckExpression(expression))
    {
      cout << "\nExpression syntax error...";
      getch();
      return;
    }

    parentesizza();

    aggiorna_posizioni();

    int max_level = 0;

    do
    {
      // Finding max level
      max_level = 0;

      for (int i = 0; i <= max_record_number; i++)
      {
        if (par[i].level > max_level) max_level = par[i].level;
      }

      //cout << "\nMax reached level: " << max_level;

      // Itering through the records with the higher level

      // Questa variabile conterrà il numero di expressioni
      // trovate in questo livello.
      int expressionNumber = 0;

      for (int a = 0; a <= max_record_number; a++)
      {

        // Entering here if we are enetering in the max level
        if (par[a].level == max_level)
        {

          // Itering through the number of operators present
          char tmp_expression[300];
          int c = 0;

          // Copying the string
          for (int b = (par[a].pos_open + 1); b < par[a].pos_close; b++)
          {
            tmp_expression[c++] = expression[b];
          }

          tmp_expression[c] = '\0';

          // Showing the string
          cout << "\nExpression: " << tmp_expression;

          // Copio la stringa in tmp_expression in splittedExpression
          for (b = 0; b < DIM_STRINGA_FINALE; b++)
          {
            splittedExpression[expressionNumber][b] = tmp_expression[b];
          }

          // Incremento il numero di espressioni estrette dalle parentesi
          // di livello maggiore nel ciclo corrente
          expressionNumber++;
        }
      }

      /*
      A questo punto splittedExpression[][] avrà tutte le espressioni
      contenute nelle parentesi più interne della prima espressione
      che devo risolvere. Il numero di espressioni estratte è determinato
      da (expressionNumber - 1).
      */

      // Risolvo tutte le espressioni
      // ============================

      // Ciclo su tutte le expressioni
      for (a = 0; a <= expressionNumber; a++)
      {
        // Ciclo su tutti gli elementi dell'array
        // Prima controlla la presenza di radici
        for (int b = 0; splittedExpression[a][b] != '\0';)
        {
          double secondoOperatore, risultato;

          // Se c'è scritta la r e dopo la r c'è un numero allora svolgo la raltrimenti lascio che prima venga svolto il resto
          if (splittedExpression[a][b] == 'r' && ((int)splittedExpression[a][b + 1] < 48 || (int)splittedExpression[a][b + 1] > 57) && splittedExpression[a][b + 1] != '+' && splittedExpression[a][b + 1] != '-')
          {
            riesegui = true;
            break;
          }

          if (splittedExpression[a][b] == 'r' && (((int)splittedExpression[a][b + 1] >= 48 && (int)splittedExpression[a][b + 1] <= 57) || splittedExpression[a][b + 1] == '+' || splittedExpression[a][b + 1] == '-'))
          {
            // Ho trovato una radice
            //find_first_second_operator(splittedExpression[a], b,
            //primoOperatore, secondoOperatore);
            secondoOperatore = find_argument(splittedExpression[a], b);

            risultato = sqrt(secondoOperatore);

            if (risultato < 0) 
            {
              cout << "\nNo number to the power of 2 is negative.\nThe program is not yet able to handle complex number.\n";
              return;
            }

            substitute_result(splittedExpression[a], b, risultato);

            //b = 0;

            cout << '\n' << splittedExpression[a];

            continue;
          }
          b++;
        }

        // Controllo la presenza di funzione trigonometriche nell'espressione
        for (b = 0; splittedExpression[a][b] != '\0';)
        {
          double risultato;

          switch((char)splittedExpression[a][b])
          {  
            // Se c'è scritta una di queste lettere controllo se è una funzione trigonometrica
            case 's':
            case 'c':
            case 't':
            case 'a':
            {
              double argomento = find_argument(splittedExpression[a], b);
              short int tipo_trigonometrica = istrigonometric(b, splittedExpression[a]);

              // So che è una trigonometrica, prima sapevo solamente che era una
              // parola che cominciava per quella lettera.
              if (tipo_trigonometrica)
              {

                switch(tipo_trigonometrica)
                {
                  case 1: {risultato = sin(argomento); break;}
                  case 2: {risultato = cos(argomento); break;}
                  case 3: {risultato = tan(argomento); break;}
                  case 4: {risultato = asin(argomento); break;}
                  case 5: {risultato = acos(argomento); break;}
                  case 6: {risultato = atan(argomento); break;}
                  case 7: {risultato = 1/tan(argomento); break;}
                  case 8: {risultato = 1/cos(argomento); break;}
                  case 9: {risultato = 1/sin(argomento); break;}
                  
                }
              
                substitute_result(splittedExpression[a], b, risultato);

                b = 0;

                //cout << '\n' << splittedExpression[a];

                continue;
              }
              else
              {
                cout << "\nError! Not recognised symbol.";
                getch();
                return;
              }
            }
          }
          b++;
        }

        // e successivamente di potenze
        for (b = 0; splittedExpression[a][b] != '\0';)
        {
          double primoOperatore, secondoOperatore, risultato;

          if (splittedExpression[a][b] == '^')
          {
            // Ho trovato una potenza
            find_first_second_operator(splittedExpression[a], b,
            primoOperatore, secondoOperatore);

            risultato = pow(primoOperatore, secondoOperatore);

            sostituisci(a, b, risultato);

            b = 0;

            cout << '\n' << splittedExpression[a];

            break;
          }
          b++;
        }

        for (b = 0; splittedExpression[a][b] != '\0';)
        {
          double primoOperatore, secondoOperatore, risultato;

          switch((char)splittedExpression[a][b])
          {
            case '*':
            {
              find_first_second_operator(splittedExpression[a], b,
              primoOperatore, secondoOperatore);

              risultato = primoOperatore * secondoOperatore;

              sostituisci(a, b, risultato);

              b = 0;

              cout << '\n' << splittedExpression[a];

              break;
            }
            case '/':
            {
              find_first_second_operator(splittedExpression[a], b,
              primoOperatore, secondoOperatore);
  
              risultato = primoOperatore / secondoOperatore;

              sostituisci(a, b, risultato);

              b = 0;

              cout << '\n' << splittedExpression[a];

              break;
            }
            default: b++;
          }
        }

        for (b = 0; splittedExpression[a][b] != '\0';)
        {        
          /*
          1. Trovo la posizione del simbolo
          2. Trovo i valori che stanno prima e dopo
             NOTA: Se non c'è ne sono allora visualizzo un msg d'errore
          3. Eseguo l'operazione determinata dal simbolo tra le due variabili
             contenenti i due valori.
          4. Sostituisco il risultato al posto dell'operazione.
          5. Continua il ciclo
          */

          double primoOperatore, secondoOperatore, risultato;

          // Se trovo un simbolo presente tra quelli consentiti
          switch((char)splittedExpression[a][b])
          {
            // In caso il simbolo sia + ...
            case '+':
            {
              // Trovo valore prima e dopo
              find_first_second_operator(splittedExpression[a], b /* posizione dell'operatore */,
              primoOperatore, secondoOperatore /*Passo l'indirizzo della variabile*/);

              // Eseguo l'operazione
              risultato = primoOperatore + secondoOperatore;

              // Sostituisco il risultato al posto dell'operazione
              sostituisci(a /* indice */, b /* posizione dell'operatore*/, risultato);

              // Azzero b per ricominciare da capo l'itering della stringa
              b = 0;

              // Showing the result
              cout << '\n' << splittedExpression[a];

              // breaking della case
              break;
            }
            case '-':
            {
              // Devo controllare che il segno sia inteso come operando
              if (b == 0) {b++; break;}

              // Controllo che prima ci sia un numero
              if (splittedExpression[a][b - 1] < 48 || splittedExpression[a][b - 1] > 57) {b++; break;} 

              find_first_second_operator(splittedExpression[a], b,
              primoOperatore, secondoOperatore);

              risultato = primoOperatore - secondoOperatore;

              sostituisci(a, b, risultato);

              b = 0;

              cout << '\n' << splittedExpression[a];

              break;
            }
            default: b++;
          }
        }
        if (riesegui == true) {a = -1; riesegui = false;}
      }

      // Dovrei aver ottenuto un numero di valori senza operatori pari a (expressionNumber - 1)

      // Visualizzo i risultati di tutte le parentesi (quelle con il lvello più alto
      /*for (int a = 0; a < expressionNumber; a++)
      {
        cout << splittedExpression[expressionNumber];
      }*/

      // Risolvo tutte le espressioni
      // Riciclo sull'espressione iniziale (expression[])
      // Quando incontro una parentesi di livello massimo
      // sostituisco il contenuto con il suo risultato.
      /*
        NOTA: Se c'è un simbolo prima della parentesi allora lo
        lascio, altrimenti metto il *
      */

      /*
        Vado a sostituire i valori risolti delle parentesi più interne all'interno
        dell'espressione intera e ricomincia il ciclo.
        max_record_number = numero di parentesi;
        max_level = livello massimo;
        splittedExpression[] = espressioni da sostituire;
        expressionNumber = numero di espressioni da sostituire;
        expression[] = espressione intera da risolvere;3.30
      */

      int numero_parentesi = max_record_number;

      int b = 0;

      for (a = 0; a <= numero_parentesi; a++)
      {
        if (par[a].level == max_level)
        {
          double numero = atof(splittedExpression[b++]);
          sostituisci_parentesi(par[a].pos_open, par[a].pos_close, numero);
          a = 0;
        }
      }
    } 
    while(max_level > 1);

    cout << "\n\n";
  }
  while(1);

  cout << '\n';

  return;
}

void aggiorna_posizioni()
{
  // Declaring variable for the position of each symbol in the expression
  int sym_pos[100];
  int sym_num = 0;

  // Declaring the variable for the position of each parentesys
  int par_pos[100];
  int par_num = 0;

  max_record_number = 0;

  // Starting iterating, stops when the finish character is met
  for (int i = 0; (char)expression[i] != '\0'; i++)
  {
    // If the symbol is a parentesys, the inserting its position in the array
    if (expression[i] == '(' || expression[i] == ')') par_pos[par_num++] = i;

    // Checking if a symbol has been entered
    for (int a = 0; a < allowed_symb_number; a++)
    {
      if (expression[i] == allowed_sym[a]) sym_pos[sym_num++] = i;
    }
  }

  // Showing the result
  //for (i = 0; i <= (par_num - 1); i++) cout << "\nParentesys found in column number: " << par_pos[i];

  //for (i = 0; i <= (sym_num - 1); i++) cout << "\nSymbol found in column number: " << sym_pos[i];

  // Finding the most internal level of parentesys
  int tmp_level = 0;
  int record = 0;

  // Azzero tutta la struttura
  for (int a = 0; a < 100; a++)
  {
    par[a].pos_open = 0;
    par[a].pos_close = 0;
    par[a].level = 0;
  }

  for (i = 0; i < par_num; i++)
  {
    if (expression[par_pos[i]] == '(')
    {
      tmp_level++;
      par[max_record_number].pos_open = par_pos[i];
      par[max_record_number].level = tmp_level;
      max_record_number++;
    }
    else
    {
      tmp_level--;

      // Checking for last not closed parentesys
      for (int a = max_record_number - 1; a >= 0; a--)
      {
        if (par[a].pos_close == 0)
        {
          par[a].pos_close = par_pos[i];
          break;
        }
      }
    }
  }

  // Showing the result
  /*for (i = 0; i < max_record_number; i++)
  {
    cout << "\n" << par[i].pos_open << " " << par[i].pos_close << " " << par[i].level;
  }*/
}

void sostituisci_parentesi(int posizione_apertura, int posizione_chiusura, double numero)
{
  // Nella posizione della prima parentesi inserisco il numero
  /*
    Costruisco un ciclo che anticipi i caratteri successivi di un numero pari a:
    (pos_close - pos_open) - calcola_numero_cifre(numero)
  */
  int lunghezza_stringa = strlen(expression);

  char tmpString[DIM_STRINGA_FINALE];

  // Copio tutto fino a posizione apertura - 1
  for (int a = 0; a < posizione_apertura; a++)
  {
    tmpString[a] = expression[a];
  }

  sprintf(tmpString + posizione_apertura, "%.12f", numero);

  int contatore;
  int indice = posizione_apertura + calcola_numero_cifre(numero);

  for (contatore = posizione_chiusura + 1; contatore <= lunghezza_stringa; contatore++)
  {
    tmpString[indice++] = expression[contatore];
  }

  tmpString[indice] = '\0';

  // Copio tutta la stringa temporanea all'interno della mia espressione
  for (a = 0; 1; a++)
  {
    expression[a] = tmpString[a];

    // Se tmpString finisce faccio finire anche expression
    if (tmpString[a] == '\0') {expression[a] = '\0'; break;}
  }

  cout << '\n' << expression;

  aggiorna_posizioni();
}

int CheckExpression(char expression[])
{
  int tmp_variable = 0;

  for (int i = 0; (char)expression[i] != '\0'; i++)
  {
    if (expression[i] == '(') tmp_variable++;
    else if (expression[i] == ')') tmp_variable--;
  }

  return !tmp_variable;
}

void find_first_second_operator(char string[], int position, double &primoOperando, double &secondoOperando)
{
  /*
  1. Ciclo all'indietro fino a che non trovo un simbolo che non è un numero
     NOTA: ascii non compreso tra 0(48) 9(57)
  2. Trovo la differenza tra gli indici e vedo quanto lungo è il numero
  3. Inserisco i caratteri in una variabile.
  4. Ripeto la medesima cosa per quello che sta davanti.
  5. uso atoi per assegnare il giusto valore a primoOperatore ed a secondoOperatore.
  */

  int inizio_operazione, fine_operazione;

  char primo_operando[20], secondo_operando[20];

  int a;

  for (a = (position - 1); a >= 0; a--)
  {
    // Se il simbolo non è compreso tra 48 e 57 allora significa che non è un
    // numero. Tengo da parte l'indice di inizio.
    if (((int) string[a] < 48 || (int) string[a] > 57) && (int) string[a] != 46)
    {
      inizio_operazione = a;
      break;
    }
    else if (a == 0) inizio_operazione = 0;
  }

  for (a = (position + 1); string[a] != '\0'; a++)
  {
    // Se il simbolo non è compreso tra 48 e 57 allora significa che non è un
    // numero. Tengo da parte l'indice di fine.
    if (((int) string[a] < 48 || (int) string[a] > 57) && (int) string[a] != 46 && /*(char) string[a] != '-' && */a != (position + 1))
    {
      fine_operazione = a;
      break;
    }
  }

  if (string[a] == '\0') fine_operazione = a;

  int indice = 0;

  for (a = inizio_operazione; a < position; a++)
  {
    // Inserisco ogni elemento all'interno della variabile primo_operatore
    // per poter poi utilizzare la funzione atoi.
    primo_operando[indice++] = string[a];
  }


  indice = 0;

  for (a = (position + 1); a <= fine_operazione; a++)
  {
    // Inserisco tutti gli elementi compresi tra position + 1 e fine_operazione
    // in un'altra variabile temporanea.
    secondo_operando[indice++] = string[a];
  }

  // Modifico i valori per indirizzo convertendo anche le stringhe in integer
  primoOperando = atof(primo_operando);
  
  secondoOperando = atof(secondo_operando);
}

void sostituisci(int indice, int position, double risultato)
{
  /*
  1. Ciclo all'indietro e trovo la posizione del primo numero del primo valore.
  2. Ciclo in avanti e trovo l'ultimo numero del secondo valore.
  3. Ciclo ed inserisco in un nuovo array uno per uno gli elementi di string
     fino ad arrivare al limite.
  4. Qui inserisco risultato.
  5. Poi continuo partendo dal secondo limite.
  */

  // Copio l'espressione in una nuova stringa
  for (int i = 0; i < DIM_STRINGA_FINALE; i++)
  {
    string[i] = splittedExpression[indice][i];
  }

  int starting_position = position - 1;

  if (risultato < 0)
  {
    while ((string[starting_position] >= 48 && string[starting_position] <= 57) || string[starting_position] == 46 || ((char) string[starting_position] == '-' && starting_position == 0))
    {
      starting_position--;
    }
    if (starting_position != -1) starting_position--;
  }
  else
  {
    while ((string[starting_position] >= 48 && string[starting_position] <= 57) || string[starting_position] == 46 || ((char) string[starting_position] == '-' && starting_position == 0))
    {
      starting_position--;
    }
  }

  // starting_position contiene l'ultimo elemento da considerare non parte
  // dell'operazione da cancellare

  int final_position = position + 1;

  while ((string[final_position] >= 48 && string[final_position] <= 57) || string[final_position] == 46 || ((char) string[final_position] == '-' && final_position == (position + 1)))
  {
    final_position++;
  }

  // final_position contiene il primo elemento da riconsiderare.
  // final_position - 1 sarà quindi l'ultimo elemento da cancellare.

  // Ricostruisco la stringa finale di testo
  // 1 + 1
  // starting_position + 1 = 1
  // final_position - 1 = 1

  for (int a = 0; a <= starting_position; a++)
  {
    splittedExpression[indice][a] = string[a];
  }

  //if (risultato < 0 && starting_position != -1) sprintf(splittedExpression[indice] + starting_position, "%.12f", risultato);

  /*else */sprintf(splittedExpression[indice] + starting_position + 1, "%.12f", risultato);

  // Calcolo il numero di cifre che compone la variabile risultato
  int b = starting_position + 1 + calcola_numero_cifre(risultato);

  for (a = (final_position); string[a] != '\0'; a++, b++)
  {
    splittedExpression[indice][b] = string[a];
  }

  splittedExpression[indice][b] = '\0';

  return;
}

void parentesizza()
{
  //if (expression[0] != '(')
  //{
    char *tmp_espressione = new char[300];
    //char tmp_espressione[300];

    tmp_espressione[0] = '(';

    int contatore;

    for (contatore = 0; contatore < 299; contatore++)
    {
      tmp_espressione[contatore + 1] = expression[contatore];
    }

    for (contatore = 0; contatore < 300; contatore++)
    {
      expression[contatore] = tmp_espressione[contatore];
    }

    for (contatore = 0; contatore < 299; contatore++)
    {
      if (expression[contatore] == '\0')
      {
        expression[contatore] = ')';
        expression[contatore + 1] = '\0';
        break;
      }
    }

    delete[] tmp_espressione;

  return;
}
