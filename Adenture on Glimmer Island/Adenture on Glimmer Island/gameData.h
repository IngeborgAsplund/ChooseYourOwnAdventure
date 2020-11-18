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
	// A question I may have around this is that I have encountered different ways of doing the below. It works both to do as I have done below with
	// the constructor and define it in the header or you can include the definition of the constructor and then implement it in the 
	//cpp file. Which way is the best to do?
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
	//Question about & from what I have understood they should be used when passing objects like strings but I seem to not get the structs to work
	// when using them. Adding strings to the struct while using the & generate errors.
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
	void CreateLocations();//create locations and place them in the locations array below
	std::vector<Location> gameLocations;
};