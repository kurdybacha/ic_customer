#ifndef _JSON_CUSTOMER_SOURCE_H_
#define _JSON_CUSTOMER_SOURCE_H_

#include "customer_source.h"
#include <fstream>

namespace ic {

class JsonCustomerSource : public CustomerSource
{
public:
    JsonCustomerSource(const std::string &filename);
    std::pair<bool, Customer> next_customer();
    bool available() const;

private:
    std::ifstream ifstream_;
};

} // namespace ic


#endif /* ifndef _JSON_CUSTOMER_SOURCE_H_ */
