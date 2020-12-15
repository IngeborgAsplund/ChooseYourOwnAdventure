#include"gameData.h"
//The Gamedata cpp file containing the functions needed to run the core functionality of the game
// it is responsible for building up the locations alongside their choices

//Constructor that setup the gameword calling the function for creating locations and then the one for debugging them
GameData::GameData()
{
	InitializeLocations();
	InitializeItems();

}
void GameData::DebugLocations()
{	
	if (gameLocations.size() > 0) 
	{
		std::cout << "\n" << "There are " << gameLocations.size() << " locations in the world";
		//loop through  the locations and se if their choices leads to valid locations ie the locations the choice leads to exists in the array of locations
		for (int i = 0; i < gameLocations.size(); i++)
		{
			if (NoDuplicates(gameLocations[i]->id))
			{
				//check that all of the location ids for the choices are findable in the list of gamelocations.
				for (int j = 0; j < gameLocations[i]->choices.size(); j++)
				{
					if (!Validate(gameLocations[i]->choices[j].locationID))
						std::cout << "\n" << "The next location id of " << gameLocations[i]->choices[j].choiceDescription << " is invalid need to lead to location that exist";
				}
			}
			else 
			{

				std::cout << "\n"<<gameLocations[i]->id<<" appears more than once please remove the ducplicate locations or change the id if intending to add a similar but slightly different location";
			}
		}
	}
	else
		std::cout << "\n" << "No locations are added to the gameworld";
	
}
//Check the sent in string towards the location ids in the list of gamelocations. if more than one location has the same id this will stop and return back out
//false.
bool GameData::NoDuplicates(const std::string& element)
{
	int elementOccurance = 0; // this is increased whenever Location.id is equal to in string 
	for(int i =0;i<gameLocations.size();i++)
	{
		if (element == gameLocations[i]->id)
			elementOccurance++;
	}
	if (elementOccurance > 1)
		return false;

	return true;
}

bool GameData::Validate(const std::string& id)
{
	for(int i = 0;i<gameLocations.size();i++)
	{
		if (id == gameLocations[i]->id)
			return true;
	}
	return false;
}

//Find the first object in our game locations list when it is not empty 
bool GameData::LoadLocationsFromFile(const std::string& fileName)
{
	std::ifstream stream(fileName);
	std::string line;
	Location working ("","");
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
				std::shared_ptr<Location> add = std::make_shared<Location>(working);
				gameLocations.push_back(add);
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
//Item Initialization
void GameData::InitializeItems()
{
	//create a new item of type teleportationscroll
	std::shared_ptr<TeleportationScroll> scroll01{ new TeleportationScroll("Scroll01","Mystic old scroll","Temple Entrance") };
	//push back to vector so we can use it
	gameItems.push_back(scroll01);
}
//Here we load locations from a number of textfiles enabling us to organize the game locations better.
void GameData::InitializeLocations()
{
	for ( int i=1;i<=4;i++)
	{
		std::string fileToLoad = "locations" + std::to_string(i)+".txt";
		bool load = LoadLocationsFromFile(fileToLoad);
		if(!load)
		{
			std::cout << "Warning couldn't load" << fileToLoad<<" double check the adress exists\n";
			return;//break loop if a file could not load a file
		}
	}
}
//get item pointers
std::shared_ptr<Location> GameData::GetStarterLocation()
{
	if (gameLocations.size() > 0)
		return gameLocations[0];
	std::cout << "\n" << "Error: the list of locations where empty";
	return nullptr;
}
std::shared_ptr<Location> GameData::GetLocationWithId(const std::string &id)
{
	for(int i =0;i<gameLocations.size();i++)
	{
		if (gameLocations[i]->id == id)
			return gameLocations[i];
	}
	return nullptr;
}
std::shared_ptr<Item> GameData::GetItemById(const std::string &itemId)
{
	for(int i = 0; i<gameItems.size();i++)
	{
		if(gameItems[i]->GetID()==itemId)
		{
			return gameItems[i];
		}
	}
	return nullptr;
}
