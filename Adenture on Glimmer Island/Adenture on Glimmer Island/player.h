#pragma once
#include<memory>
#include<iostream>
#include "gameData.h"
struct InventoryItem
{	//constructor
	InventoryItem(const std::string& inId,int inAmount)
	{
		itemId = inId;
		amount = inAmount;
	}
	std::string itemId;
	int amount = 1;
};
//Information about the player, contain the currentLocation and possible Moves
struct Player
{
	std::shared_ptr<Location> currentLocation;
	int moves;
	int satation;//how full is the player, he/she will be starting out with this value at 100
	std::string name;
	std::vector<InventoryItem> inventory;
	std::vector<std::string> visitedLocations;
	Player()
	{
		currentLocation = nullptr;
		moves = 0;
	}
	void AddItem(const std::string &id,int amountToAdd);//we would want to be able to add items to the inventory
	void RemoveItem(const std::string& id, int amountToRemove);//and remove them
	std::shared_ptr<InventoryItem> FindItem(const std::string& search);//search player inventory and return the value of specific item
	void SetUpPlayer();//sets up the main information relevant to the player
	bool AlreadyVisited(std::string compareLoc);//have we already visited this location
	bool CheckHungerStatus(std::regex inRegex);//this check the current state of the players hunger
};
