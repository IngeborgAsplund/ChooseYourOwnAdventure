#include"items.h"
#include"game.h"
//extern game variable for the game
extern Game game;
Item::Item(const std::string &inId,const std::string &inTitle)
{
	id = inId;
	title = inTitle;
}
//the base functionality for the items this will later be overriden
void Item::UseItem()
{
	std::cout << "You reach into your bag and pick out " << title << "\n";
}
//getter functions for the base item.
const std::string& Item::GetID()const
{
	return id;
}
const std::string& Item::GetTitle()const
{
	return title;
}
//Teleportationscroll specific functions
TeleportationScroll::TeleportationScroll(const std::string& inId, const std::string& inTitle, const std::string& inLocationId):Item(inId,inTitle)
{
	teleportationId = inLocationId;
}
void TeleportationScroll::UseItem()
{
	std::shared_ptr<Location> destination = game.gameData.GetLocationWithId(teleportationId);

	if(destination !=nullptr)
	{
		std::cout << "You read the words on the ancient scroll,\nfor a secound the world seem to shift and you are no longer at the same place.\n";
		game.player.currentLocation = destination;
	}
}

