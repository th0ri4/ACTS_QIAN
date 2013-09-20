#include "PgsqlConfig.h"

using namespace std;

CPgsqlConfig::CPgsqlConfig():
	m_strFrontAddr(NULL),
	m_strBrokerId(NULL),
	m_strUserId(NULL),
	m_strPassword(NULL),
	m_pgConn(NULL)
{
}

CPgsqlConfig::~CPgsqlConfig()
{
	m_pgConn->disconnect();
	delete m_pgConn;
}

bool CPgsqlConfig::InitializeConfig()
{
	m_pgConn = new connection("dbname=acts user=postgres password=postgres");
	work txn(*m_pgConn);

	result r = txn.exec("SELECT * FROM user_config");
	
	if (r.size() != 1)
		return false;
	
	m_strFrontAddr = r[0][0];
	m_strBrokerId  = r[0][1];
	m_strUserId    = r[0][2];
	m_strPassword  = r[0][3];

	return true;
}

string CPgsqlConfig::GetFrontAddress()
{
	return m_strFrontAddr;
}

string CPgsqlConfig::GetBrokerId()
{
	return m_strBrokerId;
}

string CPgsqlConfig::GetUserId()
{
	return m_strUserId;
}

string CPgsqlConfig::GetPassword()
{
	return m_strPassword;
}