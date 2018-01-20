#pragma once
#include <string>
#include<iostream>


class Player
{
private:
	std::string Name;
	int Points;

public:
	Player(int points = 0);
	~Player();
	void AddName();
	void AddPoints();
	void ShowName() const;
	void ShowPoints() const;
	bool Winner(const int MAX_POINTS) const;
};

