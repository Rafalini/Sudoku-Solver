#include "sudoku_functions.hpp"
#include <iostream>
#include <fstream>

using namespace std;

extern int rozmiarkw, ilosckw;     //obie zmienne sa parametrami, mozna je zmieniac, ale:
extern int sudoku [9][9];              //obie ilosci komorek sa iloczynem zmiennych: rozmiarkw * ilosckw
extern int tabwart [10];               //ilosc komorek jest rowna: rozmiarkw * rozmiarkw + 1

extern long int licznikspr, licznikwyw, kombinacji;

void czysc() //czysci tablice wartosci 'zajetych'
{
    for(int i=0;i<=rozmiarkw*rozmiarkw;i++)
        tabwart[i]=0;
}

bool tab_check ()  //sprawdza tablice wartosci, jesli sa powtorzenia wartosci beda >1
{
    for(int i=1;i<=rozmiarkw*rozmiarkw;i++)
        if(tabwart[i]>1)
            return false;
    return true;
}

void wypis () //wyspiuje cale sudoku z podzialem na "kwadraty"
{
    //fstream wyniki;
    //wyniki.open("wyniki.txt",ios::out | ios::app);

    for(int i=0, y=0;i<ilosckw;i++)
    {
        for(int j=0;j<rozmiarkw;j++,y++)
        {
            for(int k=0, x=0 ;k<ilosckw;k++)
            {
                for(int l=0;l<rozmiarkw; l++, x++)
                {
                    cout <<sudoku[y][x]<<" ";
                    //wyniki<<sudoku[y][x]<<" ";
                }
                cout << "  ";
                //wyniki<<"  ";
            }
            cout << endl;
           // wyniki<<endl;
        }
        cout << endl;
        //wyniki<<endl;
    }
    cout << endl<<endl;
    //wyniki<<endl<<endl;
    //wyniki.close();
}

void plikwypis () //wyspiuje cale sudoku z podzialem na "kwadraty"
{
    kombinacji++;

    fstream wyniki;
    wyniki.open("wyniki.txt",ios::out | ios::app);

    for(int i=0, y=0;i<ilosckw;i++)
    {
        for(int j=0;j<rozmiarkw;j++,y++)
        {
            for(int k=0, x=0 ;k<ilosckw;k++)
            {
                for(int l=0;l<rozmiarkw; l++, x++)
                {
                    //cout <<sudoku[y][x]<<" ";
                    wyniki<<sudoku[y][x]<<" ";
                }
                //cout << "  ";
                wyniki<<"  ";
            }
            //cout << endl;
            wyniki<<endl;
        }
       // cout << endl;
        wyniki<<endl;
    }
    //cout << endl<<endl;
    wyniki<<endl<<endl;

    wyniki.close();
}

void ekran()
{
    if(licznikwyw%8000==0)
    {
        cout <<"Progress..."<<endl;
        cout << "Liczba wywolan funkcji sprawdzajacej poprawnosc: "<<licznikspr<<endl;
        cout << "Liczba rekurencyjnych wywolan funkcji rozwiazujacej: "<<licznikwyw<<endl<<endl;
        cout << "Liczba znalezionych poprawnych kombinacji: "<<kombinacji<<endl<<endl;
        wypis();
    }
}

bool check () //sprawdza poprawnosc ukladanki w danym momencie, nie liczy zer
{
      licznikspr++;
      czysc();
      int a=0;
      for (int y = 0; y < rozmiarkw*ilosckw; ++y) //sprawdza wiersze robiac indeks wartosci (tabwart)
        {
            for (int x = 0; x < rozmiarkw*ilosckw; ++x)
                {
                    if(sudoku[y][x]!=0)
                    {
                        a=sudoku[y][x];
                        tabwart[a]++;
                    }
                }
            if(!tab_check())
                return false;
            czysc();
        }

      czysc();
      for (int y = 0; y < rozmiarkw*ilosckw; ++y) //sprawdza kolumny robiac indeks wartosci (tabwart)
        {
            for (int x = 0; x < rozmiarkw*ilosckw; ++x)
                {
                    a=sudoku[x][y];
                    tabwart[a]++;
                }
            if(!tab_check())
                    return false;
            czysc();
        }
      czysc();
      for(int i=0;i<ilosckw;i++)    //sprawdza sektory robiac indeks wartosci (tabwart)
      {
          for(int j=0;j<ilosckw;j++)
          {
              for(int y=0+i*rozmiarkw;y<(i+1)*rozmiarkw;y++)
              {
                  for(int x=0+j*rozmiarkw;x<(j+1)*rozmiarkw;x++)
                  {
                    a=sudoku[y][x];
                    tabwart[a]++;
                  }
              }
              if(!tab_check())
                    return false;
              czysc();
          }
      }
    return true;
}

bool solver () //poszukuje pierwsze 0 (dziure) w sudoku i wypelnia ja liczba k, sprawdza poprawnosc, nastepnie wywoluje sie ponownie lub cofa si�
{
    ekran();
    licznikwyw++;
    for(int y = 0; y < rozmiarkw*ilosckw; y++)
        {
            for(int x = 0; x < rozmiarkw*ilosckw; x++)
                {
                    if(sudoku[y][x]==0)
                    {
                        for(int k=1;k<=rozmiarkw*rozmiarkw;k++)
                        {
                            sudoku[y][x]=k;
//wypis();
//usleep(40000);
                            if(y==rozmiarkw*ilosckw-1 && x==rozmiarkw*ilosckw-1 && check())
                                {
                                    k++;
                                    sudoku[y][x]++;
                                    plikwypis();
                                    wypis();
                                }
                            if(check())
                                if(solver())
                                    return true;
                        }
                        sudoku[y][x]=0;
                        return false;
                    }
                    if(y==rozmiarkw*ilosckw-1 && x==rozmiarkw*ilosckw-1)
                           {
                               if(check())
                                    {
                                        plikwypis();
                                        //wypis();
                                    }
                               return false;
                           }
                }
        }
    return true;
}
