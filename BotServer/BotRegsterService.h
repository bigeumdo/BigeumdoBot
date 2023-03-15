#pragma once

enum class ERRORNO : int8
{
	INVALID = 1,
	OVERLAP,
	FAILURE,
	ALREADY
};

class RegstrationException
{
public:
	explicit RegstrationException(ERRORNO err)
	{
		switch (err)
		{
		case ERRORNO::INVALID:
			_messageDiscord = u8"옳바르지 않은 형식입니다. 다시 시도해주세요.";
			_messageConsole = L"유효성 검사 통과 실패";
			_code = 1;
			break;
		case ERRORNO::OVERLAP:
			_messageDiscord = u8"이미 존재하는 닉네임입니다.";
			_messageConsole = L"중복 검사 통과 실패";
			_code = 2;
			break;
		case ERRORNO::FAILURE:
			_messageDiscord = u8"가입에 실패했습니다.";
			_messageConsole = L"DB 등록 실패";
			_code = 3;
			break;
		case ERRORNO::ALREADY:
			_messageDiscord = u8"가입 정보가 존재합니다. 기존 정보를 불러옵니다.";
			_messageConsole = L"가입 정보 존재";
			_code = 4;
			break;
		default:
			_messageDiscord = u8"예상하지 못한 오류입니다.";
			_messageConsole = L"예상하지 못한 오류 발생";
			_code = -1;
			break;
		}
	}

	const string GetMessageD() const noexcept
	{
		return _messageDiscord;
	}

	const wstring GetMessageC() const noexcept
	{
		return _messageConsole;
	}

	bool operator==(int err)
	{
		return this->_code == err;
	}

private:
	string _messageDiscord;
	wstring _messageConsole;
	int _code;
};


class BotRegsterService
{
public:
	BotRegsterService();
	~BotRegsterService();

	void ServiceInit(const dpp::ready_t& event);
	void ShowModal(const dpp::button_click_t& event);
	void Submit(const dpp::form_submit_t& event);

	void CheckAuth(const dpp::snowflake& id, dpp::guild_member member);
	void ValidateNickName(const WCHAR* v);
	void CheckNameOverlap(const WCHAR* v);
	void RegisterExcute(const WCHAR* v, int64 id);
	void ChangeMemberRole(const WCHAR* v, const dpp::snowflake& id);

	void AddMemberRole(dpp::snowflake guildId, dpp::snowflake userId, dpp::snowflake roleId);
	void ChangeMemberName(dpp::guild_member member, char* name);

public:
	const string _buttonId = "reg_button_v1.0";
	const string _inputId = "reg_input";
private:
	const dpp::snowflake _channelId;
};
