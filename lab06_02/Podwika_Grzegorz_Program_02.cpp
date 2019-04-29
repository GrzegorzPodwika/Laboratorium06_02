#include <iostream>
#include "generatorLCG.h"
#include "generatorACG.h"
using namespace std;

void showMenu();

int main() {
	showMenu();

	getchar();
	cin.ignore();
	return 0;
}

void showMenu()
{
	int choise = 5;

	while (choise != 0)
	{
		cout <<
			"********************MENU********************\n"
			"1. Generator LCG\n"
			"2. Generator ACG\n"
			"0. Wyjscie z programu\n"
			"Wybor: ";
		cin >> choise;

		switch (choise)
		{
		case 1:
		{
			showLCGMenu();
		}
		break;

		case 2:
		{
			showACGMenu();
		}
		break;

		default:
			break;
		}
	}
}

