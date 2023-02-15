#pragma once

#include "BotRegsterService.h"
#include "BotGameRPS.h"

class BotService
{
public:
	BotService();
	~BotService();

	void Start();

private:
	BotRegsterService* _regService;
	BotGameRPS* _gameRPS;
};
