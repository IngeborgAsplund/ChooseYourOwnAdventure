#pragma once
#include<string>
#include<memory>
#include<iostream>
class Item
{
public:
	Item(const std::string& iniÍd, const std::string &inTitle,bool consumable);
	//implement destructor here
	~Item();
	virtual void UseItem()=0;
	const std::string& GetID() const;
	const std::string& GetTitle() const;
	bool GetConsumable();
protected:	 
	std::string id;	 
	std::string title;
	bool isConsumeable;
};
//This item is used to teleport to a set location, may be used for unlocked areas
class TeleportationScroll: public Item
{
public:
	TeleportationScroll(const std::string &inId,const std::string &inTitle, bool consumable, const std::string &inLocationId);
	void UseItem()override;
private:
	std::string teleportationId;
};
//this class is used for consumables such as hardtack and tropical fruit
class FoodItem: public Item
{
public:
	FoodItem(const std::string& inId, const std::string& inTitle, bool consumable, const std::string& description, int satation);
	void UseItem()override;
private:
	std::string useageDescription;
	int sataionvalue;
};
//this type of item is used to convey messages to the player example may include letters, maps and wondrous objects with inscriptions
class MessageItem: public Item
{
public:
	MessageItem(const std::string& inId,const std::string&inTitle,bool consumable,const std::string&inMessage);
	void UseItem()override;
private:
	std::string message;
};
