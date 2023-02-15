#pragma once
#include "Types.h"
#include <Windows.h>
#include "DBBind.h"

namespace SP
{
	
    class CheckAuth : public DBBind<1,2>
    {
    public:
    	CheckAuth(DBConnection& conn) : DBBind(conn, L"{CALL dbo.spCheckAuth(?)}") { }
    	void In_DiscordId(int64& v) { BindParam(0, v); };
    	void In_DiscordId(int64&& v) { _discordId = std::move(v); BindParam(0, _discordId); };
    	template<int32 N> void Out_Name(OUT WCHAR(&v)[N]) { BindCol(0, v); };
    	void Out_Role(OUT int64& v) { BindCol(1, v); };

    private:
    	int64 _discordId = {};
    };

    class CheckNameOverlap : public DBBind<1,1>
    {
    public:
    	CheckNameOverlap(DBConnection& conn) : DBBind(conn, L"{CALL dbo.spCheckNameOverlap(?)}") { }
    	template<int32 N> void In_Name(WCHAR(&v)[N]) { BindParam(0, v); };
    	template<int32 N> void In_Name(const WCHAR(&v)[N]) { BindParam(0, v); };
    	void In_Name(WCHAR* v, int32 count) { BindParam(0, v, count); };
    	void In_Name(const WCHAR* v, int32 count) { BindParam(0, v, count); };
    	void Out_Id(OUT int32& v) { BindCol(0, v); };

    private:
    };

    class InsertUser : public DBBind<5,0>
    {
    public:
    	InsertUser(DBConnection& conn) : DBBind(conn, L"{CALL dbo.spInsertUser(?,?,?,?,?)}") { }
    	void In_DiscordId(int64& v) { BindParam(0, v); };
    	void In_DiscordId(int64&& v) { _discordId = std::move(v); BindParam(0, _discordId); };
    	template<int32 N> void In_Name(WCHAR(&v)[N]) { BindParam(1, v); };
    	template<int32 N> void In_Name(const WCHAR(&v)[N]) { BindParam(1, v); };
    	void In_Name(WCHAR* v, int32 count) { BindParam(1, v, count); };
    	void In_Name(const WCHAR* v, int32 count) { BindParam(1, v, count); };
    	void In_Role(int64& v) { BindParam(2, v); };
    	void In_Role(int64&& v) { _role = std::move(v); BindParam(2, _role); };
    	void In_Money(int32& v) { BindParam(3, v); };
    	void In_Money(int32&& v) { _money = std::move(v); BindParam(3, _money); };
    	void In_CreatedDate(TIMESTAMP_STRUCT& v) { BindParam(4, v); };
    	void In_CreatedDate(TIMESTAMP_STRUCT&& v) { _createdDate = std::move(v); BindParam(4, _createdDate); };

    private:
    	int64 _discordId = {};
    	int64 _role = {};
    	int32 _money = {};
    	TIMESTAMP_STRUCT _createdDate = {};
    };

    class InsertMoney : public DBBind<3,0>
    {
    public:
    	InsertMoney(DBConnection& conn) : DBBind(conn, L"{CALL dbo.spInsertMoney(?,?,?)}") { }
    	void In_Money(int32& v) { BindParam(0, v); };
    	void In_Money(int32&& v) { _money = std::move(v); BindParam(0, _money); };
    	template<int32 N> void In_Name(WCHAR(&v)[N]) { BindParam(1, v); };
    	template<int32 N> void In_Name(const WCHAR(&v)[N]) { BindParam(1, v); };
    	void In_Name(WCHAR* v, int32 count) { BindParam(1, v, count); };
    	void In_Name(const WCHAR* v, int32 count) { BindParam(1, v, count); };
    	void In_CreatedDate(TIMESTAMP_STRUCT& v) { BindParam(2, v); };
    	void In_CreatedDate(TIMESTAMP_STRUCT&& v) { _createdDate = std::move(v); BindParam(2, _createdDate); };

    private:
    	int32 _money = {};
    	TIMESTAMP_STRUCT _createdDate = {};
    };

    class GetMoney : public DBBind<1,4>
    {
    public:
    	GetMoney(DBConnection& conn) : DBBind(conn, L"{CALL dbo.spGetMoney(?)}") { }
    	void In_Money(int32& v) { BindParam(0, v); };
    	void In_Money(int32&& v) { _money = std::move(v); BindParam(0, _money); };
    	void Out_Id(OUT int32& v) { BindCol(0, v); };
    	void Out_Money(OUT int32& v) { BindCol(1, v); };
    	template<int32 N> void Out_Name(OUT WCHAR(&v)[N]) { BindCol(2, v); };
    	void Out_CreatedDate(OUT TIMESTAMP_STRUCT& v) { BindCol(3, v); };

    private:
    	int32 _money = {};
    };


     
};