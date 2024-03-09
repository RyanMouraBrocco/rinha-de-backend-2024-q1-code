// C++ libraries
#include <iostream>
#include "Socket/socket.hpp"
#include "Connections/connection.hpp"
#include "Dto/Customer/customer_dto.pb.h"
#include "Dto/Transaction/transaction_dto.pb.h"
#include "Data/customer_data.hpp"
#include "Data/transaction_data.hpp"
#include "Commands/commands.hpp"
#include "Results/resutls.hpp"

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
    std::string notFoundMessage = "NotFound";
    std::string invalidOperationMessage = "InvalidOp";
    while (true)
    {
        std::string text = connection.ReceiveBytes(4096);

        if (connection.GetStatus() != ConnectionStatus::Connected)
            break;

        MessageCommand message = MessageCommand::DeserializeJson(text);

        if (message.endpoint == "GetCustomersWithJoinInTransactions")
        {
            GetCustomerWithJoinInTransactionsCommand getObject = GetCustomerWithJoinInTransactionsCommand::DeserializeJson(message.data);
            CustomerDataAccess customerDataAcces = CustomerDataAccess();
            CustomerDto customer = customerDataAcces.Read(getObject.id);

            TransactionDataAccess transactionDataAccess = TransactionDataAccess();
            std::queue<TransactionDto> queue = transactionDataAccess.Read(getObject.id);

            connection.SendBytes(notFoundMessage.data(), 9);

            GetCustomerWithJoinInTransactionsResult result;
            result.customer = &customer;
            result.transactions = &queue;

            std::string jsonResult = result.SerializeJson();
            char *resultInCharArray = jsonResult.data();
            connection.SendBytes(resultInCharArray, sizeof(char) * jsonResult.length());
        }
        else if (message.endpoint == "CreditTransaction")
        {
            CreditTransactionCommand creditTransaction = CreditTransactionCommand::DeserializeJson(message.data);
            CustomerDataAccess customerDataAcces = CustomerDataAccess();
            TransactionDataAccess transactionDataAccess = TransactionDataAccess();

            CustomerDto customer = customerDataAcces.Read(creditTransaction.id);
            customer.set_balance(customer.balance() + creditTransaction.balance);
            customerDataAcces.Save(creditTransaction.id, customer);

            TransactionDto newTransaction = TransactionDto();
            newTransaction.set_description(creditTransaction.description);
            newTransaction.set_iscredit(true);
            newTransaction.set_value(creditTransaction.balance);
            // Get the current time
            auto now = std::chrono::system_clock::now();
            auto seconds = std::chrono::time_point_cast<std::chrono::seconds>(now);
            auto nanoseconds = std::chrono::duration_cast<std::chrono::nanoseconds>(now - seconds);

            // Create a timestamp object and set its fields
            google::protobuf::Timestamp *timestamp = new google::protobuf::Timestamp();
            timestamp->set_seconds(std::chrono::duration_cast<std::chrono::seconds>(now.time_since_epoch()).count());
            timestamp->set_nanos(nanoseconds.count());

            // Set the timestamp field in the message
            newTransaction.set_allocated_createdate(timestamp);

            std::queue<TransactionDto> transactions = transactionDataAccess.Read(creditTransaction.id);
            transactions.push(newTransaction);
            while (transactions.size() > 10)
                transactions.pop();

            transactionDataAccess.Save(creditTransaction.id, transactions);

            CreditTransactionResult result;
            result.customer = &customer;

            std::string jsonResult = result.SerializeJson();
            char *resultInCharArray = jsonResult.data();
            connection.SendBytes(resultInCharArray, sizeof(char) * jsonResult.length());
        }
        else if (message.endpoint == "DebtTransaction")
        {
            DebtTransactionCommand debtTransaction = DebtTransactionCommand::DeserializeJson(message.data);
            CustomerDataAccess customerDataAcces = CustomerDataAccess();
            TransactionDataAccess transactionDataAccess = TransactionDataAccess();

            CustomerDto customer = customerDataAcces.Read(debtTransaction.id);
            int finalBalance = customer.balance() - debtTransaction.balance;
            if (finalBalance < -customer.limit())
            {
                connection.SendBytes(invalidOperationMessage.data(), 9);
            }
            else
            {
                customer.set_balance(finalBalance);
                customerDataAcces.Save(debtTransaction.id, customer);

                TransactionDto newTransaction = TransactionDto();
                newTransaction.set_description(debtTransaction.description);
                newTransaction.set_iscredit(false);
                newTransaction.set_value(debtTransaction.balance);
                // Get the current time
                auto now = std::chrono::system_clock::now();
                auto seconds = std::chrono::time_point_cast<std::chrono::seconds>(now);
                auto nanoseconds = std::chrono::duration_cast<std::chrono::nanoseconds>(now - seconds);

                // Create a timestamp object and set its fields
                google::protobuf::Timestamp *timestamp = new google::protobuf::Timestamp();
                timestamp->set_seconds(std::chrono::duration_cast<std::chrono::seconds>(now.time_since_epoch()).count());
                timestamp->set_nanos(nanoseconds.count());

                // Set the timestamp field in the message
                newTransaction.set_allocated_createdate(timestamp);

                std::queue<TransactionDto> transactions = transactionDataAccess.Read(debtTransaction.id);
                transactions.push(newTransaction);
                while (transactions.size() > 10)
                    transactions.pop();

                transactionDataAccess.Save(debtTransaction.id, transactions);
                DebtTransactionResult result;
                result.customer = &customer;

                std::string jsonResult = result.SerializeJson();
                char *resultInCharArray = jsonResult.data();
                connection.SendBytes(resultInCharArray, sizeof(char) * jsonResult.length());
            }
        }
        else
            connection.SendBytes(notFoundMessage.data(), 9);
    }

    return 0;
}