#include "transaction_data.hpp"

TransactionDataAccess::TransactionDataAccess()
{
}

int TransactionDataAccess::Save(const std::string &contactId, const TransactionListDto &transactions) const
{
    std::string path = "./TransactionsData/" + contactId + "/";
    CreateFolderWithNotExists(path);
    std::ofstream output(path + "data.bin", std::ios::binary);
    if (!transactions.SerializeToOstream(&output))
    {
        return -1;
    }

    return 0;
}

TransactionListDto TransactionDataAccess::Read(const std::string &contactId) const
{
    std::string path = "./CustomersData/" + contactId + "/";
    CreateFolderWithNotExists(path);
    TransactionListDto transactions;
    std::ifstream input(path + "data.bin", std::ios::binary);
    if (!transactions.ParseFromIstream(&input))
    {
        return transactions; // i need to improve this return
    }

    return transactions;
}