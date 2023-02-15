#include "pch.h"
#include "BotService.h"
#include "BotManager.h"

BotService::BotService()
{
	_regService = new BotRegsterService();
	_gameRPS = new BotGameRPS();
}

BotService::~BotService()
{
	delete _regService;
}

void BotService::Start()
{
	dpp::cluster* bot = GBotManager->GetCluster();

	bot->on_ready([&](const dpp::ready_t& event)
	{
		if (dpp::run_once<struct register_user_service>())
		{
			_regService->ServiceInit(event);
		}

		if (dpp::run_once<struct game_rps>())
		{
			_gameRPS->GameInit(event);
		}
	});

	bot->on_slashcommand([&](const dpp::slashcommand_t& event)
	{
		if (event.command.get_command_name() == _gameRPS->_gameName)
		{
			_gameRPS->SlashCommand(event);
		}
		else
		{
			GConsoleLogger->WriteStdOutWithTime(Color::RED, L"[DPP] on_slashcommand 이벤트 핸들러 오류\n");
		}
	});

	bot->on_button_click([&](const dpp::button_click_t& event)
	{
		if (event.custom_id == _regService->_buttonId)
		{
			_regService->ShowModal(event);
		}
		else
		{
			GConsoleLogger->WriteStdOutWithTime(Color::RED, L"[DPP] on_button_click 이벤트 핸들러 오류\n");
		}
	});

	bot->on_form_submit([&](const dpp::form_submit_t& event)
	{
		if (event.custom_id == _regService->_inputId)
		{
			_regService->Submit(event);
		}
		else
		{
			GConsoleLogger->WriteStdOutWithTime(Color::RED, L"[DPP] on_form_submit 이벤트 핸들러 오류\n");
		}
	});
}
