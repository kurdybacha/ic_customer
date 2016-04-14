#include "unit_test.h"
#include "json_customer_source.h"

namespace {

class JsonCustomerSourceTest
{
public:
    void file_not_exists_test() const;
    void first_line_test() const;
    void read_all_customers_test() const;
    void read_after_end_of_file_test() const;
    void invalid_json_row_data_test() const;
};

void JsonCustomerSourceTest::file_not_exists_test() const
{
    ic::JsonCustomerSource json_source("not_exits.txt");
    COMPARE(json_source.available(), false);
    auto data = json_source.next_customer();
    COMPARE(data.first, false);
}

void JsonCustomerSourceTest::first_line_test() const
{
    ic::JsonCustomerSource json_source("gistfile1.txt");
    auto data = json_source.next_customer();
    COMPARE(data.first, true);
    COMPARE(data.second.id(), 12);
    COMPARE(data.second.geocoordinate().latitude(), 52.986375);
    COMPARE(data.second.geocoordinate().longitude(), -6.043701);
}

void JsonCustomerSourceTest::read_all_customers_test() const
{
    ic::JsonCustomerSource json_source("gistfile1.txt");

    std::vector<ic::Customer> customer_list;
    
    bool read = true;
    while (read) {
        auto data = json_source.next_customer();
        read = data.first;
        if (read) {
            customer_list.push_back(data.second);
        }
    }

    COMPARE(customer_list.size(), static_cast<std::size_t>(32));
    const ic::Customer &customer = customer_list[10];
    COMPARE(customer.id(), 9);
    COMPARE(customer.name(), std::string("Jack Dempsey"));
    COMPARE(customer.geocoordinate().latitude(), 52.2559432);
    COMPARE(customer.geocoordinate().longitude(), -7.1048927);
}

void JsonCustomerSourceTest::read_after_end_of_file_test() const
{
    ic::JsonCustomerSource json_source("gistfile1.txt");
    auto customer = std::make_pair(true, ic::Customer());
    while (customer.first)
        customer = json_source.next_customer();

    customer = json_source.next_customer();
    COMPARE(customer.first, false);
    COMPARE(customer.second.id(), 0);
}

void JsonCustomerSourceTest::invalid_json_row_data_test() const
{
    ic::JsonCustomerSource json_source("gistfile1_invalid_row.txt");

    auto customer = std::make_pair(true, ic::Customer());

    std::vector<ic::Customer> customer_list;
    while (json_source.available()) {
        customer = json_source.next_customer();
        if (customer.first)
            customer_list.push_back(customer.second);
    }

    customer = json_source.next_customer();
    COMPARE(customer_list.size(), static_cast<std::size_t>(2));
}

}

int main(int argc, char *argv[])
{
    JsonCustomerSourceTest tests;
    tests.file_not_exists_test();
    tests.first_line_test();
    tests.read_all_customers_test();
    tests.read_after_end_of_file_test();
    tests.invalid_json_row_data_test();
    
    return 0;
}

