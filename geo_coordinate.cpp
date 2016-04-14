#include "geo_coordinate.h"
#include <cmath>
#include <limits>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

namespace ic {

static double NaN = std::numeric_limits<double>::quiet_NaN();

static const double geocoordinate_EARTH_RADIUS = 6371.0072;

inline static double geocoordinate_deg_to_rad(double deg)
{
    return deg * M_PI / 180;
}


//inline static double geocoordinate_rad_to_deg(double rad)
//{
//    return rad * 180 / M_PI;
//}

bool GeoCoordinate::is_valid_latitude(double latitude)
{
    return latitude >= -90 && latitude <= 90;
}

bool GeoCoordinate::is_valid_longitude(double longitude)
{
    return longitude >= -180 && longitude <= 180;
}

GeoCoordinate::GeoCoordinate()
    : latitude_(NaN)
    , longitude_(NaN)
{
}

GeoCoordinate::GeoCoordinate(double latitude, double longitude)
    : GeoCoordinate()
{
    if (is_valid_latitude(latitude) && is_valid_longitude(longitude)) {
        latitude_ = latitude;
        longitude_ = longitude;
    }
}

bool GeoCoordinate::valid() const
{
    return is_valid_latitude(latitude()) && is_valid_longitude(longitude());
}

void GeoCoordinate::set_latitude(double latitude)
{
    if (is_valid_latitude(latitude))
        latitude_ = latitude;
    else
        latitude_ = NaN;
}

double GeoCoordinate::latitude() const
{
    return latitude_;
}

void GeoCoordinate::set_longitude(double longitude)
{
    longitude_ = longitude;
}

double GeoCoordinate::longitude() const
{
    return longitude_;
}

/*
 * Returns distance (in meters) from this coordinate to the coordinate specified
 * by \a other argument.
 * This calculation return the great-circle distance between two coordinates,
 * with assumption that the Earth is spherical.
 *
 * Return 0 if one of the coordinate is invalid.
*/
Distance GeoCoordinate::distance_to(const GeoCoordinate &other) const
{
    if (!valid() || !other.valid())
        return 0;

    double lat = geocoordinate_deg_to_rad(other.latitude() - latitude());
    double lon = geocoordinate_deg_to_rad(other.longitude() - longitude());
    double haversine_lat = std::sin(lat / 2.0);
    haversine_lat *= haversine_lat;
    double haversine_lon = std::sin(lon / 2.0);
    haversine_lon *= haversine_lon;
    double y = haversine_lat + std::cos(geocoordinate_deg_to_rad(other.latitude())) * std::cos(geocoordinate_deg_to_rad(latitude())) * haversine_lon;
    double x = 2 * std::asin(std::sqrt(y));
    return x * geocoordinate_EARTH_RADIUS * 1000.0;
}

} // namespace ic
