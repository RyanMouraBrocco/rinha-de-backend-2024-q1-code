#include "transaction_data.hpp"

TransactionDataAccess::TransactionDataAccess()
{
}

int TransactionDataAccess::Save(const std::string &contactId, std::queue<TransactionDto> &transactions) const
{
    std::string path = "./TransactionsData/" + contactId + "/";
    CreateFolderWithNotExists(path);

    TransactionListDto transactionsList;
    while (!transactions.empty())
    {
        const TransactionDto &transaction = transactions.front();
        transactions.pop();
        *transactionsList.add_transactions() = transaction;
    }

    std::ofstream output(path + "data.bin", std::ios::binary);
    if (!transactionsList.SerializeToOstream(&output))
    {
        return -1;
    }

    return 0;
}

std::queue<TransactionDto> TransactionDataAccess::Read(const std::string &contactId) const
{
    std::string path = "./CustomersData/" + contactId + "/";
    CreateFolderWithNotExists(path);
    TransactionListDto transactions;
    std::queue<TransactionDto> result;

    std::ifstream input(path + "data.bin", std::ios::binary);
    if (!transactions.ParseFromIstream(&input))
    {
        return result; // i need to improve this return
    }

    for (const TransactionDto &transaction : transactions.transactions())
    {
        result.push(transaction);
    }

    return result;
}