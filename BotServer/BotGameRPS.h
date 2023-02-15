#pragma once

enum : int8
{
	SCISSORS = 0,
	ROCK = 1,
	PAPER = 2
};

class BotGameRPS
{
public:
	void GameInit(const dpp::ready_t& event);
	void CreateCommand();
	void SlashCommand(const dpp::slashcommand_t& event);

public:
	const string _gameName = u8"가위바위보";
	const string _gameParam = u8"선택";
	const string _gameDesc = u8"승리 +500원/무승부 0원/패배 -500원";

	/* 옵션 값 (디스코드에서 이모지) */
	const string _eScissors = u8":v:"; // 0
	const string _eRock = u8":fist:"; // 1
	const string _ePaper = u8":raised_hand:"; // 2

	/* 옵션 이름 */
	const string _scissors = u8"가위"; // 0
	const string _rock = u8"바위"; // 1
	const string _paper = u8"보"; // 2


private:
	bool CheckUserMoney(const dpp::slashcommand_t& event);
	void GameProcess(const dpp::slashcommand_t& event, string param);
	string NumToString(int8 v);
	int8 StringToNum(string v);
};
