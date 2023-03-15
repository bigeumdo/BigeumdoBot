#include "pch.h"
#include "BotRegsterService.h"
#include "DBConnectionPool.h"
#include "BotManager.h"
#include "GenProcedures.h"
#include <regex>

BotRegsterService::BotRegsterService()
	: _channelId(
		GBotManager->GetServer()->_categories[GBotManager->GetNames().categories.pier._name]->_channels[GBotManager->
			GetNames().categories.pier._reg]->_id) //TODO: 간략화
{
}

BotRegsterService::~BotRegsterService()
{
}

void BotRegsterService::ServiceInit(const dpp::ready_t& event)
{
	dpp::cluster* bot = GBotManager->GetCluster();
	dpp::message_map mm = bot->messages_get_sync(_channelId, 0, 0, 0, 10);

	bool updateFlag = false;
	for (auto m : mm)
	{
		if (m.second.components[0].components[0].custom_id != _buttonId)
		{
			bot->message_delete(m.first, _channelId);
			updateFlag = true;
		}
	}

	if (updateFlag)
	{
		const string content =
			u8"```\n[가입 안내]\n\n비금도에 오신것을 환영합니다.\n닉네임은 한글, 영문, 숫자로 이뤄진 2 ~ 8 글자만 가능합니다.\n아래 '가입' 버튼을 통해 가입할 수 있습니다.```";

		dpp::message message = dpp::message(_channelId, content).add_component(
			dpp::component()
			.add_component(
				dpp::component().set_label(u8"가입").
				                 set_type(dpp::cot_button).
				                 set_style(dpp::cos_success).
				                 set_id(_buttonId))

		);

		bot->message_create(message);
	}
}

void BotRegsterService::ShowModal(const dpp::button_click_t& event)
{
	try
	{
		CheckAuth(event.command.member.user_id, event.command.member);

		dpp::interaction_modal_response modal("reg_input", u8"비금도 가입");

		modal.add_component(
			dpp::component().
			set_label(u8"닉네임 입력").
			set_id("field_id").
			set_type(dpp::cot_text).
			set_placeholder(u8"2-8 글자").
			set_min_length(2).
			set_max_length(8).
			set_text_style(dpp::text_short)
		);

		event.dialog(modal);
	}
	catch (RegstrationException e)
	{
		event.reply(dpp::message(e.GetMessageD()).set_flags(dpp::m_ephemeral));
	}
}

void BotRegsterService::Submit(const dpp::form_submit_t& event)
{
	event.thinking(true);

	auto v = get<string>(event.components[0].components[0].value);
	WCHAR* ws = ConvertS2W(v);
	char* s = ConvertW2MBS(ws);

	/* 가입 프로세스 예외 처리 */
	try
	{
		ValidateNickName(ws);
		CheckNameOverlap(ws);
		RegisterExcute(ws, event.command.member.user_id);
		ChangeMemberRole(ws, event.command.member.user_id);
		ChangeMemberName(event.command.member, s);

		event.edit_response(dpp::message(u8"가입 성공! 잠시후 비금도에 도착합니다."));
	}
	catch (RegstrationException e)
	{
		event.edit_response(dpp::message(e.GetMessageD()));
		GConsoleLogger->WriteStdOutWithTime(Color::RED, L"%ws : %ws\n", e.GetMessageC().c_str(), ws);
	}

	delete ws;
	delete s;
}

void BotRegsterService::CheckAuth(const dpp::snowflake& id, dpp::guild_member member)
{
	DBConnection* dbConn = GDBConnectionPool->Pop();
	WCHAR name[16];
	int64 role;

	SP::CheckAuth checkAuth(*dbConn);
	checkAuth.In_DiscordId(id);
	checkAuth.Out_Name(name);
	checkAuth.Out_Role(role);

	checkAuth.Execute();

	GDBConnectionPool->Push(dbConn);

	if (checkAuth.Fetch())
	{
		ChangeMemberName(member, ConvertW2MBS(name));
		ChangeMemberRole(name, member.user_id);
		throw RegstrationException(ERRORNO::ALREADY);
	}

	GConsoleLogger->WriteStdOutWithTime(Color::BLUE, L"%lld: 최초 가입\n", id);
}


