#include "pch.h"
#include "BotGameRPS.h"

#include "BotManager.h"

void BotGameRPS::GameInit(const dpp::ready_t& event)
{
	dpp::cluster* bot = GBotManager->GetCluster();

	const dpp::snowflake advId = GBotManager->GetServer()->_roles[L"adventurer"]->_id;

	bot->global_command_delete(1075041201750806618);

	bot->global_command_create(
		dpp::slashcommand()
		.set_name(_gameName)
		.set_description(_gameDesc)
		.add_permission(
			dpp::command_permission(advId, dpp::command_permission_type::cpt_role, true))
		.add_option(
			dpp::command_option(dpp::co_string, _gameParam, u8"가위, 바위, 보중 하나를 선택해주세요!", true)
			.add_choice(dpp::command_option_choice(_scissors, string(_eScissors)))
			.add_choice(dpp::command_option_choice(_rock, string(_eRock)))
			.add_choice(dpp::command_option_choice(_paper, string(_ePaper)))
		)
	);
}

void BotGameRPS::SlashCommand(const dpp::slashcommand_t& event)
{
	if (!CheckUserMoney(event))
	{
		event.reply(dpp::message(u8"돈이 부족합니다.").set_flags(dpp::m_ephemeral));
		return;
	}

	auto param = std::get<std::string>(event.get_parameter(_gameParam));

	GameProcess(event, param);
}

bool BotGameRPS::CheckUserMoney(const dpp::slashcommand_t& event)
{
	return true;
}

void BotGameRPS::GameProcess(const dpp::slashcommand_t& event, string param)
{
	srand(static_cast<uint64>(time(nullptr)));
	string resultString;
	int8 botRandVal = rand() % 3;
	int8 userVal = StringToNum(param);
	int8 resultVal = 0; // 승/무/패 1/0/-1

	resultString = u8"봇: " + NumToString(botRandVal) + u8"\n당신: " + param + u8"\n";

	if (botRandVal == userVal)
	{
		resultVal = 0;
	}
	else
	{
		if (botRandVal == SCISSORS)
		{
			if (userVal == ROCK)
			{
				resultVal = 1;
			}
			else
			{
				resultVal = -1;
			}
		}
		else if (botRandVal == ROCK)
		{
			if (userVal == SCISSORS)
			{
				resultVal = -1;
			}
			else
			{
				resultVal = 1;
			}
		}
		else
		{
			if (userVal == SCISSORS)
			{
				resultVal = 1;
			}
			else
			{
				resultVal = -1;
			}
		}
	}


	if (resultVal == 0)
	{
		resultString += u8"비겼습니다.";
	}
	else if (resultVal == 1)
	{
		resultString += u8"이겼습니다!";
	}
	else
	{
		resultString += u8"졌습니다...";
	}

	event.reply(dpp::message(resultString).set_flags(dpp::m_ephemeral));
}

string BotGameRPS::NumToString(int8 v)
{
	if (v == SCISSORS)
	{
		return _eScissors;
	}
	if (v == ROCK)
	{
		return _eRock;
	}
	return _ePaper;
}

int8 BotGameRPS::StringToNum(string v)
{
	if (v == _eScissors)
	{
		return SCISSORS;
	}
	if (v == _eRock)
	{
		return ROCK;
	}
	return PAPER;
}
