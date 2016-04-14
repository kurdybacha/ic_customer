#include "json_customer_source.h"
#include "gason.hpp"
#include <vector>
#include <iostream>
#include <string>

namespace ic {


JsonCustomerSource::JsonCustomerSource(const std::string &filename)
    : ifstream_(filename)
{
}

bool JsonCustomerSource::available() const
{
    return ifstream_.good() && !ifstream_.eof();
}

template<typename T>
T to_type_helper(const gason::JsonValue &value, bool &ok)
{
    assert(false);
}

template<>
int to_type_helper<int>(const gason::JsonValue &value, bool &ok)
{
    return value.toInt(&ok);
}

template<>
std::string to_type_helper<std::string>(const gason::JsonValue &value, bool &ok)
{
    return value.toString(&ok);
}

template<typename T>
T to_type(const gason::JsonValue &root, const char *child_key, const std::string &line)
{
    gason::JsonValue value = root.child(child_key);
    if (!value)
        throw std::invalid_argument(line + " (Missing key " + std::string(child_key) + ")");

    bool ok = false;
    T result = to_type_helper<T>(value, ok);
    if (!ok)
        throw std::invalid_argument(line + " (Cannot parse data of " + std::string(child_key) + ")");

    return result;
}

//simple JSON parser
std::pair<bool, Customer> JsonCustomerSource::next_customer()
{
    static std::pair<bool, Customer> invalid_customer{false, Customer()};

    if (!available())
        return invalid_customer;

    try {
        std::string line;
        if (std::getline(ifstream_, line)) {
            gason::JsonAllocator    allocator;
            gason::JsonValue        root;
            std::vector<char> buffer;
            std::copy(std::begin(line), std::end(line), std::back_inserter(buffer));
            buffer.push_back('\0');
            gason::JsonParseStatus status = gason::jsonParse(buffer.data(), root, allocator);

            if (status != gason::JSON_PARSE_OK)
                throw std::invalid_argument(line);

            int user_id = to_type<int>(root, "user_id", line);
            const std::string &user_name = to_type<std::string>(root, "name", line);
            const std::string latitude_string = to_type<std::string>(root, "latitude", line);
            double latitude = std::stod(latitude_string);
            const std::string longitude_string = to_type<std::string>(root, "longitude", line);
            double longitude = std::stod(longitude_string);

            return {true, Customer(user_id, user_name, GeoCoordinate(latitude, longitude))};

        }

    } catch (std::invalid_argument ex) {
        std::cout << "Warning: ignoring invalid json row data: " << ex.what() << std::endl;
    } 

    return invalid_customer;
}

} // namespace ic
