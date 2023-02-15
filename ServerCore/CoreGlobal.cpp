#include "pch.h"
#include "CoreGlobal.h"
#include "DBConnectionPool.h"
#include "BotManager.h"
#include "ConsoleLog.h"

DBConnectionPool* GDBConnectionPool = nullptr;
BotManager* GBotManager = nullptr;
ConsoleLog* GConsoleLogger = nullptr;

class CoreGlobal
{
public:
	CoreGlobal()
	{
		GDBConnectionPool = new DBConnectionPool();
		GBotManager = new BotManager();
		GConsoleLogger = new ConsoleLog();
	}

	~CoreGlobal()
	{
		delete GDBConnectionPool;
		delete GBotManager;
		delete GConsoleLogger;
	}
} GCoreGlobal;
