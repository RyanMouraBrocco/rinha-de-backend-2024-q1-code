#include "connection.hpp"

Connection::Connection(int &socketListener) : m_socketListener(socketListener) {}

Connection::~Connection()
{
    if (m_status != ConnectionStatus::Closed)
        close(m_clientSocket);
}

void Connection::AcceptForNewAccess()
{
    m_clientSocket = accept(m_socketListener, (sockaddr *)&m_client, &m_clientSize);
    if (m_clientSocket == -1)
        m_status = ConnectionStatus::Fail;
    else
        m_status = ConnectionStatus::Connected;
}

ConnectionStatus Connection::GetStatus() const
{
    return m_status;
}

int Connection::ReceiveBytes(char *buffer, const int &size) const
{
    
}