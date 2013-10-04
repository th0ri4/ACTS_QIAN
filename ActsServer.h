#if !defined(ACTSSERVER_H)
#define ACTSSERVER_H

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <boost/asio.hpp>
#include <boost/bind.hpp>

namespace acts
{

using boost::asio::ip::tcp;

extern class CSession;

class CServer
{
public:
    CServer(boost::asio::io_service &io_service, tcp::endpoint &endpoint);
    void Accept(CSession* new_session, const boost::system::error_code& error)
    void Run();
private:
    boost::asio::io_service &m_io_service;
    tcp::acceptor m_acceptor;
};


}

#endif
