#ifndef _IC_CUSTOMER_
#define _IC_CUSTOMER_

#include <string>

#include "geo_coordinate.h"

namespace ic {

class Customer
{
public:
    Customer() : id_(0) {}

    Customer(int id, const std::string &name, const GeoCoordinate &geocoordinate)
        : id_(id)
        , name_(name)
        , geocoordinate_(geocoordinate)
    {}

    int id() const { return id_; }
    std::string name() const { return name_; };
    const GeoCoordinate& geocoordinate() const {  return geocoordinate_; };



private:
    int id_;
    std::string name_;
    GeoCoordinate geocoordinate_;
};


} // namespace ic

#endif /* ifndef _IC_CUSTOMER_ */
