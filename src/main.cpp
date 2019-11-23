#include <iostream>
#include <fstream>
#include <time.h>
#include <math.h>
#include <iomanip>
#include <cstdlib>
#include <unistd.h>
#include "sudoku_functions.hpp"

using namespace std;

int rozmiarkw=3, ilosckw=3;     //obie zmienne sa parametrami, mozna je zmieniac, ale:
int sudoku [9][9];              //obie ilosci komorek sa iloczynem zmiennych: rozmiarkw * ilosckw
int tabwart [10];               //ilosc komorek jest rowna: rozmiarkw * rozmiarkw + 1
long int licznikspr=0, licznikwyw=0, kombinacji=0;
clock_t start,stop;
double czas;

int main()
{
    fstream Fsudoku;
    Fsudoku.open("Sudoku1.txt", ios::in);

    for(int i=0;i<rozmiarkw*ilosckw;i++)
        for(int j=0;j<rozmiarkw*ilosckw;j++)
            Fsudoku>>sudoku[i][j];

    czysc();
    cout << "Wejsciowe sudoku (0 sa pustymi miejscami do wypelnienia): "<<endl;
    wypis();

    if(check())
        cout << "Podane sudoku poprawne, zaczynam rozwiazywac..."<<endl<<endl;
    else
        {
            cout << "Blad w podanym sudoku, sprawdz czy dobre sudoku zostalo podane..."<<endl;
            return 0;        }

    start = clock();
    solver();
    stop = clock();
    cout << "Skonczone !"<<endl;
    cout << "Wejsciowa ukladanka: "<<endl<<endl;
    wypis();

    stop = clock();
    czas = (double)(stop-start) / CLOCKS_PER_SEC;
    cout<<endl<<"Czas rozwiazywania: "<<czas<<" s"<<endl;
    cout << "Liczba wywolan funkcji sprawdzajacej poprawnosc: "<<licznikspr<<endl;
    cout << "Liczba rekurencyjnych wywolan funkcji rozwiazujacej "<<licznikwyw<<endl<<endl;
    cout << "Liczba znalezionych poprawnych kombinacji: "<<kombinacji<<endl<<endl;
    cout << "konkretne kombinacje znajduja sie w pliku 'wyniki.txt'  "<<endl<<endl;

    return 0;
}
