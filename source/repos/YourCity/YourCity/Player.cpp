#include "stdafx.h"
#include "Player.h"
#include <string>

Player::Player(int points)
{
	Points = points;
}

Player::~Player()
{
}

void Player::AddName()
{
	std::cin >> Name;
}

void Player::AddPoints()
{
	Points += 10;
}

void Player::ShowName() const
{
	std::cout << Name;
}

void Player::ShowPoints() const
{
	std::cout << Points << std::endl;
}

bool Player::Winner(const int MAX_POINTS) const
{
	if (Points == MAX_POINTS)
		return true;
}
