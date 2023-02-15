#pragma once

namespace BotDiscordModel
{
	class Channel
	{
	public:
		wstring _name;
		dpp::snowflake _id;
	};

	class Category
	{
	public:
		wstring _name;
		dpp::snowflake _id;
		map<wstring, Channel*> _channels;
		wstring _cName;
	};

	class Role
	{
	public:
		wstring _name;
		dpp::snowflake _id;
	};

	class Server
	{
	public:
		wstring _name;
		string _token;
		dpp::snowflake _id;
		map<wstring, Role*> _roles;
		map<wstring, Category*> _categories;
	};
}
