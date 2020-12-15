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
	std::string name;
	std::vector<InventoryItem> inventory;
	std::vector<std::shared_ptr<Location>> visitedLocations;
	Player()
	{
		currentLocation = nullptr;
		moves = 0;
	}
	void AddItem(const std::string &id,int amountToAdd);//we would want to be able to add items to the inventory
	void RemoveItem(const std::string& id, int amountToRemove);//and remove them	
	
};
