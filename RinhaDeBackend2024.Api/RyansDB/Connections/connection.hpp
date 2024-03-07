#pragma once

#include <netdb.h>
#include <unistd.h>

enum class ConnectionStatus
{
    Closed,
    Connected,
    Fail
};

class Connection
{
private:
    int &m_socketListener;
    sockaddr_in m_client;
    socklen_t m_clientSize = sizeof(m_client);
    int m_clientSocket;
    ConnectionStatus m_status = ConnectionStatus::Closed;

public:
    Connection(int &socketListener);
    ~Connection();
    void AcceptForNewAccess();
    ConnectionStatus GetStatus() const;
    int ReceiveBytes(char *buffer, const int &size) const;
    int SendBytes(char *buffer, const int &size) const;
};
