// C++ libraries
#include <iostream>
#include "Socket/socket.hpp"
#include "Connections/connection.hpp"
#include "Dto/Customer/customer_dto.pb.h"
#include "Dto/Transaction/transaction_dto.pb.h"
#include "Data/customer_data.hpp"
#include "nlohmann/json.hpp"

struct Message
{
    std::string endpoint;
    std::string data;
};

Message DeserializeStringToMessage(const std::string &jsonString)
{
    nlohmann::json jsonObject = nlohmann::json::parse(jsonString);
    Message message;
    message.endpoint = jsonObject["e"];
    message.data = jsonObject["d"];
    return message;
}

int main()
{
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

        Message message = DeserializeStringToMessage(text);
        std::cout << "Message: " << message.endpoint << " with data: " << message.data << std::endl;

        connection.SendBytes(text.data(), sizeof(text) + 1);
    }

    return 0;
}