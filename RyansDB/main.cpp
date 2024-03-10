// C++ libraries
#include <iostream>
#include "Socket/socket.hpp"
#include "Connections/connection.hpp"
#include "Data/Access/data_access.hpp"
#include <thread>

void InsertAllCustomer()
{
    CustomerRepository customerDataAccess;
    std::vector<int> limits = {100000, 80000, 1000000, 10000000, 500000};

    CustomerDto customer;
    for (short i = 0; i < 5; i++)
    {
        customer.set_limit(limits[i]);
        customer.set_balance(0);
        customerDataAccess.Save(std::to_string((i + 1)), customer);
    }
}

void EndPointsListener(Connection *connection)
{
    connection->AcceptForNewAccess();

    char buf[4096];
    std::string notFoundMessage = "NotFound";
    std::string invalidOperationMessage = "InvalidOp";
    DataAccess *dataAccess = DataAccess::GetInstance();
    while (true)
    {
        std::string text = connection->ReceiveBytes(4096);

        if (connection->GetStatus() != ConnectionStatus::Connected)
            break;

        MessageCommand message = MessageCommand::DeserializeJson(text);

        if (message.endpoint == "GetCustomersWithJoinInTransactions")
        {
            GetCustomerWithJoinInTransactionsCommand command = GetCustomerWithJoinInTransactionsCommand::DeserializeJson(message.data);
            GetCustomerWithJoinInTransactionsResult result = dataAccess->GetCustomersWithJoinInTransactions(command);
            std::string jsonResult = result.SerializeJson();
            char *resultInCharArray = jsonResult.data();
            connection->SendBytes(resultInCharArray, sizeof(char) * jsonResult.length());
        }
        else if (message.endpoint == "CreditTransaction")
        {
            CreditTransactionCommand command = CreditTransactionCommand::DeserializeJson(message.data);
            CreditTransactionResult result = dataAccess->CreditTransaction(command);
            std::string jsonResult = result.SerializeJson();
            char *resultInCharArray = jsonResult.data();
            connection->SendBytes(resultInCharArray, sizeof(char) * jsonResult.length());
        }
        else if (message.endpoint == "DebtTransaction")
        {
            DebtTransactionCommand command = DebtTransactionCommand::DeserializeJson(message.data);
            DebtTransactionResult result = dataAccess->DebtTransaction(command);

            if (result.success)
            {
                std::string jsonResult = result.SerializeJson();
                char *resultInCharArray = jsonResult.data();
                connection->SendBytes(resultInCharArray, sizeof(char) * jsonResult.length());
            }
            else
                connection->SendBytes(invalidOperationMessage.data(), 9);
        }
        else
            connection->SendBytes(notFoundMessage.data(), 9);
    }
}

int main()
{
    InsertAllCustomer();
    Socket socket = Socket(5432);
    socket.Listen();
    if (socket.GetStatus() != SocketStatus::Opened)
    {
        return -1;
    }

    short connectionPool = 40;

    Connection **connections = new Connection *[connectionPool];
    std::thread **threads = new std::thread *[connectionPool];

    for (short i = 0; i < connectionPool; i++)
    {
        connections[i] = new Connection(socket);
        threads[i] = new std::thread(EndPointsListener, connections[i]);
    }

    for (short i = 0; i < connectionPool; i++)
    {
        threads[i]->join();
    }

    for (short i = 0; i < connectionPool; i++)
    {
        delete connections[i];
        delete threads[i];
    }

    delete[] connections;
    delete[] threads;

    return 0;
}