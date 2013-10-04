#include "DbUserConfig.h"

namespace acts
{
namespace db
{

using namespace std;

CUserConfig::CUserConfig():
    m_comm(NULL)
{
}

CUserConfig::~CUserConfig()
{
    m_comm->disconnect();
    delete m_comm;
    m_comm = NULL;
}

bool CUserConfig::InitConfig()
{
    m_conn = new connection("dbname=acts user=postgres");
    work txn(*m_conn);

    result r = txn.exec("SELECT * FROM user_config");

    if (r.size() != 1)
        return false;

    m_frontaddr = r[0][0].as<string>();
    m_brokerid  = r[0][1].as<string>();
    m_userid    = r[0][2].as<string>();
    m_password  = r[0][3].as<string>();

    return true;
}

string CUserConfig::GetFrontAddress()
{
    return m_frontaddr;
}

string CUserConfig::GetBrokerId()
{
    return m_brokerid;
}

string CUserConfig::GetUserId()
{
    return m_userid;
}

string CUserConfig::GetPassword()
{
    return m_password;
}

}

}