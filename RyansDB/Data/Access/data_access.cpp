#include "data_access.hpp"

inline google::protobuf::Timestamp *GetCurrentTimeStamp()
{
    // Get the current time
    auto now = std::chrono::system_clock::now();
    auto seconds = std::chrono::time_point_cast<std::chrono::seconds>(now);
    auto nanoseconds = std::chrono::duration_cast<std::chrono::nanoseconds>(now - seconds);

    // Create a timestamp object and set its fields
    google::protobuf::Timestamp *timestamp = new google::protobuf::Timestamp();
    timestamp->set_seconds(std::chrono::duration_cast<std::chrono::seconds>(now.time_since_epoch()).count());
    timestamp->set_nanos(nanoseconds.count());

    return timestamp;
}

DataAccess::DataAccess() {}

GetCustomerWithJoinInTransactionsResult DataAccess::GetCustomersWithJoinInTransactions(const GetCustomerWithJoinInTransactionsCommand command) const
{
    CustomerDto customer = m_contactRepository.Read(command.id);
    std::queue<TransactionDto> queue = m_transactionRepository.Read(command.id);

    GetCustomerWithJoinInTransactionsResult result;
    result.customer = customer;
    result.transactions = queue;

    return result;
}

CreditTransactionResult DataAccess::CreditTransaction(CreditTransactionCommand command) const
{
    CustomerDto customer = m_contactRepository.Read(command.id);
    customer.set_balance(customer.balance() + command.balance);
    m_contactRepository.Save(command.id, customer);

    AddTransaction(command.id, command.description, true, command.balance);

    CreditTransactionResult result;
    result.customer = customer;

    return result;
}

DebtTransactionResult DataAccess::DebtTransaction(DebtTransactionCommand command) const
{
    DebtTransactionResult result;

    CustomerDto customer = m_contactRepository.Read(command.id);
    int finalBalance = customer.balance() - command.balance;
    if (finalBalance < -customer.limit())
    {
        result.success = false;
        return result;
    }

    customer.set_balance(finalBalance);
    m_contactRepository.Save(command.id, customer);

    AddTransaction(command.id, command.description, false, command.balance);

    result.customer = customer;
    result.success = true;

    return result;
}

void DataAccess::AddTransaction(const std::string contactId, const std::string &description, const bool isCredit, const int &value) const
{
    TransactionDto newTransaction = TransactionDto();
    newTransaction.set_description(description);
    newTransaction.set_iscredit(isCredit);
    newTransaction.set_value(value);
    newTransaction.set_allocated_createdate(GetCurrentTimeStamp());

    std::queue<TransactionDto> transactions = m_transactionRepository.Read(contactId);
    transactions.push(newTransaction);
    while (transactions.size() > 10)
        transactions.pop();

    m_transactionRepository.Save(contactId, transactions);
}
