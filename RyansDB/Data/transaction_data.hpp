#pragma once

#include "../Dto/Transaction/transaction_dto.pb.h"
#include <fstream>
#include <string>
#include "file_manager_helper.hpp"
#include <queue>

class TransactionDataAccess
{
public:
    TransactionDataAccess();
    int Save(const std::string &contactId, std::queue<TransactionDto> &transactions) const;
    std::queue<TransactionDto> Read(const std::string &contactId) const;
};