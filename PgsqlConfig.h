#if !defined(PGSQLCONFIG_H)
#define PGSQLCONFIG_H

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <string> 
#include <pqxx\pqxx>

using namespace std;
using namespace pqxx;

class CPgsqlConfig
{
public:
	CPgsqlConfig();
	~CPgsqlConfig();
	bool InitializeConfig();
	string GetFrontAddress();
	string GetBrokerId();
	string GetUserId();
	string GetPassword();
private:
	string m_strFrontAddr;
	string m_strBrokerId;
	string m_strUserId;
	string m_strPassword;
	connection* m_pgConn;
};

#endif