#include "generatorLCG.h"
#include "libFiles.h"
#include <iostream>
#include <vector>
#include <cmath>
#include <fstream>
#include <Windows.h>
using namespace std;

bool isPrimeNumber(unsigned long long number)
{
	//jesli liczba jest mniejsza od 2 napewno nie jest liczba pierwsza
	if (number < 2)
		return false;

	//sprawdzenie czy liczba n ma jakiekolwiek dzielniki z przedzialu [2,...,sqrt(n)], jesli nie => jest to liczba pierwsza
	for (unsigned int i = 2; i*i <= number; i++) {
		if (number%i == 0)
			return false;
	}


	return true;
}

bool isMultiple(unsigned long long primeNum, unsigned long long b)
{
	unsigned long long tmp = primeNum;

	//dopoki primeNum jest mniejszy lub rowny liczbie b, mnozymy tmp razy kolejne liczby naturalne i sprawdzamy czy jest wielokrotnoscia
	for (int i = 1; tmp <= b; i++)
	{
		tmp *= i;

		if (b == tmp)
			return true;
	}

	return false;
}

void divideToPrimeNumbers(vector<unsigned long long> &vec, unsigned long long number)
{
	int k = 2;
	if (isPrimeNumber(number))				//jesli przyslana liczba jest liczba pierwsza to wpisujemy ja do vectora i konczymy
	{
		vec.push_back(number);
	}
	else
	{
		while (number > 1)					//dopoki liczba jest wieksza od 1
		{
			while (number % k == 0)			//dopoki liczba % k = 0, wpisujemy do wektora i dzielimy przez k, i ponawiamy sprawdzenie warunku
			{
				vec.push_back(k);
				number /= k;
			}
			++k;
		}
	}
}

unsigned long long computeMultiplierA(unsigned long long range)
{
	vector <unsigned long long> lambdas;							//vector lambd
	vector <unsigned long long> preMultipliers;						//vector wstepnych wartosci mnoznikow a

	unsigned long long multiplier = 2, tmp = 1;

	//szukanie lambd dla ktorych spelniony jest warunek (a^lambda) % m = 1
	for (unsigned long long i = multiplier; i < range; i++)
	{
		while (tmp < range)
		{
			unsigned long long res = pow(i, tmp);
			if (res % range == 1) {
				preMultipliers.push_back(i);
				lambdas.push_back(tmp);
				break;
			}
			tmp++;
		}
		tmp = 1;
	}

	//szukanie najwiekszej lambdy posrod obliczonych
	unsigned long long maxLambda{};
	if (lambdas.size())
		maxLambda = lambdas[0];

	for (unsigned int i = 0; i < lambdas.size(); i++)
	{
		if (maxLambda < lambdas[i])
			maxLambda = lambdas[i];
	}


	vector <unsigned long long> resMultipliers;						

	//wpisywanie  do vectora mnoznikow takich a, dla ktorych lambda jest najwieksza
	for (unsigned int i = 0; i < lambdas.size(); i++)
	{
		if (lambdas[i] == maxLambda)
			resMultipliers.push_back(preMultipliers[i]);
	}

	unsigned long long maxA{};

	//obliczenie maxA 
	if (resMultipliers.size())
		maxA = resMultipliers[0];

	for (unsigned int i = 1; i < resMultipliers.size(); i++)
	{
		if (maxA < resMultipliers[i])
			maxA = resMultipliers[i];
	}

	vector <unsigned long long> rangeFactors;						//vector dzielnikow liczby m - modulu
	divideToPrimeNumbers(rangeFactors, range);						//podzial liczby m na liczby pierwsze do spawdzenia warunkow

	//jesli dzielnikiem m jest ona sama to znaczy ze m jest liczba pierwsza i bierzemy tylko pod uwage maxA
	if (rangeFactors.size() == 1)
	{
		return maxA;
	}
	else
	{
		vector <unsigned long long> resB;
		unsigned long long maxB{};

		//b = a-1
		for (unsigned int i = 0; i < resMultipliers.size(); i++)
		{
			resB.push_back(resMultipliers[i] - 1);
		}

		//sprawdzenie czy b % 4 == 0 <=> m % 4 == 0, czyli 3 warunku
		if (range % 4 == 0) {
			for (unsigned int i = 0; i < resB.size(); i++)
			{
				if (resB[i] % 4 != 0)
				{
					resB[i] = 0;
				}
			}
		}

		//sprawdzenie czy b jest wielokrotnoscia kazdej liczby pierwszej ktora dzieli m
		int counter{};

		for (unsigned int i = 0; i < resB.size(); i++)
		{
			for (unsigned int j = 0; j < rangeFactors.size(); j++)
			{
				if (isMultiple(rangeFactors[j], resB[i]) == false || resB[i] == 0) {
					resB[i] = 0;
					counter++;
					break;
				}
			}
		}

		//jesli wszystkie elemnty sa wyzerowane zwracamy maxA, w przeciwnym wypadku szukamy tej liczby i ja zwracamy
		if (counter == resB.size())
			return maxA;
		else
		{
			for (unsigned int i = 0; i < resB.size(); i++)
			{
				if (resB[i] != 0)
					return resMultipliers[i];
			}
		}

	}

	return maxA;
}

