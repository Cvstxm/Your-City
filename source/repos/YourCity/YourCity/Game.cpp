#include "stdafx.h"
#include "Game.h"
#include <string>


Game::Game(int timess)
{
	myTime = timess;
}

Game::~Game()
{
}

void Game::StartGame(Player players[], Player* pPlayers[], int hMuch, HANDLE &handle, int points)
{
	pNumbers = hMuch;
	for (int i = 0; i < hMuch; i++) 
	{
		pPlayers[i] = &players[i];
		std::cout << "Gracz " << i+1 << ": ";
		SwitchColor(handle, true);
		pPlayers[i]->AddName();
		SwitchColor(handle, false);
	}
}

void Game::Rules(HANDLE &handle) const
{
	system("cls");
	SwitchColor(handle, true);
	std::cout << "ZASADY GRY SA PROSTE. PO WPISANIU IMION GRACZY ROZPOCZYNA SIE LOSOWANIE, A NASTEPNIE ODLICZANIE CZASU(15 SEKUND)\n";
	std::cout << "PO ZAKONCZENIU ODLICZANIA WYMAGANE JEST WCISNIECIE KLAWISZA, KTÓRY JEST PRZYPISANY DO ODPOWIENIO PODANYCH GRACZY\nW KOLEJNOSCI:\n";
	std::cout << "GRACZ 1: Q\n";
	std::cout << "GRACZ 2: W\n";
	std::cout << "GRACZ 3: E\n";
	std::cout << "GRACZ 4: R\n";
	std::cout << "DO GRY WYMAGANE JEST MINIMUM 2 OSOBY. PO WCISNIECY ODPOWIEDNIEGO KLAWISZA GRACZE MIEDZY SOBA UZASADNIAJA CZY ODPOWIEDZ\nJEST ZLA CZY DOBRA\n";
	std::cout << "JEZELI ODPOWIEDZ JEST POZYTYWNA PRZYZNAWANE JEST 10 PUNKTÓW DANEMU GRACZOWI, A GRACZ KTORY PIERWSZY UZYSKA 100pkt,\nWYGRYWA GRE!\n";
	std::cout << "WCISNIJ 1, ABY ZACZAC GRE LUB 3, ABY WYJSC!\n";
	SwitchColor(handle, false);
}

void Game::SwitchColor(HANDLE &hwnd, bool sColor) const
{
	if (sColor == true)
		SetConsoleTextAttribute(hwnd, 10);
	else if (sColor == false)
		SetConsoleTextAttribute(hwnd, 15);
}

void Game::Loading(HANDLE &handle, int load) const
{
	std::cout << "LOSUJE: ";
	SwitchColor(handle, true);
	for (int i = 0; i < load; i++) 
	{
		std::cout << char(219);
		Sleep(500);
	}
	SwitchColor(handle, false);
	std::cout << std::endl;
}

void Game::CategoryLoss(HANDLE &handle)
{
	Loading(handle);
	Category = rand() % 6 + 1;
	switch (Category)
	{
	case 1: std::cout << "WYLOSOWANO KATEGORIE: "; SwitchColor(handle, true); std::cout << "PANSTWO\n"; SwitchColor(handle, false); break;
	case 2: std::cout << "WYLOSOWANO KATEGORIE: "; SwitchColor(handle, true); std::cout << "MIASTO\n"; SwitchColor(handle, false); break;
	case 3: std::cout << "WYLOSOWANO KATEGORIE: "; SwitchColor(handle, true); std::cout << "ROSLINA\n"; SwitchColor(handle, false); break;
	case 4: std::cout << "WYLOSOWANO KATEGORIE: "; SwitchColor(handle, true); std::cout << "IMIE\n"; SwitchColor(handle, false); break;
	case 5: std::cout << "WYLOSOWANO KATEGORIE: "; SwitchColor(handle, true); std::cout << "ZWIERZE\n"; SwitchColor(handle, false); break;
	case 6: std::cout << "WYLOSOWANO KATEGORIE: "; SwitchColor(handle, true); std::cout << "RZECZ\n"; SwitchColor(handle, false); break;
	}
}

void Game::LetterLoss(HANDLE &handle)
{
	Loading(handle);
	Letter = rand() % 25 + 65;
	std::cout << "WYLOSOWANO LITERE: ";
	SwitchColor(handle, true);
	std::cout << Letter << std::endl;
	SwitchColor(handle, false);
	Sleep(2500);
}

void Game::ChoicePlayer(Player* pPlayers[], char* choice, int myTime, HANDLE &handle, bool switcher)
{
		std::cout << "KTORY GRACZ ZNA ODPOWIEDZ??\n";
		*choice = _getch();

		if (*choice == 'q')
			Answers(pPlayers, choice, 0, handle, switcher);
		else if (*choice == 'w')
			Answers(pPlayers, choice, 1, handle, switcher);
		else if (pNumbers == 3 && *choice == 'e')
			Answers(pPlayers, choice, 2, handle, switcher);
		else if (pNumbers == 4 && *choice == 'r')
			Answers(pPlayers, choice, 3, handle, switcher);
		else
		{
			switcher = false;
			std::cout << "ZA MALO GRACZY. SPROBUJ JESZCZE RAZ!\n";
			Sleep(2500);
			CountDown(pPlayers, choice, handle, &switcher);
		}
	}


void Game::CountDown(Player* pPlayers[], char* choice, HANDLE &handle, bool* switcher, int miliseconds)
{
	if (*switcher == true)
	{
		while (myTime != 0)
		{
			std::cout << "ROZPOCZYNAM ODLICZANIE CZASU: ";
			std::cout << myTime--;
			Sleep(miliseconds);
			system("cls");
		}
		myTime = 15;
		ChoicePlayer(pPlayers, choice, myTime, handle, switcher);
	}
	else if(*switcher == false)
	{
		*switcher = true;
		ChoicePlayer(pPlayers, choice, myTime, handle, switcher);
	}
}

void Game::Answers(Player* pPlayers[], char* choice, int number, HANDLE &handle, bool switcher, const int MAX_POINTS)
{
	std::cout << "Gracz: "; pPlayers[number]->ShowName();
	std::cout << " NACISNIETO: " << *choice << " CZY ODPOWIEDZ JEST PRAWIDLOWA? WYBIERZ <T> LUB <N>\n";
	std::cin >> *choice;

		if (*choice == 't')
		{
			pPlayers[number]->AddPoints();
			std::cout << "Przyznaje 10 punktow dla "; pPlayers[number]->ShowName();
			std::cout << std::endl;
			std::cout << "Oto twoje punkty: "; pPlayers[number]->ShowPoints(); 
			std::cout << std::endl;
			Sleep(2500);
			if (pPlayers[number]->Winner(MAX_POINTS) == true)
			{
				std::cout << "BRAWO GRE WYGYRWA: "; pPlayers[number]->ShowName(); 
				std::cout << std::endl;
				std::cout << "ABY ZAGRAC JESZCZE RAZ WCISNIJ: 1 LUB 2, ABY WYJSC Z GRY\n";
			}
			else
			{
				switcher = true;
				CategoryLoss(handle);
				LetterLoss(handle);
				CountDown(pPlayers, choice, handle, &switcher);
			}
		}
		else if (*choice == 'n')
		{
			switcher = true;
			std::cout << "PRZYKRO MI TA ODPOWIEDZ JEST BLEDNA! JEDZIEMY DALEJ!\n";
			Sleep(2500);
			CategoryLoss(handle);
			LetterLoss(handle);
			CountDown(pPlayers, choice, handle, &switcher);
		}
	}

