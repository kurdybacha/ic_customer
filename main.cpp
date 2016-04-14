#include <iomanip>
#include <iostream>
#include "customer.h"
#include "json_customer_source.h"
#include "customer_filter.h"
#include "customer_provider.h"

constexpr double operator"" _km (long double value) {
    return value * 1000.0;
}

int main(int argc, char *argv[])
{
    ic::GeoCoordinate dublin_coordinate(53.3381985, -6.2592576);

    ic::CustomerProvider provider;
    provider.set_source(new ic::JsonCustomerSource("gistfile1.txt"));
    provider.set_filter(new ic::CustomerWithinDistanceFilter(dublin_coordinate, 100.0_km));
    auto compare_method = [](const ic::Customer &left, const ic::Customer &right) { return left.id() < right.id(); };
    auto customers = provider.customer_list(compare_method);

    std::cout  << "CUSTOMER LIST" << std::endl;
    std::cout  << "-------------------------------------" << std::endl;
    std::cout << std::left << std::setw(8) << std::setfill(' ') << "ID" << "NAME" << std::endl;
    std::cout  << "-------------------------------------" << std::endl;
    for (const auto &customer : customers)
        std::cout << std::left << std::setw(8) << std::setfill(' ') << customer.id() << customer.name() << std::endl;

    return 0;
}
