#ifndef _IC_CUSTOMER_SOURCE_H_
#define _IC_CUSTOMER_SOURCE_H_

#include "customer.h"

namespace ic {

class CustomerSource
{
public:
    virtual ~CustomerSource() = default;
    /* Returns next customer data*/
    virtual std::pair<bool, Customer> next_customer() = 0;
    /* Return true if there are still data to be read */
    virtual bool available() const = 0;
};

} // namespace ic

#endif /* ifndef _IC_CUSTOMER_SOURCE_H_ */
