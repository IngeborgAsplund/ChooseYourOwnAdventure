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
	if (gameLocations.size() > 0) 
	{
		std::cout << "\n" << "There are " << gameLocations.size() << " locations in the world";
		//loop through  the locations and se if their choices leads to valid locations ie the locations the choice leads to exists in the array of locations
		for (int i = 0; i < gameLocations.size(); i++)
		{			
			if (NoDuplicates(gameLocations[i].id))
			{
				//check that all of the location ids for the choices are findable in the list of gamelocations.
				for (int j = 0; j < gameLocations[i].choices.size(); j++)
				{
					if (!Validate(gameLocations[i].choices[j].locationID))
						std::cout << "\n" << "The next location id of " << gameLocations[i].choices[j].choiceDescription << " is invalid need to lead to location that exist";
				}
			}
			else 
			{

				std::cout << "\n"<<gameLocations[i].id<<" appears more than once please remove the ducplicate locations or change the id if intending to add a similar but slightly different location";
					return;
			}
		}
	}
	else
		std::cout << "\n" << "No locations are added to the gameworld";
	
}
//Check the sent in string towards the location ids in the list of gamelocations. if more than one location has the same id this will stop and return back out
//false.
bool GameData::NoDuplicates(std::string& element)
{
	int elementOccurance = 0; // this is increased whenever Location.id is equal to in string 
	for(int i =0;i<gameLocations.size();i++)
	{
		if (element == gameLocations[i].id)
			elementOccurance++;
	}
	if (elementOccurance > 1)
		return false;

	return true;
}

bool GameData::Validate(std::string& id)
{
	for(int i = 0;i<gameLocations.size();i++)
	{
		if (id == gameLocations[i].id)
			return true;
	}
	return false;
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

	gameLocations[4].choices.push_back(LocationChoice("Temple Entrance","Walk into the ruins"));
	gameLocations[4].choices.push_back(LocationChoice("Jungle", "Go back"));

	gameLocations[5].choices.push_back(LocationChoice("Ruins", "Go back out into the Ruins"));
}