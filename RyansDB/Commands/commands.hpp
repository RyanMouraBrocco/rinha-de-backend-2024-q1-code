#pragma once

#include "../nlohmann/json.hpp"
#include <string>

struct MessageCommand
{
    std::string endpoint;
    std::string data;

    static MessageCommand DeserializeJson(const std::string &jsonString)
    {
        nlohmann::json jsonObject = nlohmann::json::parse(jsonString);
        MessageCommand message;
        message.endpoint = jsonObject["e"];
        message.data = jsonObject["d"];
        return message;
    }
};

struct GetCustomerWithJoinInTransactionsCommand
{
    std::string id;

    static GetCustomerWithJoinInTransactionsCommand DeserializeJson(const std::string &jsonString)
    {
        nlohmann::json jsonObject = nlohmann::json::parse(jsonString);
        GetCustomerWithJoinInTransactionsCommand result;
        result.id = jsonObject["id"];
        return result;
    }
};

struct CreateCustomerCommand
{
    std::string id;
    int limit;
    int balance;

    static CreateCustomerCommand DeserializeJson(const std::string &jsonString)
    {
        nlohmann::json jsonObject = nlohmann::json::parse(jsonString);
        CreateCustomerCommand result;
        result.id = jsonObject["id"];
        result.limit = jsonObject["limit"];
        result.balance = jsonObject["balance"];
        return result;
    }
};

struct CreditTransactionCommand
{
    std::string id;
    int balance;
    std::string description;

    static CreditTransactionCommand DeserializeJson(const std::string &jsonString)
    {
        nlohmann::json jsonObject = nlohmann::json::parse(jsonString);
        CreditTransactionCommand result;
        result.id = jsonObject["id"];
        result.balance = jsonObject["balance"];
        result.description = jsonObject["description"];
        return result;
    }
};

struct DebtTransactionCommand
{
    std::string id;
    int balance;
    std::string description;

    static DebtTransactionCommand DeserializeJson(const std::string &jsonString)
    {
        nlohmann::json jsonObject = nlohmann::json::parse(jsonString);
        DebtTransactionCommand result;
        result.id = jsonObject["id"];
        result.balance = jsonObject["balance"];
        result.description = jsonObject["description"];
        return result;
    }
};