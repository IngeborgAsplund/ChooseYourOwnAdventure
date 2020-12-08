#include"gameData.h"
//The Gamedata cpp file containing the functions needed to run the core functionality of the game
// it is responsible for building up the locations alongside their choices

//Constructor that setup the gameword calling the function for creating locations and then the one for debugging them
GameData::GameData()
{
	bool location = LoadLocationsFromFile("locations.txt");
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
//Create a number of locations you can visit on Glimmer Island and set up their choices. Now obsolete, can be used for debugging though.
void GameData::CreateLocations()
{
	gameLocations.push_back(Location("Campsite", "A small fire is flickering in the middle of the cliffy beach.\nIt is surrounded by vreckage from various ships.\nBehind %%Name%% surge the open sea, and to the south lies a thick jungle."));
	gameLocations.push_back(Location("Jungle","Thick vines and lush threes surrounds %%Name%% on all sides.\nThere are lots of flowers and %%Name%% can hear birds and insects among the foliage.\nAmong the underbrush a thin path moves forward."));
	gameLocations.push_back(Location("Dark Campsite", "As %%Name%% put out the flames of the camppfire the surrounding goes dark\nmaking a swarm of fireflies the only remaining lightsource."));
	gameLocations.push_back(Location("Wreckage","There are wreckaged parts from at least three different ships here of which one was the ship %%Name%% came with"));
	gameLocations.push_back(Location("Ruins","%%Name%% came upon a set of old temple ruins in the middle of the jungle. It is partially grown over with vines and moss"));
	gameLocations.push_back(Location("Temple Entrance","%%Name%% enter the ruins and comes upon the entrance to what seem to be an ancient temple.\n There are two corridors, one continuing south from where %%Name%% stand\nand one turning to the left"));
	gameLocations.push_back(Location("Small waterfall","The fireflies seem to be drawn to a small waterall hitting a lagoon suth west of the camp.\nThe lagoon is surrounded by jungle threes and %%Name%% can hear the humming of thousands of tropical insects in the distance"));

	gameLocations.push_back(Location("Left Corridor", "Turning to the left %%Name%% enter a long corridor.\nWithered stonewalls on towers on both sides of %%Name%% and an further down %%Name%% se a doorway and a set of stairs leading down."));
	gameLocations.push_back(Location("Main Corridor", "Walkning south from the temple entance %%Name%% come upon three doorways,\none to the right, one to the left and one to the south "));
	gameLocations.push_back(Location("Ritual Chamber","%%Name%% enter a small room, walls and floor made of greenish overgrown stones.\n In the middle sits the remnants of a black stone altar."));
	gameLocations.push_back(Location("Pit Chamber", "%%Name%% enter a large rectangular room lined with stone stairs leading down to a pit in the middle.\n a shallow layer of water cover the floor of the pit"));
	gameLocations.push_back(Location("Round Chamber", "The room %%Name%% have entered is big with rounded walls, clear indents or pockets in the walls appear with regular frequencey.\nThere are eith of them in total"));
	gameLocations.push_back(Location("Octagon Chamber", "%%Name%% enter a large octagonal chamber, empty skanses lines the wall with frequent intervalls\nand in the middle a garagantum statue of a strange creature seemingly made up of snakes rests.\n it is partially overgrown with jungle flora."));
	gameLocations.push_back(Location("Lower Floor", "Decending down the staors %%Name%% come upon a big open space.\nFour low square shaped plattforms is located in each corner of the room\nin the far end %%Name%% se a single glowing doorway shaped like an eye."));
	gameLocations.push_back(Location("Chamber of Lor'Ashack", "A huge chamber stretches out in front of %%Name%%. Towards what seem to be a steaming subterrainian lake.\nAlongside the wall several statues depicting a creature partially made up of snakes is lined up.\n A low ominous hissing sound can be heard near the waterline"));
	gameLocations.push_back(Location("Lor'Ashack", "From the water rises a creature, a dangling mass of rotten seaweed,\nseveral bestial heads attached to a massive body of some huge aquatic animal\n and from the central mass a cluster of snakelike tendrils ending in gaping toothy maws.\n The creature lets out a menacing roar."));
	gameLocations.push_back(Location("Death1", "Two massive tentacles rips away the statue %%Name%% where hiding behind.\nSoon %%Name%% feel the wet sticky texture of the tentacles wrapping around their torso.\n As you are dragged toward the waterline %%Name%% can feel the sharp pain of teeth sinking into their left shoulder."));
	//campsite
	gameLocations[0].choices.push_back(LocationChoice("Dark Campsite","1. Extinguish the campfire"));
	gameLocations[0].choices.push_back(LocationChoice("Jungle", "2. Walk south towards the Jungle"));
	gameLocations[0].choices.push_back(LocationChoice("Wreckage", "3. Examine the wreckaged ships"));
	//Jungle
	gameLocations[1].choices.push_back(LocationChoice("Ruins", "1. Follow the path."));
	gameLocations[1].choices.push_back(LocationChoice("Campsite", "2. Go back to camp"));
	//dark campsite
	gameLocations[2].choices.push_back(LocationChoice("Campsite", "1. Light the fire again"));
	gameLocations[2].choices.push_back(LocationChoice("Small waterfall", "2. Follow the fireflies"));
	//wreckage on beach
	gameLocations[3].choices.push_back(LocationChoice("Campsite", "1. Go back to camp"));
	//Ruins in the Jungle
	gameLocations[4].choices.push_back(LocationChoice("Temple Entrance","1. Enter the temple ruins"));
	gameLocations[4].choices.push_back(LocationChoice("Jungle", "2. Go back"));
	//temple entrance
	gameLocations[5].choices.push_back(LocationChoice("Main Corridor", "1. Follow the main corridor"));
	gameLocations[5].choices.push_back(LocationChoice("Left Corridor", "2. Go to the left"));
	gameLocations[5].choices.push_back(LocationChoice("Ruins", "3. Go back"));
	//lagoon
	gameLocations[6].choices.push_back(LocationChoice("Dark Campsite", "1. Go back to camp."));
	//left corridor
	gameLocations[7].choices.push_back(LocationChoice("Octagon Chamber", "1. Enter Doorway"));
	gameLocations[7].choices.push_back(LocationChoice("Lower Floor", "2. Go down the stairs"));
	gameLocations[7].choices.push_back(LocationChoice("Temple Entrance", "3. Go back"));
	//main corridor
	gameLocations[8].choices.push_back(LocationChoice("Ritual Chamber", "1. Enter doorway to the right"));
	gameLocations[8].choices.push_back(LocationChoice("Pit Chamber", "2. Enter doorway to the left"));
	gameLocations[8].choices.push_back(LocationChoice("Round Chamber", "3. Enter doorway to the south"));
	gameLocations[8].choices.push_back(LocationChoice("Temple Entrance", "4. Go back"));
	//ritual chamber
	gameLocations[9].choices.push_back(LocationChoice("Main Corridor", "1. Go back"));
	//pit chanmber
	gameLocations[10].choices.push_back(LocationChoice("Main Corridor", "1. Go back"));
	//round chamber
	gameLocations[11].choices.push_back(LocationChoice("Main Corridor", "1. Go back"));
	//octagon chamber
	gameLocations[12].choices.push_back(LocationChoice("Left Corridor", "1. Go back"));
	//lower floor
	gameLocations[13].choices.push_back(LocationChoice("Chamber of Lor'Ashack", "1. Go through the glowing eye"));
	gameLocations[13].choices.push_back(LocationChoice("Left Corridor", "2. Go back up the stairs"));
	//Chamber of Lor'Ashack
	gameLocations[14].choices.push_back(LocationChoice("Lor'Ashack", "1. Gingerly move towards the waterline"));
	gameLocations[14].choices.push_back(LocationChoice("Lower Floor", "2. Go back, making sure not to make a noise"));
	//Lor'Ashack encounter
	gameLocations[15].choices.push_back(LocationChoice("Death1","1. Hide Behind one of the statues"));
	gameLocations[15].choices.push_back(LocationChoice("Temple Entrance", "2. Run!"));
}
//Find the first object in our game locations list when it is not empty 
bool GameData::LoadLocationsFromFile(const std::string& fileName)
{
	std::ifstream stream(fileName);
	std::string line;
	Location working("", "");
	std::string id;
	if(stream.is_open())
	{
		while(std::getline(stream,line))
		{
			// Skips forward if first character is /
			//I know the strech goal want me to include % as a signal for this first step to jump but that would interefer with 
			//my already defined regex %%Name%% which sometimes is the first that appears on a new line.
			if (line.length() == 0||line[0]=='/') { continue; }
			if(line[0]=='#')
			{
				id = line.substr(1, line.npos);
				working.id = id;
				continue;
			}
			if(line[0]=='&')
			{
				int colonIndex = line.find(':');
				std::string locid = line.substr(1, colonIndex - 1);
				std::string locdesc = line.substr(colonIndex + 1, line.npos);
				working.choices.push_back(LocationChoice(locid, locdesc));
				continue;
			}
			if(line=="===")
			{
				gameLocations.push_back(working);
				working.choices.clear();
				working.id.clear();
				working.description.clear();
				continue;
			}
			else
			{				
				working.description += line.substr(0, line.npos)+"\n";			
			}
		}
		stream.close();
		return true;
	}
	else 
	{
		std::cout << "Unable to open " << fileName << "Please check that the path is correct";
	}
	return false;
}


Location* GameData::GetStarterLocation()
{
	if (gameLocations.size() > 0)
		return &gameLocations[0];
	std::cout << "\n" << "Error: the list of locations where empty";
	return nullptr;
}
Location* GameData::GetLocationWithId(const std::string id)
{
	for(int i =0;i<gameLocations.size();i++)
	{
		if (gameLocations[i].id == id)
			return &gameLocations[i];
	}
	return nullptr;
}