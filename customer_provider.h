#ifndef _IC_CUSTOMER_PROVIDER_
#define _IC_CUSTOMER_PROVIDER_

#include <vector>
#include <memory>
#include "customer.h"

namespace ic {

class CustomerFilter;
class CustomerSource;

class CustomerProvider
{
public:
    CustomerProvider();

    void set_source(CustomerSource *source);
    void set_filter(CustomerFilter *filter);

    std::vector<Customer> customer_list();
private:
    CustomerProvider(const CustomerProvider &other) = delete;
    void operator=(const CustomerProvider &other) = delete;

    std::unique_ptr<CustomerFilter> filter_;
    std::unique_ptr<CustomerSource> source_;
};


} // namespace ic


#endif /* ifndef _IC_CUSTOMER_PROVIDER_ */
