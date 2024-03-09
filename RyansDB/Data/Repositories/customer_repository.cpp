#include "customer_repository.hpp"

CustomerRepository::CustomerRepository()
{
}

int CustomerRepository::Save(const std::string &id, const CustomerDto &customer) const
{
    std::string path = "./CustomersData/" + id + "/";
    CreateFolderWithNotExists(path);
    std::ofstream output(path + "data.bin", std::ios::binary);
    if (!customer.SerializeToOstream(&output))
    {
        return -1;
    }

    return 0;
}

CustomerDto CustomerRepository::Read(const std::string &id) const
{
    std::string path = "./CustomersData/" + id + "/";
    CreateFolderWithNotExists(path);
    CustomerDto customer;
    std::ifstream input(path + "data.bin", std::ios::binary);
    if (!customer.ParseFromIstream(&input))
    {
        return customer; // i need to improve this return
    }

    return customer;
}