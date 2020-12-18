#include"items.h"
#include"game.h"
//extern game variable for the game
extern Game game;
Item::Item(const std::string &inId,const std::string &inTitle, bool consumable)
{
	id = inId;
	title = inTitle;
	isConsumeable = consumable;
}
//default destructor of the item class this will be called when 
Item::~Item(){}
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
bool Item::GetConsumable() 
{
	return isConsumeable; 
}
//Teleportationscroll specific functions
TeleportationScroll::TeleportationScroll(const std::string& inId, const std::string& inTitle,bool consumable, const std::string& inLocationId):Item(inId,inTitle, consumable)
{
	teleportationId = inLocationId;
}
FoodItem::FoodItem(const std::string& inId, const std::string& inTitle,bool consumable, const std::string& description, int satation):Item(inId,inTitle, consumable)
{
	useageDescription = description;
	sataionvalue = satation;
}
MessageItem::MessageItem(const std::string& inId, const std::string& inTitle,bool consumable, const std::string& inMessage):Item(inId,inTitle,consumable)
{
	message = inMessage;
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
void FoodItem::UseItem()
{
	if(game.player.satation<100)
	{
		game.player.satation += sataionvalue;
		if (game.player.satation > 100)
			game.player.satation = 100;
	}
	std::cout << useageDescription << "\n";
}
void MessageItem::UseItem()
{
	std::cout << "\n" << message << "\n";
}



