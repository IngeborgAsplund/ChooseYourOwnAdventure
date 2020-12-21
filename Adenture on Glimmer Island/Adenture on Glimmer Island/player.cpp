# include "player.h"
//player related functions started to be many so I moved these to a new file
//function that add an inventory item to the player providing an id and an amount of items added
void Player::AddItem(const std::string& id, int amountToAdd)
{
	//check if we already has the inventory item
	for (int i = 0; i < inventory.size(); i++)
	{
		//if so we want to just increase the amount of items
		if (id == inventory[i].itemId)
		{
			inventory[i].amount += amountToAdd;
			return;
		}
	}
	inventory.push_back(InventoryItem(id, amountToAdd));
}
//Item removal functions similar to the above but remove the amount of items specified.
void Player::RemoveItem(const std::string& id, int amountToRemove)
{
	for (int i = 0; i < inventory.size(); i++)
	{
		if (id == inventory[i].itemId)
		{			
			inventory[i].amount -= amountToRemove;
			if (inventory[i].amount <= 0)
				inventory[i].amount = 0;//here we can remove the item completely in the future.
			return;
		}
	}
	std::cout << "There where no items of type " << id << " in the inventory";
}
//check the status of the players hunger message the player when they get hungry and apply consequences for starvation
bool Player::CheckHungerStatus(std::regex inRegex)
{
	std::string message;//what we want to write to the console
	if (satation <= 50)
	{
		message = "\n\n%%Name%% is getting hungry\n\n";
		std::cout << std::regex_replace(message, inRegex, name);
		return true;
	}
	if (satation <= 20)
	{
		message = "\n\n%%Name%% is getting very hungry\n\n";
		std::cout << std::regex_replace(message, inRegex, name);
		return true;
	}
	if (satation <= 0)
	{
		satation = 0;
		message = "\n\nGame over %%Name%% has died of starvation.\n\n";
		std::cout << std::regex_replace(message, inRegex, name);
		return false;
	}
	return true;
}
//boolean that check if visited locations already contains a given location
bool Player::AlreadyVisited(std::string compareLoc)
{
	if (std::find(visitedLocations.begin(), visitedLocations.end(), compareLoc) != visitedLocations.end())
		return true;
	return false;
}
//Search for 
std::shared_ptr<InventoryItem>Player::FindItem(const std::string& search)
{
	for(int it = 0; it< inventory.size();it++)
	{
		if (search == inventory[it].itemId)
		{
			std::shared_ptr<InventoryItem> returnval = std::make_shared<InventoryItem>(inventory[it]);
			return returnval;
		}
	}
	return nullptr;
}
//set up all but the players starter location and the ininital console output this serves the purpose of making the menue code in the main game loop more readable
void Player::SetUpPlayer()
{
	std::cout << "\nBefore the game starts, what is your name? \n";
	std::cin>>name;
	moves = 0;
	satation = 100;
	AddItem("Scroll01", 1);
	AddItem("hardtack", 6);
}