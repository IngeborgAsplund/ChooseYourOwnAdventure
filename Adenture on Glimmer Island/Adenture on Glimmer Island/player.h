#pragma once
#include<iostream>
#include "gameData.h"
//Information about the player, contain the currentLocation and possible Moves
struct Player
{
	Location* currentLocation;
	int moves;
	std::string name;
	std::vector<Location*> visitedLocations;
	Player()
	{
		currentLocation = nullptr;
		moves = 0;
	}
};
