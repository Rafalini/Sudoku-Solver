#ifndef SUDOKU_FUN
#define SUDOKU_FUN

void czysc(); //czysci tablice wartosci 'zajetych' -uzywane do sprawdzana poprawnosci
              //pionowo, poziomo i w kwadratach

bool tab_check ();  //sprawdza tablice wartosci, jesli sa powtorzenia wartosci beda >1

void wypis (); //wyspiuje cale sudoku z podzialem na "kwadraty"

void plikwypis (); //wyspiuje cale sudoku z podzialem na "kwadraty"

void ekran ();

bool check (); //sprawdza poprawnosc ukladanki w danym momencie, nie liczy zer

bool solver (); //poszukuje pierwsze 0 (dzire) w sudoku i wypelnia ja liczba k, sprawdza poprawnosc, nastepnie wywoluje sie ponownie lub cofa si�

#endif
