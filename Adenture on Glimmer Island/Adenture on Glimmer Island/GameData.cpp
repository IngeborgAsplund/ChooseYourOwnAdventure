#include"gameData.h"
//The Gamedata cpp file containing the functions needed to run the core functionality of the game
// it is responsible for building up the locations alongside their choices

//Constructor that setup the gameword calling the function for creating locations and then the one for debugging them
GameData::GameData()
{
	CreateLocations();
	DebugLocations();
}
void GameData::DebugLocations()
{
	for(int i = 0;i<gameLocations.size();i++)
	{
		std::cout<<"\n"<<gameLocations[i].id;
		std::cout << "\n" << gameLocations[i].description;
		//go through all of the locations choices and write them out along with where they lead
		for(int j =0;j<gameLocations[i].choices.size();j++)
		{
			std::cout << "\n" << gameLocations[i].choices[j].choiceDescription;
			std::cout << "\n" << gameLocations[i].choices[j].locationID;
		}
	}
}
//Create a number of locations you can visit on Glimmer Island and set up their choices.
void GameData::CreateLocations()
{
	gameLocations.push_back(Location("Campsite", "A small flickering fire in the middle on the cliffy beach.\nIt is surrounded by vreckage from various ships.\nBehind you are the sea, and to the south lies a thick jungle."));
	gameLocations.push_back(Location("Jungle","Thick vines and lush threes surrounds you on all sides.\nThere are lots of flowers and you can hear birds and insects among the foliage.\nAmong the underbrush a thin path moves forward."));
	gameLocations.push_back(Location("Dark Campsite", "As you put out the flames of the camppfire the surrounding goes dark\nmaking a swarm of fireflies the only remaining lightsource."));
	gameLocations.push_back(Location("Wreckage","There are wreckaged parts from at least three different ships here of which one was the one you came with"));
	gameLocations.push_back(Location("Ruins","You came upon a set of old temple ruins in the middle of the jungle. It is partially grown over with vines and moss"));
	gameLocations.push_back(Location("Temple Entrance","You enter the ruins and comes upon the entrance to what seem to be an ancient temple"));

	gameLocations[0].choices.push_back(LocationChoice("Dark Campsite","Extinguish the campfire"));
	gameLocations[0].choices.push_back(LocationChoice("Jungle", "Walk south towards the Jungle"));
	gameLocations[0].choices.push_back(LocationChoice("Wreckage", "Examine the wreckaged ships"));

	gameLocations[1].choices.push_back(LocationChoice("Ruins", "Follow the path."));
	gameLocations[1].choices.push_back(LocationChoice("Campsite", "Go back to camp"));

	gameLocations[2].choices.push_back(LocationChoice("Campsite", "Light the fire again"));
	gameLocations[2].choices.push_back(LocationChoice("Jungle", "Follow the fireflies"));

	gameLocations[3].choices.push_back(LocationChoice("Campsite", "Go back to camp"));

	gameLocations[4].choices.push_back(LocationChoice("Temple", "Walk into the ruins"));
	gameLocations[4].choices.push_back(LocationChoice("Jungle", "Go back"));

	gameLocations[5].choices.push_back(LocationChoice("Ruins", "Go back out into the Ruins"));
}