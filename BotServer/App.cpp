#include "pch.h"
#include "BotManager.h"
#include "DBConnectionPool.h"
#include "DBSynchronizer.h"
#include "BotService.h"
#include "XmlParser.h"
#include "GenProcedures.h"
#include <dpp/snowflake.h>

int main()
{
	SetConsoleOutputCP(CP_UTF8);
	setlocale(LC_ALL, ".UTF8");

	{
		// DB 및 디스코드 봇 연결

		ASSERT_CRASH(
			GDBConnectionPool->Connect(1,
				L"Driver={SQL Server};Server=DESKTOP-G2PFA7N;Database=Bigeumdo_test;Trusted_Connection=Yes;"
			));

		GBotManager->Connect(L"Discord.xml",
		                     dpp::i_default_intents | dpp::i_message_content | dpp::i_guild_members |
		                     dpp::i_all_intents);
	}

	{
		/* DB XML 동기화 */
		DBConnection* dbConn = GDBConnectionPool->Pop();
		DBSynchronizer dbSync(*dbConn);
		dbSync.Synchronize(L"DB.xml");
		GDBConnectionPool->Push(dbConn);
	}

	dpp::cluster* bot = GBotManager->GetCluster();

	bot->on_log(dpp::utility::cout_logger());

	auto botService = new BotService();
	botService->Start();

	bot->start(false);
}
