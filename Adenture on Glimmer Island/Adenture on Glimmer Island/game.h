#pragma once
#include"gameData.h"
#include"player.h"

class Game
{
public:
	GameData gameData;//initialize struct gamedata
	Player player;//initialize struct player

	void Run();

private:
	bool isRunning;
};