unsigned long long generateRandNumb(unsigned long long x0, unsigned long long multiplier, unsigned long long range)
{
	return (multiplier*x0 + increment) % range;
}

void showLCGMenu()
{
	unsigned long long x0{}, xMax{}, amountOfElem{}, range{}, multiplier{};

	cout << "Podaj zakres xmax: ";			
	xMax = loadNonNegativeNumber();										//zaladowanie xMax, czyli do jakiej liczby chcemy losowac; gorna granica

	cout << "Ile liczb chcesz wygenerowac: ";
	amountOfElem = loadNonNegativeNumber();								//zaladowanie amountOfElem, czyli ilosci elementow, ile chcemy wygenerowac

	range = xMax + 1;													//range = m - modul, zakres potrzebny do obliczen
	x0 = 0;																//wstepna inicjalizacja ziarna (seed) jako 0
	multiplier = computeMultiplierA(range);								//obliczenie optymalnego mnoznika a

	unsigned long long *resTab = new unsigned long long[amountOfElem];	//tablica wynikowych wartosci
	fillTableWithLCGRandNumb(resTab, amountOfElem, range, multiplier, x0);

	int choise=4;

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

		case 2:	{
			cout << "Podaj ziarno x0 z przedzialu 0 do xMax: ";
			x0 = loadNumberFromRanges(0, xMax);
			fillTableWithLCGRandNumb(resTab, amountOfElem, range, multiplier, x0);
		}
				break;

		case 3: {
			fstream outFile = createOutputFile();
			saveDataToFileInColumn(resTab, amountOfElem, outFile);
			outFile.close();
		}
		default: 
			break;
		}
	}
	
	delete[] resTab;
}

unsigned long long loadNonNegativeNumber()
{
	long long tmp{};
	bool flag = true;
	
	cin >> tmp;
	if (tmp < 1)
		flag = false;

	while (flag != true)
	{
		cout << "Liczba musi byc wieksza od 0: ";
		cin >> tmp;
		if (tmp >= 1)
			flag = true;
	}

	unsigned long long nnNumber = tmp;
	return nnNumber;
}

unsigned long long loadNumberFromRanges(unsigned long long low, unsigned long long high)
{
	long long tmp{};
	bool flag = true;

	cin >> tmp;
	if (tmp < low || tmp > high)
		flag = false;

	while(flag != true)
	{
		cout << "Liczba nie jest z zakresu (" << low << "," << high << ")!";
		cin >> tmp;
		if (tmp >= low || tmp <= high)
			flag = true;
	}

	unsigned long long result = tmp;
	return result;
}

void fillTableWithLCGRandNumb(unsigned long long *tab, unsigned long long amountOfElem, unsigned long long range, unsigned long long multiplier, unsigned long long x0)
{
	for (int i = 0; i < amountOfElem; i++)
	{
		tab[i] = generateRandNumb(x0, multiplier, range);
		x0 = tab[i];
	}
}

void showTable(unsigned long long * tab, unsigned long long Tsize, unsigned long long startIterator)
{
	for (int i = startIterator; i < Tsize; i++)
	{
		cout << tab[i] << " ";
	}
	cout << endl;
}

