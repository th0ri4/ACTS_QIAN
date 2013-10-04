#include <cstring>
#include <string>
#include <boost/thread/thread.hpp>
#include <boost/thread/condition.hpp>
#include <boost/bind.hpp>
#include "ActsSession.h"

namespace acts
{

CSession::CSession(boost::asio::io_service& io_service):
    m_socket(io_service),
    m_tr(NULL),
    m_ts(NULL),
    m_tm(NULL),
    m_keep_running(true),
    m_lock(m_mutex),
    m_retry_count(0),
    m_max_retry_count(10)
{
    memset(m_msg, 0, sizeof(m_msg));
    m_stat = new CNologon(this);
}

CSession::~CSession()
{
    m_tr->join();
    m_ts->join();
    m_tm->join();

    m_socket.close();
    m_msgs_in.clear();
    m_msgs_out.clear();
}

tcp::socket& CSession::Socket()
{
    return m_socket;
}

void CSession::Start()
{
    m_tr = new boost::thread(boost::bind(&CSession::Thread_Recv, this));
    m_ts = new boost::thread(boost::bind(&CSession::Thread_Send, this));
    m_tm = new boost::thread(boost::bind(&CSession::Thread_Main, this));

}

void CSession::Thread_Recv()
{

    std::string delim = MSG_DELIMITER;
    boost::asio::async_read_until(m_socket,
	                              m_buf,
								  delim,
                                  boost::bind(&CSession::Read_Callback, this,
                                              boost::asio::placeholders::error,
                                              boost::asio::placeholders::bytes_transferred));										  
    //boost::this_thread::sleep_for(boost::chrono::milliseconds(1000));

}

void CSession::Thread_Send()
{
    while(true){
        if(m_msgs_out.size() == 0){
            boost::this_thread::sleep_for(boost::chrono::milliseconds(1000));
            continue;
        }
        boost::asio::async_write(m_socket,
                                 boost::asio::buffer(m_msgs_out.front().data(), m_msgs_out.front().length()),
                                 boost::bind(&CSession::Write_Callback, this,
                                             boost::asio::placeholders::error,
                                             boost::asio::placeholders::bytes_transferred));
    }
}

void CSession::Thread_Main()
{

    while(true){
        if(m_msgs_in.size() == 0){
            //boost::unique_lock<boost::mutex> lock(m_mutex_in);
            //m_cond_in.wait(lock);

            boost::this_thread::sleep_for(boost::chrono::milliseconds(1000));
            continue;
        }
        m_stat->Handle_Cmd(); 
    }
}

void CSession::Read_Callback(const boost::system::error_code& error, size_t bytes)
{
    if (!error) {
        //m_retry_count = 0;
        m_msgs_in.push_back(m_buf);
        //boost::lock_guard<boost::mutex> lock(m_mutex_in);
        //m_cond_in.notify_one();
		m_buf = new boost::asio::streambuf(2048);
        std::string delim = MSG_DELIMITER;
        boost::asio::async_read_until(m_socket,
	                                  m_buf,
	    							  delim,
                                      boost::bind(&CSession::Read_Callback, this,
                                                  boost::asio::placeholders::error,
                                                  boost::asio::placeholders::bytes_transferred));
    } else {
        CLog::Debug("[CSession] - socket read error!");
        //handle_error();
    }
}

void CSession::Write_Callback(const boost::system::error_code& error)
{
    if (!error) {
        m_retry_count = 0;
        m_msgs_out.pop_front();
    } else {
        CLog::Debug("[CSession] - socket write error!");
        handle_error();
    }
}

void CSession::Handle_Error()
{
    m_retry_count++;
    if(m_retry_count > 10) {
        m_tr.interrupt();
        m_ts.interrupt();
        m_tm.interrupt();
    }
}


namespace CSession
{


CState::CState(CSession* cs)
{
    m_session = cs;
}

CState::~CState()
{
}

void CState::Handle_Cmd()
{
    if (m_CSession->m_msgs_in.front().data().type != TYPE_LOGON)
    {
        return;
    }
    switch (m_CSession->m_msgs_in.front().data().type)
    {
        case MSG_LOGON:
             Handle_Logon();
             break;
		case MSG_LOGOUT:
             Handle_Logout();
             break;
        default:
             break;
    }
}


void CNologon::Handle_Logon()
{
    if ((g_userconfig.getuserid() == m_CSession->m_msgs_in.front().data().cmd.logon.user_id) && (g_userconfig.getpassword() == m_msgs_in.front().data().cmd.logon.password))
    {
        //delete m_CSession->m_stat;
        m_session->m_stat = new CSession::logon(this);
        
        message msg;
        msg.version = VERSION;
        msg.type    = MSG_LOGON_RESPONSE;
        sprintf(msg.cmd.logon_response.text, "OK");
        m_session->m_msgs_out.push_back(msg);
        m_session->m_msgs_in.pop_front();

        delete this;
    }
    else
    {
        m_session->m_msgs_in.pop_front();
        CLog::Debug("invalid logon request!");
    }
}


}


}

