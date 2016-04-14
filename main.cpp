#include <iomanip>
#include <iostream>
#include "customer.h"
#include "json_customer_source.h"
#include "customer_filter.h"
#include "customer_provider.h"

int main(int argc, char *argv[])
{
    ic::GeoCoordinate dublin_coordinate(53.3381985, -6.2592576);

    ic::CustomerProvider provider;
    provider.set_source(new ic::JsonCustomerSource("gistfile1.txt"));
    provider.set_filter(new ic::CustomerWithinDistanceFilter(dublin_coordinate, 100.0));
    //auto compare_method = [](const ic::Customer &left, const ic::Customer &right) { return left.id() < right.id(); };
    //auto customers = provider.customer_list(compare_method);
    auto customers = provider.customer_list();

    std::cout  << "CUSTOMER LIST" << std::endl;
    for (const auto &customer : customers)
        std::cout << std::setw(8) << customer.id() << customer.name() << std::endl;

    return 0;
}
