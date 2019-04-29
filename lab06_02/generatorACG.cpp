#include "generatorACG.h"
#include "generatorLCG.h"
#include "libFiles.h"
#include <iostream>
using namespace std;

void findBestPair(int n, int m, int & j, int & k)
{
	int maxIndexK{}, maxIndexJ{};

	//wyszukanie max indeksu k
	for (int i = 0; i < 90; i++)
	{
		if (i != 89) {
			if (tabK[i] < n && tabK[i + 1] >= n)
			{
				maxIndexK = i;
				break;
			}
		}
		else
			maxIndexK = i;
	}

	//szukanie od najwiekszego indeksu k w dol i sprawdzanie czy dla m zgadza sie warunek
	for (int i = maxIndexK; i >= 0; i--)
	{
		if (tabJ[i] < m)
		{
			maxIndexJ = i;
			maxIndexK = i;
			break;
		}
	}

	j = tabJ[maxIndexJ];
	k = tabK[maxIndexK];
}

void showACGMenu()
{
	unsigned long long x0{}, xMax{}, amountOfElem{}, range{}, multiplier{};

	cout << "Podaj zakres xmax: ";
	xMax = loadNonNegativeNumber();											//zaladowanie xMax, czyli do jakiej liczby chcemy losowac; gorna granica

	cout << "Ile liczb chcesz wygenerowac: ";
	amountOfElem = loadNonNegativeNumber();									//zaladowanie amountOfElem, czyli ilosci elementow, ile chcemy wygenerowac

	range = xMax + 1;														//range = m - modul, zakres potrzebny do obliczen
	x0 = 0;																	//wstepna inicjalizacja ziarna (seed) jako 0
	multiplier = computeMultiplierA(range);									//obliczenie optymalnego mnoznika a

	unsigned long long *tabX = new unsigned long long[amountOfElem];		//tablica losowych wartosci obliczonych za pomoca generatora LCG
	unsigned long long *tabY = new unsigned long long[amountOfElem + 1];	//tablica wartosci z tabX w odwrotnej kolejnosci
	unsigned long long *resTab = new unsigned long long[amountOfElem];		//tablica wynikowych wartosci

	//pierwsze obliczenie losowych wartosci
	fillTableWithLCGRandNumb(tabX, amountOfElem, range, multiplier, x0);
	reverseLCGTableToACGTable(tabX, tabY, amountOfElem);
	fillTableACGRandNumb(resTab, tabY, xMax, amountOfElem);

	int choise = 4;

	while (choise != 0)
	{
		cout << "1. Pokazanie wygenerowanych liczb na ekranie\n"
			"2. Zmiana ziarna x0\n"
			"3. Zapis liczb do pliku\n"
			"0. Koniec pracy\n"
			"Wybor ";
		cin >> choise;

		switch (choise)
		{
		case 1: {
			showTable(resTab, amountOfElem);
		}
				break;
		case 2: {
			cout << "Podaj ziarno x0 z przedzialu 0 do xMax: ";
			x0 = loadNumberFromRanges(0, xMax);

			//kazde nastepne obliczenie losowych wartosci jesli zaszla zmiana ziarna
			fillTableWithLCGRandNumb(tabX, amountOfElem, range, multiplier, x0);
			reverseLCGTableToACGTable(tabX, tabY, amountOfElem);
			fillTableACGRandNumb(resTab, tabY, xMax, amountOfElem);
		}
				break;
		case 3: {

			fstream outFile = createOutputFile();
			saveDataToFileInColumn(tabY, amountOfElem + 1, outFile, 1);
			outFile.close();
		}
		default:
			break;
		}
	}

	delete[] tabX;
	delete[] tabY;
	delete[] resTab;
}

unsigned long long generateACGRandNumb(unsigned long long *tabY, unsigned long long xMax, unsigned long long amountOfElem, int &j, int &k)
{
	unsigned long long result{};

	result = (tabY[j] + tabY[k]) % xMax;

	if (k == amountOfElem)
		tabY[1] = result;
	else
		tabY[k + 1] = result;

	k--;
	j--;

	if (k == 0)
		k = amountOfElem;
	else if (j == 0)
		j = amountOfElem;


	return result;
}

void reverseLCGTableToACGTable(unsigned long long * tabX, unsigned long long * tabY, unsigned long long amountOfElem)
{
	for (int i = 1; i < amountOfElem + 1; i++)
	{
		tabY[i] = tabX[amountOfElem - i];
	}
}

void fillTableACGRandNumb(unsigned long long * resTab, unsigned long long * tabY, unsigned long long xMax, unsigned long long amountOfElem)
{
	int j{}, k{};
	findBestPair(amountOfElem, xMax, j, k);									//zaladowanie najlepszej pary liczb do algorytmu

	for (int i = 0; i < amountOfElem; i++)
	{
		resTab[i] = generateACGRandNumb(tabY, xMax, amountOfElem, j, k);
	}
}
