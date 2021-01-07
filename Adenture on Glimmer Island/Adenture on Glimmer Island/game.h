#pragma once
#include"gameData.h"
#include"player.h"

class Game
{
public:
	GameData gameData;//initialize class gamedata
	Player player;//initialize struct player
	void Run(); 

private:
	//variables
	bool isRunning;
	//functions
	void ShowMenue(std::regex inRegex);//this is called whenever we want to bring up the games menue, right now it has two options exit and new game
	void ShowvInventory();
	std::vector<LocationChoice> FindAvailableChoices();
	void SaveGame();
	void LoadGame();
	std::string NameInput();//take input from the player
	int CastStringToInt(std::string &castMe);//try and cast the string returning an errormessage to console if failing

};
