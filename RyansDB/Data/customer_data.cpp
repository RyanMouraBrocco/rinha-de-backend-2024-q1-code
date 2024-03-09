#include "../Dto/Customer/customer_dto.pb.h"
#include <fstream>
#include <string>

int SaveCustomer(std::string &id, CustomerDto &customer)
{
    std::string path = "CustomersData/" + id + "/data.bin";
    std::ofstream output(path, std::ios::binary);
    if (!customer.SerializeToOstream(&output))
    {
        return -1;
    }

    return 0;
}

CustomerDto ReadCustomer(std::string &id)
{
    std::string path = "CustomersData/" + id + "/data.bin";
    CustomerDto customer;
    std::ifstream input(path, std::ios::binary);
    if (!customer.ParseFromIstream(&input))
    {
        return customer; // i need to improve this return
    }

    return customer;
}