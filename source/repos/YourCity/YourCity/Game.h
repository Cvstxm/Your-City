#pragma once
#include <iostream>
#include <string>
#include <Windows.h>
#include <conio.h>
#include <vector>
#include "Player.h"

class Game
{
private:
	int Category;
	int myTime;
	int pNumbers;
	char Letter;

public:
	Game(int timess = 15);
	~Game();
	void StartGame(Player players[], Player* pPlayers[], int hMuch, HANDLE &handle, int points = 0);
	void Rules(HANDLE &handle) const;
	void Loading(HANDLE &handle, int load = 5) const;
	void CategoryLoss(HANDLE &handle);
	void LetterLoss(HANDLE &handle);
	void CountDown(Player* pPlayers[], char* choice, HANDLE &handle, bool* switcher, int miliseconds = 1000);
	void Answers(Player* pPlayers[], char* choice, int number, HANDLE &handle, bool switcher, const int MAX_POINTS = 100);
	void SwitchColor(HANDLE &hwnd, bool sColor) const;
	void ChoicePlayer(Player* pPlayers[], char* choice, int myTime, HANDLE &handle, bool switcher);
};

