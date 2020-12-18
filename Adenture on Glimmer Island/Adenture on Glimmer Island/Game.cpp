#include<iostream>
#include"game.h"
//The function through which the game is run it contains the main gameloop. As the game grows stuff done here will be 
//split up on multiple classes
void Game::Run()
{
	//Location debugging block, checks how many locations there are in the list of gamelocations and that all of the locations
	//choices lead somewhere existing in the game
	std::cout << "Debugging Locations"<<"\n";
	gameData.DebugLocations();
	std::regex nameRegex("%%Name%%");
	ShowMenue(nameRegex);
	//start game loop
	while (isRunning)
	{
		//check that player. currentlocation is not a nullpointer
		if(player.currentLocation==nullptr)
		{
			std::cout<<"\n"<<"the location currently set as current location do not exist, please make sure all of the locations in the choices is valid";
			isRunning = false;//is running is false
			return;//return to the top breaking the while loop
		}
		
		std::string roomDescription = std::regex_replace(player.currentLocation->description, nameRegex, player.name);
		std::cout << roomDescription<<"\n\n";
		//check so that we havent added the id to the visiedlocations vector
		if (std::find(player.visitedLocations.begin(), player.visitedLocations.end(), player.currentLocation->id) == player.visitedLocations.end())
		{
			player.visitedLocations.push_back(player.currentLocation->id);
		}
		if (player.currentLocation->items.size() > 0)
		{
			for (int i = 0; i < player.currentLocation->items.size(); i++)
			{
				if(gameData.GetItemById(player.currentLocation->items[i])!=nullptr)
				{
				  player.AddItem(player.currentLocation->items[i], 1);
				  std::cout << "You picked up " << player.currentLocation->items[i]<<"\n";
				}
			}
		}
		//check if choices equals zero
		if(player.currentLocation->choices.size()==0)
		{
			//if so remark the game have ended
			std::cout << "\n" << "The story of the Adventure of Glimmer Island has come to an end.";
			std::cout << "\nYour moves this game was " << player.moves << "\n";//write out the current number of moves.
			std::cout << "\n" << "You visited the following locations durning the game\n";
			if(player.visitedLocations.size()>0)
			{
				for(int j = 0;j<player.visitedLocations.size();j++)
				{
					std::cout << player.visitedLocations[j]<<"\n";
				}
			}

			isRunning = false;//set isrunning false
			return;// return back to top, exiting the loop
		}
		//write out all of the choices for the current location
		for(int i =0;i<player.currentLocation->choices.size();i++)
		{
			std::cout << player.currentLocation->choices[i].choiceDescription<<"\n";			
		}
		
		std::cout << "Menue [m]\n"<<"Inventory[i]\n";//write out input call pr the menue
		isRunning = player.CheckHungerStatus(nameRegex);
		//prompt for input
		std::string prompt= "What do %%Name%% want to do?\nPick their choice through printing the number of the choice and press enter\n";
		std::string promptstring = std::regex_replace(prompt, nameRegex, player.name);
		std::cout << promptstring;
		SaveGame();
		//read input
		std::string inputstring;
		int input;
		std::cin >> inputstring;
		if(inputstring[0]=='m')
		{
			ShowMenue(nameRegex);
		}
		if(inputstring[0]=='i')
		{
			ShowvInventory();
		}
		else
		{
			std::string::size_type st;
			input = std::stoi(inputstring, &st);
			//if input is bigger than zero but less than or equal to the max amount of choices
			if (input > 0 && input <= player.currentLocation->choices.size())
			{
				
				player.currentLocation = gameData.GetLocationWithId(player.currentLocation->choices[input - 1].locationID);
				player.moves++;//increase player moves
				player.satation -= 5;
			}
			
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
		isRunning = true;
		return;
	}
	if(input==2)
	{
		isRunning = false;
		return;
	}
	if(input==3)
	{
		LoadGame();
		isRunning = true;
	}
	else
	{
		std::cout << "\n Faulty input. Please input must range between 1-2";
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
		return;//exit this function
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



