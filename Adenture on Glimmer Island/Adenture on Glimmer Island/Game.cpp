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
	std::cout<<"Adventure on Glimmer Island"<<"\n"<<"\n";
	std::cout << "After the ship where you worked as a deckhand on sunk during a raging storm\nyou find yourself stranded on the rocky beaches of" <<
		" a tropical island, there you have set up a camp on the northern shore."<<"\n"<<"While waiting or rather hoping for another ship to pass by and pickk you up"<<
		"\n"<<" you are currently doing your best to survive,\nexploring the landscape of the island and collecting whatever resources you can find.\n\n";
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
		//write out the description for the currentlocation
		std::cout << player.currentLocation->description<<"\n\n";
		//check if choices equals zero
		if(player.currentLocation->choices.size()==0)
		{
			//if so remark the game have ended
			std::cout << "\n" << "The story of the Adventure of Glimmer Island has come to an end.";
			isRunning = false;//set isrunning false
			return;// return back to top, exiting the loop
		}
		//write out all of the choices for the current location
		for(int i =0;i<player.currentLocation->choices.size();i++)
		{
			std::cout << player.currentLocation->choices[i].choiceDescription<<"\n";
		}
		//prompt for input
		std::cout << "\n" << "What do You want to do?\nPick your choice through printing the number of your choice and press enter\n";
		//read input
		int input;
		std::cin >> input;
		//if input is bigger than zero but less than or equal to the max amount of choices
		if(input>0&&input<=player.currentLocation->choices.size())
		{
			player.currentLocation = gameData.GetLocationWithId(player.currentLocation->choices[input - 1].locationID);
			player.moves++;//increase player moves
		}
		std::cout << "\nYour current amount of moves is " << player.moves<<"\n";//write out the current number of moves.
	}
	
}