void BotRegsterService::ValidateNickName(const WCHAR* v)
{
	wregex reg(L"([a-z|0-9|가-힣]+)?");
	wcmatch ret;

	if (regex_match(v, OUT ret, reg) == false)
	{
		throw RegstrationException(ERRORNO::INVALID);
	}
	GConsoleLogger->WriteStdOutWithTime(Color::BLUE, L"%ws: 유효성 검사 통과 성공\n", v);
}

void BotRegsterService::CheckNameOverlap(const WCHAR* v)
{
	DBConnection* dbConn = GDBConnectionPool->Pop();

	WCHAR name[BUFFER_MAX];
	int32 id;
	wcscpy_s(name, BUFFER_MAX, v);

	SP::CheckNameOverlap checkNameOverlap(*dbConn);
	checkNameOverlap.In_Name(name);
	checkNameOverlap.Out_Id(OUT id);

	checkNameOverlap.Execute();

	GDBConnectionPool->Push(dbConn);

	if (checkNameOverlap.Fetch())
	{
		throw RegstrationException(ERRORNO::OVERLAP);
	}

	GConsoleLogger->WriteStdOutWithTime(Color::BLUE, L"%ws: 중복 검사 통과 통과\n", v);
}

void BotRegsterService::RegisterExcute(const WCHAR* v, int64 id)
{
	DBConnection* dbConn = GDBConnectionPool->Pop();

	WCHAR name[BUFFER_MAX];
	wcscpy_s(name, BUFFER_MAX, v);

	TIMESTAMP_STRUCT tstamp{0,};
	time_t timer = time(nullptr);
	tm t;
	errno_t error;
	error = localtime_s(&t, &timer);
	if (error == 0)
	{
		SQLSMALLINT year = t.tm_year + 1900;
		SQLUSMALLINT month = t.tm_mon + 1;
		SQLUSMALLINT day = t.tm_mday;
		SQLUSMALLINT hour = t.tm_hour;
		SQLUSMALLINT minute = t.tm_min;
		SQLUSMALLINT second = t.tm_sec;
		tstamp = TIMESTAMP_STRUCT{
			year, month, day, hour, minute, second, 0
		};
	}

	SP::InsertUser insertUser(*dbConn);
	insertUser.In_DiscordId(id);
	insertUser.In_Name(name);
	insertUser.In_Money(100000);
	insertUser.In_Role(
		static_cast<int64>(GBotManager->GetServer()->_roles[GBotManager->GetNames().roles._adventurer]->_id));
	insertUser.In_CreatedDate(tstamp);


	GDBConnectionPool->Push(dbConn);

	if (!insertUser.Execute())
	{
		throw RegstrationException(ERRORNO::FAILURE);
	}

	GConsoleLogger->WriteStdOutWithTime(Color::BLUE, L"%ws: 가입 성공\n", v);
}

void BotRegsterService::ChangeMemberRole(const WCHAR* v, const dpp::snowflake& id)
{
	const DNC::Names names = GBotManager->GetNames();

	AddMemberRole(GBotManager->GetServer()->_id, id, GBotManager->GetServer()->_roles[names.roles._adventurer]->_id);
	GConsoleLogger->WriteStdOutWithTime(Color::BLUE, L"%ws: 역할 부여 성공\n", v);
}

void BotRegsterService::AddMemberRole(dpp::snowflake guildId, dpp::snowflake userId, dpp::snowflake roleId)
{
	dpp::cluster* bot = GBotManager->GetCluster();
	bot->guild_member_add_role(guildId, userId, roleId);
}

void BotRegsterService::ChangeMemberName(dpp::guild_member member, char* name)
{
	dpp::cluster* bot = GBotManager->GetCluster();
	member.set_nickname(name);
	bot->guild_edit_member(member);
}
