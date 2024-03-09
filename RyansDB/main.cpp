// C++ libraries
#include <iostream>
#include "Socket/socket.hpp"
#include "Connections/connection.hpp"
#include "Data/Customer/customer_data.pb.h"
#include "Data/Transaction/transaction_data.pb.h"

int main()
{
    CustomerData data;
    TransactionData teste;

    Socket socket = Socket(5001);
    socket.Listen();
    if (socket.GetStatus() != SocketStatus::Opened)
    {
        return -1;
    }

    Connection connection = Connection(socket);
    connection.AcceptForNewAccess();

    char buf[4096];
    while (true)
    {
        std::string text = connection.ReceiveBytes(4096);

        if (connection.GetStatus() != ConnectionStatus::Connected)
            break;

        std::cout << "Receive data: " << text << std::endl;

        connection.SendBytes(text.data(), sizeof(text) + 1);
    }

    return 0;
}