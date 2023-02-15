#include "pch.h"
#include "BotManager.h"
#include "XmlParser.h"

BotManager::BotManager()
{
}

BotManager::~BotManager()
{
	delete _bot;
	auto roles = _server->_roles;
	for (auto role : roles)
	{
		delete role.second;
	}

	auto categories = _server->_categories;
	for (auto category : categories)
	{
		auto channels = category.second->_channels;
		for (auto channel : channels)
		{
			delete channel.second;
		}
		delete category.second;
	}
}


void BotManager::Connect(const WCHAR* path, uint32 intents)
{
	ParseDiscordXml(path);

	if (_server == nullptr)
	{
		GConsoleLogger->WriteStdOutWithTime(Color::RED, L"Server info is empty\n");
		return;
	}

	if (_server->_token.empty())
	{
		GConsoleLogger->WriteStdOutWithTime(Color::RED, L"Token is empty\n");
		return;
	}
	_bot = new dpp::cluster(_server->_token, intents);

	GConsoleLogger->WriteStdOutWithTime(Color::BLUE, L"[Discord] 디스코드 봇 연결 성공\n");
}

dpp::cluster* BotManager::GetCluster()
{
	return _bot;
}

BotDiscordModel::Server* BotManager::GetServer()
{
	return _server;
}

const dnc::Names& BotManager::GetNames()
{
	return _names;
}

void BotManager::ParseDiscordXml(const WCHAR* path)
{
	XmlNode root;
	XmlParser parser;
	ASSERT_CRASH(parser.ParseFromFile(path, OUT root));

	XmlNode server = root.FindChild(L"Server");

	auto s = new BotDiscordModel::Server();
	s->_name = server.GetStringAttr(L"name");
	s->_id = dpp::snowflake(server.GetInt64Attr(L"id"));
	s->_token = ConvertW2MBS(server.GetStringAttr(L"token"));

	vector<XmlNode> role = server.FindChildren(L"Role");
	for (XmlNode& r : role)
	{
		wstring name = r.GetStringAttr(L"name");
		dpp::snowflake id = r.GetInt64Attr(L"id");

		auto nr = new BotDiscordModel::Role();
		nr->_id = id;
		nr->_name = name;
		s->_roles.insert({name, nr});
	}

	vector<XmlNode> categories = server.FindChildren(L"Category");
	for (XmlNode& category : categories)
	{
		auto ca = new BotDiscordModel::Category();
		ca->_name = category.GetStringAttr(L"name");
		ca->_id = category.GetInt64Attr(L"id");

		vector<XmlNode> channels = category.FindChildren(L"Channel");
		for (XmlNode& channel : channels)
		{
			wstring name = channel.GetStringAttr(L"name");
			dpp::snowflake id = channel.GetInt64Attr(L"id");

			auto ch = new BotDiscordModel::Channel();
			ch->_id = id;
			ch->_name = name;

			ca->_channels.insert({name, ch});
		}

		s->_categories.insert({ca->_name, ca});
	}

	_server = s;
}
