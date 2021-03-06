#ifndef _IC_GEO_COORDINATE_
#define _IC_GEO_COORDINATE_

namespace ic {

/* Distance in meters */
class Distance
{
public:
    Distance(double meters) : meters_(meters) {}
    operator double() const { return  meters_; }
private:
    double meters_;
};

class GeoCoordinate
{
public:
    enum CoordinateFormat {
        Degrees
    };

    static bool is_valid_latitude(double latitude);
    static bool is_valid_longitude(double longitude);

    GeoCoordinate();
    GeoCoordinate(double latitude, double longitude);

    bool valid() const;

    void set_latitude(double latitude);
    double latitude() const;

    void set_longitude(double longitude);
    double longitude() const;

    Distance distance_to(const GeoCoordinate &other) const;

private:

    double latitude_;
    double longitude_;
};

} // namespace ic

#endif /* ifndef _IC_GEO_COORDINATE_ */
