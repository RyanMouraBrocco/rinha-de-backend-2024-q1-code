#pragma once

#include "../Dto/Transaction/transaction_dto.pb.h"
#include <fstream>
#include <string>
#include "file_manager_helper.hpp"

class TransactionDataAccess
{
public:
    TransactionDataAccess();
    int Save(const std::string &contactId, const TransactionListDto &transactions) const;
    TransactionListDto Read(const std::string &contactId) const;
};