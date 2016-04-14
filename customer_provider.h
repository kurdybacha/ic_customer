#ifndef _IC_CUSTOMER_PROVIDER_
#define _IC_CUSTOMER_PROVIDER_

#include <memory>
#include "customer.h"
#include <set>

namespace ic {

class CustomerFilter;
class CustomerSource;

using CompareCustomer = std::function<bool(const Customer &left, const Customer &righ)>;

class CustomerProvider
{
public:
    CustomerProvider();

    void set_source(CustomerSource *source);
    void set_filter(CustomerFilter *filter);

    std::set<Customer,CompareCustomer> customer_list(const CompareCustomer &compare);
private:
    CustomerProvider(const CustomerProvider &other) = delete;
    void operator=(const CustomerProvider &other) = delete;

    std::unique_ptr<CustomerFilter> filter_;
    std::unique_ptr<CustomerSource> source_;
};


} // namespace ic


#endif /* ifndef _IC_CUSTOMER_PROVIDER_ */
