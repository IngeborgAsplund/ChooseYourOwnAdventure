#include<iostream>
#include"game.h"
GameState state;
//The function through which the game is run it contains the main gameloop. As the game grows stuff done here will be 
//split up on multiple classes
void Game::Run()
{
	//Location debugging block, checks how many locations there are in the list of gamelocations and that all of the locations
	//choices lead somewhere existing in the game
	std::cout << "Debugging Locations"<<"\n";
	gameData.DebugLocations();
	std::regex nameRegex("%%Name%%");
	isRunning = true;	
	state = GameState::MENUE;
	//start game loop
	while (isRunning)
	{		
		if( state==GameState::MENUE)
			ShowMenue(nameRegex);			
		if(state==GameState::RUNNING)
			RunMainLoop(nameRegex);			
		if(state== GameState::INVENTORY)
			ShowvInventory();			
				
	}
	
}
//This function sorts out the choices for each location into an own separate vector that it returns for the main function to use for presenting choices
std::vector<LocationChoice> Game::FindAvailableChoices()
{
	std::vector<LocationChoice> choicesToPresent;
	for(int i = 0; i<player.currentLocation->choices.size();i++)
	{
		std::shared_ptr<Location> temp = gameData.GetLocationWithId(player.currentLocation->choices[i].locationID);
		//the majority case
		if(!player.AlreadyVisited(temp->id)&&!temp->requireKey)
		{
			choicesToPresent.push_back(player.currentLocation->choices[i]);
		}
		else if(!temp->uinqueLocation&&!temp->requireKey)
		{					
			choicesToPresent.push_back(player.currentLocation->choices[i]);
		}
		else 
		{
			if(temp->requireKey)
			{
				if (player.FindItem(temp->key)!=nullptr)
				{
					choicesToPresent.push_back(player.currentLocation->choices[i]);
				}
			}
		}

	}
	return choicesToPresent;
}
void Game::RunMainLoop(std::regex inRegex)
{
	//check that player. currentlocation is not a nullpointer
	if (player.currentLocation == nullptr)
	{
		std::cout << "\n" << "the location currently set as current location do not exist, please make sure all of the locations in the choices is valid";
		isRunning = false;//is running is false
		return;//return to the top breaking the while loop
	}

	std::string roomDescription = std::regex_replace(player.currentLocation->description, inRegex, player.name);
	std::cout << roomDescription << "\n\n";
	//check so that we havent added the id to the visiedlocations vector
	if (!player.AlreadyVisited(player.currentLocation->id))
	{
		//if not see if there are any items to pick up from the location
		if (player.currentLocation->items.size() > 0)
		{
			//go through the list of items 
			for (int i = 0; i < player.currentLocation->items.size(); i++)
			{
				//and add them to the player if they are not equal to null
				if (gameData.GetItemById(player.currentLocation->items[i]) != nullptr)
				{
					player.AddItem(player.currentLocation->items[i], 1);
					std::cout << "You picked up " << player.currentLocation->items[i] << "\n";
				}
			}
		}
		if (player.currentLocation->negativeItems.size() > 0)
		{
			for (int k = 0; k < player.currentLocation->negativeItems.size(); k++)
			{
				if (gameData.GetItemById(player.currentLocation->negativeItems[k]) != nullptr)
				{
					player.RemoveItem(player.currentLocation->negativeItems[k], 1);
					std::cout << "\nUsed up " << player.currentLocation->negativeItems[k] << "\n";
				}
			}
		}
		player.visitedLocations.push_back(player.currentLocation->id);
	}
	//check if choices equals zero
	if (player.currentLocation->choices.size() == 0)
	{
		//if so remark the game have ended
		std::cout << "\n" << "The story of the Adventure of Glimmer Island has come to an end.";
		std::cout << "\nYour moves this game was " << player.moves << "\n";//write out the current number of moves.
		std::cout << "\n" << "You visited the following locations durning the game\n";
		if (player.visitedLocations.size() > 0)
		{
			for (int j = 0; j < player.visitedLocations.size(); j++)
			{
				std::cout << player.visitedLocations[j] << "\n";
			}
		}

		isRunning = false;//set isrunning false
		return;// return back to top, exiting the loop
	}
	//write out all of the choices for the current location
	std::vector<LocationChoice> available = FindAvailableChoices();
	for (int i = 0; i < available.size(); i++)
	{
		std::cout << i + 1 << ". " << std::regex_replace(available[i].choiceDescription, inRegex, player.name) << "\n";
	}

	std::cout << "Menue [m]\n" << "Inventory[i]\n";//write out input call pr the menue
	isRunning = player.CheckHungerStatus(inRegex);
	//prompt for input
	std::string prompt = "What do %%Name%% want to do?\nPick their choice through printing the number of the choice and press enter\n";
	std::string promptstring = std::regex_replace(prompt, inRegex, player.name);
	std::cout << promptstring;
	SaveGame();
	//read input
	std::string inputstring;
	int input;
	std::cin >> inputstring;
	if (inputstring[0] == 'm')
	{
		state = GameState::MENUE;		
	}
	if (inputstring[0] == 'i')
	{
		state = GameState::INVENTORY;	
	}
	else
	{

		input = CastStringToInt(inputstring);
		//if input is bigger than zero but less than or equal to the max amount of choices
		if (input > 0 && input <= available.size())
		{
			player.currentLocation = gameData.GetLocationWithId(available[input - 1].locationID);
			player.moves++;//increase player moves
			player.satation -= 5;			
		}

	}

}
void Game::ShowMenue(std::regex inRegex)
{
	isRunning = false;//temporary shut of the game
	std::cout << "\nWelcome to the Adventure of Glimmer Island choose the alternative you want to pursue\nselecting the number in front of it\n";
	std::cout << "1. Start a new game"<<"\n"<<"2. Exit\n"<<"3. Load SaveGame\n";
	int input;
	std::cin >> input;
	if(input ==1)
	{
		player.SetUpPlayer();
		player.currentLocation = gameData.GetStarterLocation();
		std::string  introduce = "\nAfter the ship where %%Name%% worked as a deckhand sunk during a raging storm\n%%Name%% find themselves stranded on the rocky beaches of a tropical island,\nthere %%Name%% have set up a camp on the northern shore.\nWhile waiting or rather hoping for another ship to pass by and pick them up\n %%Name%% are currently doing their best to survive,\nexploring the landscape of the island and collecting whatever resources they can find.\n\n";
		std::string output = std::regex_replace(introduce, inRegex, player.name);
		std::cout << output;
		state = GameState::RUNNING;//set the game state to running
		
	}
	if(input==2)
	{
		isRunning = false;
		
	}
	if(input==3)
	{
		LoadGame();
		state = GameState::RUNNING;
	}
	if(input<1||input>3)
	{
		std::cout << "\n Faulty input. Please input must range between 1-3";
	}
}
//when showing the inventory this function is called
void Game::ShowvInventory()
{
	for (int i = 0; i < player.inventory.size(); i++)
	{
		for(int j =0; j < gameData.gameItems.size();j++)
		{
			if(player.inventory[i].itemId == gameData.gameItems[j]->GetID())
			{
				std::cout << i + 1 << ". " << gameData.gameItems[j]->GetTitle()<<"["<<player.inventory[i].amount<<"]"<<"\n";
			}
		}
	}
	std::cout << "[i] Close inventory\n";
	std::string inventoryInput;
	std::cin >> inventoryInput;
	if (inventoryInput[0] == 'i')
	{
		state = GameState::RUNNING;
	}
	else
	{
		std::string::size_type stringToInt;
		int input = std::stoi(inventoryInput, &stringToInt);
		for(int i = 0; i<gameData.gameItems.size(); i++)
		{
			if(player.inventory[input-1].itemId==gameData.gameItems[i]->GetID()&&player.inventory[input-1].amount>0)
			{
				gameData.gameItems[i]->UseItem();
				//only remove items that is consumeable
				if(gameData.gameItems[i]->GetConsumable())
				{
				     player.RemoveItem(player.inventory[input - 1].itemId, 1);//remove one of the items
				}
				return;
			}
		}
		std::cout << "Item selected do not exist, you need to find more of "<<player.inventory[input-1].itemId<<"\n";
	}
}
std::string Game::NameInput()
{
	std::string name;
	std::cin >> name;
	return name;
}
//save down the information inside the current location along the players name and current amount of moves. I did not save down the visited locations
//as you do not use that while playing and there could be a value to get a new output on what you decided to visit each time you play rather than a recording
//of every single location visited since the game first started.
void Game::SaveGame()
{
	std::ofstream stream("savegame.txt");
	if (stream.is_open())
	{
		stream << "#" << player.currentLocation->id << "\n";
		stream <<"*"<<player.name<<"\n";
		stream << player.moves<<"\n";
		for(int i = 0;i<player.visitedLocations.size(); i++)
		{
			stream << "~" << player.visitedLocations[i] << "\n";
		}
		stream.close();
	}
	else
		std::cout << "Could not open savefile\n";
}
//load a saved game from menue, can only be done when we have a saved game to load from
void Game::LoadGame()
{
	std::string line;
	std::ifstream stream("savegame.txt");
	if (stream.is_open())
	{
		while (std::getline(stream, line))
		{
			if (line.length() == 0) { continue; }
			if (line[0] == '#')
			{
				std::string id = line.substr(1, line.npos);
				player.currentLocation = gameData.GetLocationWithId(id);
				continue;
			}
			if (line[0] == '*')
			{
				player.name = line.substr(1, line.npos);
				continue;
			}
			if(line[0]=='~')
			{
				player.visitedLocations.push_back(line.substr(1, line.npos));
			}
			else
			{
				std::string::size_type st;
				player.moves = std::stoi(line, &st);
				continue;
			}
		}
		stream.close();
	}
	else
		std::cout << "Cannot open savefile\n";
}
//whenever we ask the player for input we want to use this to catch wrongful input whenever we want to cast a string to an int.
int Game:: CastStringToInt(std::string &castMe)
{
	std::string::size_type st;	
	try
	{
		int output = std::stoi(castMe, &st);
		return output;
	}
	catch(const std::invalid_argument& exception)
	{
		std::cout << "Input was invalid, cannot cast letters to an int";
	}
	return 0;
}



