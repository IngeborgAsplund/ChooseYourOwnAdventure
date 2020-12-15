#pragma once
#include<string>
#include<memory>
#include<iostream>
class Item
{
public:
	Item(const std::string& iniÍd, const std::string &inTitle);
	virtual void UseItem()=0;
	const std::string& GetID() const;
	const std::string& GetTitle() const;
protected:	 
	std::string id;	 
	std::string title;
};
class TeleportationScroll: public Item
{
public:
	TeleportationScroll(const std::string &inId,const std::string &inTitle, const std::string &inLocationId);
	virtual void UseItem()override;
private:
	std::string teleportationId;
};
