#if !defined(ACTSSESSION_H)
#define ACTSSESSION_H

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <deque>
#include <boost/asio.hpp>
#include <boost/thread/thread.hpp>
#include <boost/thread/condition.hpp>
#include "ActsMessage.h"

namespace acts
{

using boost::asio::ip::tcp;

class CSession
{
public:
    CSession(boost::asio::io_service& io_service);
    tcp::socket& Socket();
    void Read_Callback(const boost::system::error_code& error, size_t bytes);
    void Write_Callback(const boost::system::error_code& error);
    void Start();
    void Thread_Recv();
    void Thread_Send();
    void Thread_Main();
    void Handle_Error();
private:
    tcp::socket m_socket;
	boost::asio::streambuf* m_buf;
    message m_msg;
    std::deque<boost::asio::streambuf*> m_msgs_in;
    std::deque<boost::asio::streambuf*> m_msgs_out;
    boost::thread* m_tr;
    boost::thread* m_ts;
    boost::thread* m_tm;
    //boost::mutex m_mutex_in;
    //boost::mutex m_mutex_out;
    //boost::condition_variable m_cond_in;
    //boost::condition_variable m_cond_out;
    unsigned int m_max_retry_count;
    unsigned int m_retry_count;
    CState* m_stat;
};

namespace session
{


class CState
{
public:
    CState(CSession s);
    ~CState();
    virtual void Handle_Cmd();
protected:
    virtual void Handle_Logon();
    virtual void Handle_Logout();
public:
    CSession* m_session;
};

class CNologon : public CState
{
protected:
    virtual void Handle_Logon();
};

}


}
#endif
