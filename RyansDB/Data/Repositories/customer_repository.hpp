#pragma once

#include "../../Dto/Customer/customer_dto.pb.h"
#include <fstream>
#include <string>
#include "file_manager_helper.hpp"

class CustomerRepository
{
public:
    CustomerRepository();
    int Save(const std::string &id, const CustomerDto &customer) const;
    CustomerDto Read(const std::string &id) const;
};