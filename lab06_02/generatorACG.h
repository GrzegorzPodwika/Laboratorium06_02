#ifndef GENERATORACG_H
#define GENERATORACG_H

//tablica najlepszych wartosci k
constexpr int tabJ[90] = {1, 1, 1, 2, 1, 1, 3, 4, 3, 2, 1, 4, 7, 3, 5 ,6, 7, 3, 2, 1,
						  5, 9, 3, 7, 3, 9, 13, 2, 3, 6, 7, 12, 13, 2, 11, 4, 8, 14, 3, 20,
						  5, 14, 20, 21, 9, 12, 15, 22, 3, 19, 21, 24, 7, 22, 19, 1, 11, 1, 5, 31,
						  18, 32, 9, 33, 6, 9, 18, 20, 35, 25, 28, 31, 9, 19, 4, 16, 35, 13, 13, 38,
						  2, 21, 11, 17, 6, 12, 33, 34, 11, 27
						 };

//tablica najlepszych wartosci j
constexpr int tabK[90] = {2, 3, 4, 5, 6, 7, 7, 9, 10, 11, 15, 15, 15, 17, 17, 17, 18, 20, 21, 22,
						  23, 23, 25, 25, 28, 28, 28, 29, 31, 31, 31, 31, 33, 35, 36, 39, 39, 39, 41, 41,
						  47, 47, 47, 47, 49, 49, 49, 49, 52, 52, 52, 55, 57, 57, 58, 60, 60, 63, 63, 63,
						  65, 65, 68, 68, 71, 71, 71, 71, 71, 73, 73, 73, 79, 79, 81, 81, 81, 84, 87, 89,
						  93, 94, 95, 95, 97, 97, 97, 97, 98, 98};

/*
Funkcja znajdujaca najlepsza pare zalezna od n i m
@param n ilosc elementow do wygenerowania
@param m zakres - modul losowanej liczby
@param j referencja do pierwszego obliczonego wspolczynnika
@param k referencja do drugiego obliczonego wspolczynnika
*/
void findBestPair(int n, int m, int &j, int &k);

/*
Funkcja obslugujaca menu generatora LCG i zarzadzajaca funkcjami pobocznymi
*/
void showACGMenu();

/*
Funkcja generujaca losowa liczbe z tablicy tabY za pomoca wspolczynnikow j i k
@param tabY odwrocona tablica z losowymi wartosciami wylosowanymi przez generator LCG
@param xMax zakres losowania liczby
@param amountOfElem liczba elementow
@param j pierwszy wspolczynnik do algorytmu
@param k drugi wspolczynnik do algorytmu
*/
unsigned long long generateACGRandNumb(unsigned long long *tabY, unsigned long long xMax, unsigned long long amountOfElem,int &j, int &k);

/*
Funkcja pomocnicza odwracajaca tablice
@param tabX tablica z wygenerowanymi liczbami pseudolosowymi przez generator LCG
@param tabY tablica do wpisywania wartosci tabX w odrotnej kolejnosci
@param amountOfElem liczba elementow w tym wypadku rownoznaczne z rozmiarem tablicy
*/
void reverseLCGTableToACGTable(unsigned long long *tabX, unsigned long long *tabY, unsigned long long amountOfElem);

/*
Funkcja wypelniajaca wynikowa tablice obliczonymi algorytmem wartosciami pseudolosowymi z tablicy Y
@param resTab wynikowa tablica
@param tabY tablica z poczatkowymi randomowymi liczbami
@param xMax zakres losowania
@param amountOfElem liczba elementow do wpisania, tu takze jako rozmiar tablicy resTab
*/
void fillTableACGRandNumb(unsigned long long *resTab, unsigned long long *tabY, unsigned long long xMax, unsigned long long amountOfElem);

#endif // !GENERATORACG_H

