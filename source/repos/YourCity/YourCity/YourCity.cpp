// YourCity.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <conio.h>
#include <ctime>
#include "Game.h"
#include <Windows.h>
#include "Player.h"

int main()
{
	HANDLE hwnd = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hwnd, 15);

	std::cout << "WITAJ W GRZE PANSTWA-MIASTA\nPROSZE WYBIERZ COS SOBIE Z MENU:\n";
	std::cout << "1.START\n2.ZASADY\n3.WYJSCIE\n";

	srand(time(0));
	const int MAX = 4;
	
	Game myGame;
	Player myPlayers[MAX];
	Player* pPlayers[MAX];

	int nPlayers;
	char choice = 0;
	bool mySwitch = true;

	while (choice != '3') 
	{
		choice = _getch();
		if (choice == '1')
		{
			std::cout << "PODAJ ILOSC GRACZY: ";
			std::cin >> nPlayers;
			while (!(nPlayers >= 2 && nPlayers <= 4))
			{
				std::cout << "MINIMUM 2 GRACZY\n";
				std::cin >> nPlayers;
			}
			myGame.StartGame(myPlayers, pPlayers, nPlayers, hwnd);
			myGame.CategoryLoss(hwnd);
			myGame.LetterLoss(hwnd);
			myGame.CountDown(pPlayers, &choice, hwnd, &mySwitch);
		}
		else if (choice == '2')
			myGame.Rules(hwnd);
		else
			std::cout << "PROSZE WYBRAC PONOWNIE COS INNEGO\n"; 
	}
	std::cout << "DZIEKUJE ZA GRE, ZYCZE MILEGO DNIA!\n";

	system("pause");
    return 0;
}

