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


std::vector<Customer> CustomerProvider::customer_list()
{
    //auto compare_method = [](const Customer &left, const Customer &right) { return left.id() < right.id(); };
    struct compare_method
    {
        bool operator()(const Customer &left, const Customer &right) const { return left.id() < right.id(); }
    };
    std::vector<Customer> customers;

    if (!source_ || !filter_)
        return customers;

    ic::Customer customer;
    bool op_result = true;
    
    while (source_->available()) {
        std::tie(op_result, customer) = source_->next_customer();
        if (op_result && filter_->accept(customer))
            customers.insert(std::upper_bound(std::begin(customers), std::end(customers), customer, compare_method()), customer);
    }

    return customers;
}

} // namespace ic
