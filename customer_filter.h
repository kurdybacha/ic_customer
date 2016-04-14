#ifndef _IC_CUSTOMER_FILTER_H_
#define _IC_CUSTOMER_FILTER_H_

#include "geo_coordinate.h"

namespace ic {

class Customer;

class CustomerFilter
{
public:
    virtual ~CustomerFilter() = default;
    virtual bool accept(const Customer &customer) const = 0;
};


class CustomerWithinDistanceFilter : public CustomerFilter
{
public:
    CustomerWithinDistanceFilter(const GeoCoordinate &from_geocoordinate, double within_distance)
        : from_geocoordinate_(from_geocoordinate)
        , within_distance_(within_distance)
    {}

    bool accept(const Customer &customer) const
    {
        return from_geocoordinate_.distance_to(customer.geocoordinate()) <= within_distance_;
    }

private:
    GeoCoordinate from_geocoordinate_;
    double within_distance_;

};

} // namespace ic


#endif /* ifndef _IC_CUSTOMER_FILTER_H_ */
