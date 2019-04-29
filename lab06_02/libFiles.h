#ifndef LIBFILES_H
#define LIBFILES_H

#include <fstream>

/*
Funkcja pomocnicza wczytujaca poprawna nazwe pliku
@param fileName nazwa pliku do wczytania
*/
void loadCorrectFileName(char *fileName);

/*
Funkcja tworzaca strumien do wczytywania wlasciwego pliku
@return wczytany plik z dysku
*/
std::fstream createInputFile();

/*
Funkcja tworzaca strumien do zapisu wlasciwego pliku
@return plik do zapisu
*/
std::fstream createOutputFile();

/*
Funkcja zapisujaca przyslane dane w tablicy do pliku wynikowego do kolumny
@param tab tablica danych
@param Tsize rozmiar tablicy
@param startIterator argument domniemany oznaczajacy iterator od poczatku tablicy, ktorego mozna zmienic w wywolaniu funkcji, jesli zajdzie taka potrzeba
@param outFile wynikowy plik do ktorego zapisuja sie dane
*/
void saveDataToFileInColumn(unsigned long long *tab, unsigned long long Tsize, std::fstream &outFile, int startIterator = 0);

#endif // LIBFILES_H

