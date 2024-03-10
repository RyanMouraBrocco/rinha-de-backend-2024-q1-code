#pragma once

#include "../Repositories/customer_repository.hpp"
#include "../Repositories/transaction_repository.hpp"
#include "../../Results/resutls.hpp"
#include "../../Commands/commands.hpp"
#include <mutex>
#include <map>

class DataAccess
{
private:
    std::map<std::string, std::mutex> m_contactsMutex;
    CustomerRepository m_contactRepository = CustomerRepository();
    TransactionRepository m_transactionRepository = TransactionRepository();
    void AddTransaction(const std::string contactId, const std::string &description, const bool isCredit, const int &value) const;
    DataAccess();

public:
    DataAccess(DataAccess const &) = delete;
    void operator=(DataAccess const &) = delete;
    static DataAccess *GetInstance();
    GetCustomerWithJoinInTransactionsResult GetCustomersWithJoinInTransactions(GetCustomerWithJoinInTransactionsCommand command) const;
    CreditTransactionResult CreditTransaction(CreditTransactionCommand command);
    DebtTransactionResult DebtTransaction(DebtTransactionCommand command);
};