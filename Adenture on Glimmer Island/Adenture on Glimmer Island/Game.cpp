#include"game.h"
//The function through which the game is run it contains the main gameloop. As the game grows stuff done here will be 
//split up on multiple classes
void Game::Run()
{
	//Location debugging block, checks how many locations there are in the list of gamelocations and that all of the locations
	//choices lead somewhere existing in the game
	std::cout << "Debugging Locations"<<"\n";
	gameData.DebugLocations();
	//welcome message
	std::cout<<"\nAdventure on Glimmer Island"<<"\n";
	//ask the player to enter a name
	std::cout << "\nBefore the game starts, what is your name? \n";
	//read in name
	std::getline(std::cin, player.name);

	std::string  introduce= "\nAfter the ship where %%Name%% worked as a deckhand sunk during a raging storm\n%%Name%% find themselves stranded on the rocky beaches of a tropical island,\nthere %%Name%% have set up a camp on the northern shore.\nWhile waiting or rather hoping for another ship to pass by and pick them up\n %%Name%% are currently doing their best to survive,\nexploring the landscape of the island and collecting whatever resources they can find.\n\n";
	std::regex nameRegex("%%Name%%");
	std::string output = std::regex_replace(introduce, nameRegex, player.name);
	std::cout<< output;
	
	player.currentLocation = gameData.GetStarterLocation();
	isRunning = true;
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
					std::cout << player.visitedLocations[j]->id<<"\n";
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
		//prompt for input
		std::string prompt= "What do %%Name%% want to do?\nPick thir choice through printing the number of the choice and press enter\n";
		std::string promptstring = std::regex_replace(prompt, nameRegex, player.name);
		std::cout << promptstring;
		//read input
		int input;
		std::cin >> input;
		//if input is bigger than zero but less than or equal to the max amount of choices
		if (input > 0 && input <= player.currentLocation->choices.size())
		{
			player.visitedLocations.push_back(player.currentLocation);
			player.currentLocation = gameData.GetLocationWithId(player.currentLocation->choices[input - 1].locationID);
			player.moves++;//increase player moves
		}
		else
			std::cout << "\nFaulty input, please type in the number of the choice you want to take.\n";
		
	}
	
}