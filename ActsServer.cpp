#include "ActsServer.h"

namespace acts
{

CServer::CServer(boost::asio::io_service &io_service, tcp::endpoint &endpoint):
    m_io_service(io_service),
    m_acceptor(io_service, endpoint)
{
    session* new_session = new session(m_io_service);
    m_acceptor.async_accept(new_session->Socket(),
                            boost::bind(&CServer::Accept,
                                        this,
                                        new_session,
                                        boost::asio::placeholders::error));
}

void CServer::Accept(CSession* new_session, const boost::system::error_code& error)
{
    if (error) {
        delete new_session;
        return;
    }
    new_session->start();
    new_session = new session(m_io_service);
    m_acceptor.async_accept(new_session->socket(),
                            boost::bind(&CServer::Accept,
                                        this,
                                        new_session,
                                        boost::asio::placeholders::error));
}

void CServer::Run()
{
    m_io_service.run();
}

}
