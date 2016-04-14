#include "unit_test.h"
#include "geo_coordinate.h"

namespace {

class GeoCoordinateTest
{
public:

    void default_constructor_test() const;
    void lat_long_constructor_test() const;
    void copy_constructor_test() const;
    void latitude_test() const;
    void longitude_test() const;
    void distance_to_test() const;

};

void GeoCoordinateTest::default_constructor_test() const
{
    ic::GeoCoordinate c;
    COMPARE(c.valid(), false);
}

void GeoCoordinateTest::lat_long_constructor_test() const
{
    ic::GeoCoordinate c(0.0, 0.0);
    COMPARE(c.valid(), true);
    COMPARE(c.latitude(), 0.0);
    COMPARE(c.longitude(), 0.0);

    ic::GeoCoordinate c1(-1.0, -1.0);
    COMPARE(c1.valid(), true);
    COMPARE(c1.latitude(), -1.0);
    COMPARE(c1.longitude(), -1.0);

    ic::GeoCoordinate c2(1.0, -1.0);
    COMPARE(c2.valid(), true);
    COMPARE(c2.latitude(), 1.0);
    COMPARE(c2.longitude(), -1.0);

    ic::GeoCoordinate c3(-1.0, 1.0);
    COMPARE(c3.valid(), true);
    COMPARE(c3.latitude(), -1.0);
    COMPARE(c3.longitude(), 1.0);

    ic::GeoCoordinate c4(91.0, 181.0);
    COMPARE(c4.valid(), false);

    ic::GeoCoordinate c5(-91.0, -181.0);
    COMPARE(c5.valid(), false);

    ic::GeoCoordinate c6(91.0, -181.0);
    COMPARE(c6.valid(), false);

    ic::GeoCoordinate c7(-91.0, 181.0);
    COMPARE(c7.valid(), false);
}

void GeoCoordinateTest::copy_constructor_test() const
{
    ic::GeoCoordinate c(1.0, -1.0);
    ic::GeoCoordinate c2(c);
    COMPARE(c2.latitude(), 1.0);
    COMPARE(c2.longitude(), -1.0);
}

void GeoCoordinateTest::latitude_test() const
{
    ic::GeoCoordinate c;
    c.set_latitude(3.0);
    COMPARE(c.latitude(), 3.0);
}

void GeoCoordinateTest::longitude_test() const
{
    ic::GeoCoordinate c;
    c.set_longitude(3.0);
    COMPARE(c.longitude(), 3.0);
}

void GeoCoordinateTest::distance_to_test() const
{
    ic::GeoCoordinate north_pole_coordinate(90,0);
    ic::GeoCoordinate south_pole_coordinate(-90,0);
    ic::GeoCoordinate london_coordinate(51.500152, -0.126236);
    ic::GeoCoordinate new_your_coordinate(40.71453, -74.00713);
    COMPARE(ic::GeoCoordinate().distance_to(north_pole_coordinate), ic::Distance(0.0));
    COMPARE(london_coordinate.distance_to(ic::GeoCoordinate()), ic::Distance(0.0));
    COMPARE(north_pole_coordinate.distance_to(south_pole_coordinate), ic::Distance(20015109.4154876769));
    COMPARE(london_coordinate.distance_to(new_your_coordinate), ic::Distance(5570538.4987236410)); 
}


} // namespace tst_geo_coordinate

int main(int argc, char *argv[])
{
    GeoCoordinateTest geo_test;
    geo_test.default_constructor_test();
    geo_test.lat_long_constructor_test();
    geo_test.copy_constructor_test();
    geo_test.latitude_test();
    geo_test.longitude_test();
    geo_test.distance_to_test();
    
    return 0;
}

