#ifndef GENERATORLCG_H
#define GENERATORLCG_H

#include <vector>

constexpr unsigned int increment = 1;				//inicjowanie przyrostu c=1, poniewaz 1 zawsze bedzie wzglednie pierwsza z modulem m!

/*
Funkcja sprawdzajaca czy liczba jest liczba pierwsza
@param number przysylana liczba do sprawdzenia
@return true jesli jest liczba pierwsza, false w przeciwnym wypadku
*/
bool isPrimeNumber(unsigned long long number);

/*
Funkcja sprawdzajaca czy primeNum jest wielokrotnoscia przesylanej liczby b
@param b przesylana liczba do sprawdzenia
@param primeNum liczba pierwsza; czynnik przyrostu m
@return true jesli jest wielokrotnoscia, false w przeciwnym wypadku
*/
bool isMultiple(unsigned long long primeNum, unsigned long long b);

/*
Funkcja dzielaca przysylana liczbe na liczby pierwsze i wpisujaca je do wektora
@param vec przysylany vector do zapisu czynnikow pierwszych liczbyy
@param number przysylana liczba do znalezienia czynnikow pierwszych
*/
void divideToPrimeNumbers(std::vector <unsigned long long> &vec, unsigned long long number);

/*
Funkcja obliczajaca mnoznik a zgodnie z wytycznymi dla najlepszego a
@param increment modul m potrzebny do obliczen
@return najbardziej odpowiedni mnoznik a do losowania liczb
*/
unsigned long long computeMultiplierA(unsigned long long range);

/*
Funkcja generujaca liczbe losowa z danego przedzialu (range - 1)
@param x0 ziarno (seed) liczba poczatkowa z zakresu
@param multiplier mnoznik a juz wczesniej obliczony
@param range modul m  - zakres liczb losowanych
@return liczba pseudolosowa z podanego zakresu
*/
unsigned long long generateRandNumb(unsigned long long x0, unsigned long long multiplier, unsigned long long range);

/*
Funkcja obslugujaca menu generatora LCG
*/
void showLCGMenu();

/*
Funkcja wczytujaca liczbe nieujemna
@return liczba nieujemna
*/
unsigned long long loadNonNegativeNumber();

/*
Funkcja wczytujaca liczbe z zakresu low do high
@return liczba z zakresu low do high
*/
unsigned long long loadNumberFromRanges(unsigned long long low, unsigned long long high);

/*
Funkcja wypelniajaca tablice za pomoca randomowych wartosci poprzez genrator LCG
@param tab przysylana tablica do wpisywania wartosci
@param amountOfElem liczba elementow n, rowniez dlugosc tablicy
@param range zakres, modul m
@param multiplier mnoznik a
@param x0 argument domniemany jesli go nie ma zaczynamy od ziarna 0
*/
void fillTableWithLCGRandNumb(unsigned long long *tab, unsigned long long amountOfElem, unsigned long long range, unsigned long long multiplier, unsigned long long x0 = 0);

/*
Funkcja pokazujaca zawartosc tablicy
@param Tsize rozmiar tablicy
@param startIterator poczatkowy iterator, inaczej mowiac od jakiego indeksu p0kazywac na ekranie tablice
*/
void showTable(unsigned long long *tab, unsigned long long Tsize, unsigned long long startIterator = 0);

#endif // !GENERATORLCG_H

