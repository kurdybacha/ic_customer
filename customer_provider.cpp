#include "customer_provider.h"
#include "customer_source.h"
#include "customer_filter.h"
#include <algorithm>

namespace ic {


CustomerProvider::CustomerProvider()
    : filter_(nullptr)
    , source_(nullptr)
{}

void CustomerProvider::set_source(CustomerSource *source)
{
    source_.reset(source);
}

void CustomerProvider::set_filter(CustomerFilter *filter)
{
    filter_.reset(filter);
}


std::set<Customer, CompareCustomer> CustomerProvider::customer_list(const CompareCustomer &compare_method)
{
    std::set<Customer,CompareCustomer> customers(compare_method);

    if (!source_ || !filter_)
        return customers;

    ic::Customer customer;
    bool op_result = true;
    
    while (source_->available()) {
        std::tie(op_result, customer) = source_->next_customer();
        if (op_result && filter_->accept(customer))
            customers.insert(customer);
    }

    return customers;
}

} // namespace ic
