#pragma once
#include<iostream>
#include<string>
#include<vector>
//this file contains the definition of all data necessary for the game to run, things like locations, location choices NPCs 
// and similar

//############################################################################
//data structure for the choices that players can make when they enter a location in the game for instance "fight the troll" id "figthscene"
struct LocationChoice
{
	std::string locationID;//choice leads here
	std::string choiceDescription;// what the choice is
	// Since the constructor for this one is so short I choose to define it here in the headerfile, for longer functions I would just leave the declaration
	//and put the implementation in the cpp file.
	LocationChoice(std::string nextLocation,std::string description)
	{
		locationID = nextLocation;
		choiceDescription = description;
	}
};
// data structure for  locations which the player may come upon during the game, for instance campsite, forest, village, shore etc
struct Location
{
	std::string id;
	std::string description;
	std::vector<LocationChoice> choices;
	//the constructor takes in strings rather than string references right now as the strings are defined at creation of this struct
	// in the future when predefined strings is used I will change these to string references, the same goes for the Location choice above
	Location(std::string locationId,std::string inDescription)
	{
		id = locationId;
		description = inDescription;
	}
};
class GameData 
{
public:
	GameData();//constructor, calls the debuglocations and setup the gameworld
	void DebugLocations();//write out the id and description of all the locations in the game world.
private:
	std::vector<Location> gameLocations;

	void CreateLocations();//create locations and place them in the locations array below
	bool NoDuplicates(std::string& element); //search for the input string location id in the gamelocations list and see so that there are no duplicates
	bool Validate(std::string& id); // compare the next id towards all location ids in the GameLocations if found this will come out true.
};