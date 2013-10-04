#if !defined(PGSQLCONFIG_H)
#define PGSQLCONFIG_H

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <string>
#include <pqxx/pqxx>

namespace acts
{
namespace db
{

using std::string;

class CUserConfig
{
public:
    CUserConfig();
    ~CUserConfig();
    bool InitConfig();
    string GetFrontAddress();
    string GetBrokerId();
    string GetUserId();
    string GetPassword();
private:
    string m_frontaddr;
    string m_brokerid;
    string m_userid;
    string m_password;
    connection* m_conn;

};

}
}
#endif
