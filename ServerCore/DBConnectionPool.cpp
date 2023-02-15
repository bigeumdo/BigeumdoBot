#include "pch.h"
#include "DBConnectionPool.h"

DBConnectionPool::DBConnectionPool()
{
}

DBConnectionPool::~DBConnectionPool()
{
	Clear();
}

bool DBConnectionPool::Connect(int32 connectionCount, const WCHAR* connectionString)
{
	// WRITE_LOCK;

	if (SQLAllocHandle(SQL_HANDLE_ENV, nullptr, &_environment) != SQL_SUCCESS)
		return false;

	if (SQLSetEnvAttr(_environment, SQL_ATTR_ODBC_VERSION, reinterpret_cast<SQLPOINTER>(SQL_OV_ODBC3), 0) !=
		SQL_SUCCESS)
		return false;

	for (int32 i = 0; i < connectionCount; i++)
	{
		auto connection = new DBConnection();
		if (connection->Connect(_environment, connectionString) == false)
			return false;

		_connections.push_back(connection);
	}
	GConsoleLogger->WriteStdOutWithTime(Color::BLUE, L"[DB] DB ���� ����.\n", connectionString);
	return true;
}

void DBConnectionPool::Clear()
{
	// WRITE_LOCK;

	if (_environment != nullptr)
	{
		SQLFreeHandle(SQL_HANDLE_ENV, _environment);
		_environment = nullptr;
	}

	for (DBConnection* connection : _connections)
		delete connection;
}

DBConnection* DBConnectionPool::Pop()
{
	// WRITE_LOCK;

	if (_connections.empty())
		return nullptr;

	DBConnection* connection = _connections.back();
	_connections.pop_back();
	return connection;
}

void DBConnectionPool::Push(DBConnection* connection)
{
	// WRITE_LOCK;

	_connections.push_back(connection);
}
