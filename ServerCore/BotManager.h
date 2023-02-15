#pragma once

#include "BotDiscordModel.h"
#include <dpp/cluster.h>
#include "GenDiscordNameClass.h"

class BotManager
{
public:
	BotManager();
	~BotManager();

	void Connect(const WCHAR* path, uint32 intents = dpp::i_default_intents);

	dpp::cluster* GetCluster();
	BotDiscordModel::Server* GetServer();
	const dnc::Names& GetNames();

private:
	void ParseDiscordXml(const WCHAR* path);

private:
	dpp::cluster* _bot = nullptr;
	BotDiscordModel::Server* _server = nullptr;
	const dnc::Names _names;
};
