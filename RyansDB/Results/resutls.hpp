#include "../nlohmann/json.hpp"
#include <string>
#include <queue>
#include "../Dto/Customer/customer_dto.pb.h"
#include "../Dto/Transaction/transaction_dto.pb.h"

struct GetCustomerWithJoinInTransactionsResult
{
    CustomerDto *customer;
    std::queue<TransactionDto> *transactions;

    std::string SerializeJson()
    {
        nlohmann::json resultJson;
        nlohmann::json customerJson;
        nlohmann::json transactionsListJson;

        customerJson["limit"] = customer->limit();
        customerJson["balance"] = customer->balance();

        while (!transactions->empty())
        {
            nlohmann::json transactionJson;
            TransactionDto &transaction = transactions->front();
            transactionJson["value"] = transaction.value();
            transactionJson["iscredit"] = transaction.iscredit();
            transactionJson["description"] = transaction.description();
            transactionJson["createdate"] = transaction.createdate().Utf8DebugString();

            transactionsListJson.push_back(transactionJson);

            transactions->pop();
        }

        customerJson["customer"] = customerJson;
        customerJson["transactions"] = transactionsListJson;
        return resultJson.dump();
    }
};

struct CreditTransactionResult
{
    CustomerDto *customer;

    std::string SerializeJson()
    {
        nlohmann::json customerJson;
        customerJson["limit"] = customer->limit();
        customerJson["balance"] = customer->balance();
        return customerJson.dump();
    }
};

struct DebtTransactionResult
{
    CustomerDto *customer;

    std::string SerializeJson()
    {
        nlohmann::json customerJson;
        customerJson["limit"] = customer->limit();
        customerJson["balance"] = customer->balance();
        return customerJson.dump();
    }
};