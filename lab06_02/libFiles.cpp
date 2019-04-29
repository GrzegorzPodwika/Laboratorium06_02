#include "libFiles.h"
#include <iostream>
#include <string>
#include <fstream>
using namespace std;

void loadCorrectFileName(char *fileName)
{
	cin >> fileName;
	int nameLength = strlen(fileName);
	bool flag = false;

	for (int i = 1; i <= 3; i++)
	{
		if (i == 3) {
			cout << "Przekroczono limit prob wprowadzenia wlasciwej nazwy.";
			cin.ignore();
			exit(0);
		}

		for (int j = 0; j < nameLength; j++)
		{
			if (j <= nameLength - 4 && fileName[j] == '.' && fileName[j + 1] == 't' && fileName[j + 2] == 'x' && fileName[j + 3] == 't') {
				flag = true;
				break;
			}
		}

		if (flag)
			break;
		else {
			cout << "Bledna nazwa pliku! Podaj nazwe z rozszerzeniem .txt!" << endl;
			cin >> fileName;
			nameLength = strlen(fileName);
		}
	}
}

fstream createInputFile()
{
	char fileName[50];
	cout << "Podaj nazwe pliku do oczytu z rozszerzeniem .txt  ";
	loadCorrectFileName(fileName);
	bool flag = false;

	while (!flag) {

		fstream rFile(fileName, ios::in);

		if (rFile) {
			flag = true;
			cout << "Poprawnie wczytano plik...\n";
			//Sleep(1500);
			return rFile;
		}
		else {
			cout << "Nie ma pliku z taka nazwa, sprobuj ponownie!" << endl;
			loadCorrectFileName(fileName);
		}
	}
}

fstream createOutputFile()
{
	char fileName[50];
	cout << "Podaj nazwe pliku do zapisu z rozszerzeniem .txt  ";
	loadCorrectFileName(fileName);
	bool flag = false;

	while (!flag) {

		fstream rFile(fileName, ios::out);

		if (rFile) {
			flag = true;
			cout << "Poprawnie utworzono plik do zapisu...";
			//Sleep(1500);
			cout << endl;
			return rFile;
		}
		else {
			cout << "Nie mozna utworzyc pliku z taka nazwa, sprobuj ponownie!" << endl;
			loadCorrectFileName(fileName);
		}
	}
}

void saveDataToFileInColumn(unsigned long long *tab, unsigned long long Tsize, std::fstream & outFile, int startIterator)
{
	for (int i = startIterator; i < Tsize; i++)
	{
		outFile << tab[i] << endl;
	}
}
