// C++ libraries
#include <iostream>
#include <string>

// C libraries
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <string.h>

int CreateSocketListenerToIpv4()
{
    int socketListener = socket(AF_INET, SOCK_STREAM, 0);
    if (socketListener == -1)
    {
        std::cerr << "Error to create socket listener";
        return -1;
    }

    return socketListener;
}

int BindSocketListenerToPort(int socketListener, u_int16_t port)
{
    sockaddr_in hint;
    hint.sin_family = AF_INET;
    hint.sin_port = htons(port);
    inet_pton(AF_INET, "0.0.0.0", &hint.sin_addr);

    if (bind(socketListener, (sockaddr *)&hint, sizeof(hint)) == -1)
    {
        std::cerr << "Can't bind to IP/port";
        return -2;
    }

    return 1;
}

int main()
{
    int socketListener = CreateSocketListenerToIpv4();
    if (socketListener < 0)
        return socketListener;

    int bindResult = BindSocketListenerToPort(socketListener, 55000);
    if (bindResult < 0)
        return bindResult;

    // Mark the socket for listen
    if (listen(socketListener, SOMAXCONN) == -1)
    {
        std::cerr << "Can't listen";
        return -3;
    }

    // Close the listening socket
    close(socketListener);

    // While receiving display message, echo message
    char buf[4096];
    while (true)
    {
        
    }

    std::cout << "hello world" << std::endl;
    return 0;
}