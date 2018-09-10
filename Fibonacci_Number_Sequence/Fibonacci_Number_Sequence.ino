/* Dette er et program som skriver Fibonaccis tallrekke
   (https://en.wikipedia.org/wiki/Fibonacci_number)
   i den serielle overvåkeren til Arduino Uno.
   Laget av: Børre A. Opedal Lunde, 3ELDATA.
   Sist oppdatert: 10.09.2018
*/

/* 
   Grenseverdien for når tallrekken skal slutte.
   Den er en konstant siden den aldri skal forandre
   verdi mens programmet kjører.
*/
const int limit = 46;

/*
   Tabellen fibonacciSequence inneholder
   alle Fibonaccitallene fra 1 til grensen.
*/
unsigned long fibonacciSequence[limit];

/*
   Separator er tegnet som adskiller
   tusendeler i tallene. Dette er
   for gjøre det lettere å lese
   høye tall, f.eks. 5,673,201.
*/
const char separator = ',';

/*
   Funksjonen formatterer et tall
   slik at det blir lettere å lese.
*/
String formatNumber(String number) {
  String result;                                    // resultatet som skal bygges i løpet av funksjonen.
  int numberLength = number.length() + 1;           // lengden på tallet.
  char numberArray[numberLength];                   // en tabell som skal inneholde sifrene i tallet.
  number.toCharArray(numberArray, numberLength);    // tabellen blir fylt med sifrene fra tallet.

  for (int i = 0; i < numberLength; i++) {
    /* Separatortegnet teller siffer fra høyre til venstre.
       Ettersom tallet blir bygget fra venstre til høyre er
       det nødvendig å gjøre om prosessen for separatortegnet.
       Derfor er heltallet j som brukes som indeksposisjonen
       til separatoren omvendt av i, som er indeksposisjonen
       for sifrene i tallet.
    */
    int j = numberLength - (i + 1);
    /*
        Regneoperasjonen modulo (markeres som %) blir benyttet 
        for å vite om resten er lik null. På den måten kan man
        separere tre sifre om gangen.
    */
    if (j % 3 == 0 && j != numberLength - 1 && j != 0) {
      result = result + separator;      // Separator blir lagt til i tallet.
    }
    result = result + numberArray[i];   // Resulatet bygges et siffer om gangen.
  }

  /*
     Det ferdige resultet returneres.
     Det består av tallet delt opp med
     separatortegn hvor det er nødvendig.
  */
  return result;
}

/*
   Funksjonen utfører utregningene som lager
   Fibonaccitallene og populerer tabellen som
   skal inneholde dem. På denne måten kan man
   raskt hente fram Fibonaccitall fra tabellen
   uten å måtte regne dem ut på nytt.
*/
void createFibonacciSequence() {
  unsigned long previousNumber = 0;
  unsigned long previousResult = 1;
  unsigned long result = 0;
  Serial.println("Creating Fibonacci Sequence...");
  for (int i = 0; i <= limit; i++) {
    previousNumber = previousResult;
    previousResult = result;
    result = previousNumber + previousResult;
    fibonacciSequence[i] = result;
  }
}

/*
   Henter et Fibonaccitall fra Fibonaccitalltabellen.
*/
unsigned long fib(int n) {
  return fibonacciSequence[n];
}

/*
   Printer Fibonaccitallsekvensen i den serielle overvåkeren.
*/
void printFibonacciSequence() {
  Serial.println("Fibonacci sequence:");
  for (int i = 0; i <= limit; i++) {
    Serial.println("F" + (String) i + "\t" + formatNumber((String) fib(i)));
  }
}

/*
   Starter den serielle overvåkeren og åpner den på datahastighet på 9600
   bits per sekund. Den brukes for å kommunisere med brukeren, i dette
   programmet er det hele poenget.
   Fibonaccitabellen lages og printes på den serielle overvåkeren.
*/
void setup() {
  Serial.begin(9600);
  createFibonacciSequence();
  printFibonacciSequence();
}

/*  loop benyttes ikke i dette programmet,
    men må likevel være med for at
    programmet skal kunne lastes opp.
*/
void loop() {}
