#pragma once

#include "../Repositories/customer_repository.hpp"
#include "../Repositories/transaction_repository.hpp"
#include "../../Results/resutls.hpp"
#include "../../Commands/commands.hpp"

class DataAccess
{
private:
    CustomerRepository m_contactRepository = CustomerRepository();
    TransactionRepository m_transactionRepository = TransactionRepository();

    void AddTransaction(const std::string contactId, const std::string &description, const bool isCredit, const int &value) const;

public:
    DataAccess();
    GetCustomerWithJoinInTransactionsResult GetCustomersWithJoinInTransactions(GetCustomerWithJoinInTransactionsCommand command) const;
    CreditTransactionResult CreditTransaction(CreditTransactionCommand command) const;
    DebtTransactionResult DebtTransaction(DebtTransactionCommand command) const;
};