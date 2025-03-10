#include "ipv4.hpp"

#include <algorithm>
#include <cctype>
#include <limits>
#include <sstream>

namespace ip
{

IPv4::IPv4(uint8_t first_octet, uint8_t second_octet, uint8_t third_octet,
           uint8_t fourth_octet) noexcept
    : octets_{first_octet, second_octet, third_octet, fourth_octet}
{
}

bool IPv4::operator==(const IPv4& other) const noexcept
{
    return octets_ == other.octets_;
}

bool IPv4::operator!=(const IPv4& other) const noexcept
{
    return !(*this == other);
}

bool IPv4::operator<(const IPv4& other) const noexcept
{
    return octets_ < other.octets_;
}

bool IPv4::operator>(const IPv4& other) const noexcept { return other < *this; }

bool IPv4::operator<=(const IPv4& other) const noexcept
{
    return !(*this > other);
}

bool IPv4::operator>=(const IPv4& other) const noexcept
{
    return !(*this < other);
}

IPv4::operator std::string() const
{
    std::ostringstream oss;
    oss << static_cast<int>(octets_[0]) << '.' << static_cast<int>(octets_[1])
        << '.' << static_cast<int>(octets_[2]) << '.'
        << static_cast<int>(octets_[3]);
    return oss.str();
}

bool IPv4::Matches(
    const std::array<std::optional<uint8_t>, 4>& mask) const noexcept
{
    for (size_t i = 0; i < 4; ++i)
    {
        if (mask[i].has_value() && octets_[i] != mask[i].value())
        {
            return false;
        }
    }

    return true;
}

bool IPv4::ContainsOctet(uint8_t octet_value) const noexcept
{
    return std::any_of(octets_.cbegin(), octets_.cend(),
                       [octet_value](uint8_t octet) noexcept
                       { return octet == octet_value; });
}

}  // namespace ip

std::ostream& operator<<(std::ostream& os, const ip::IPv4& ip)
{
    os << static_cast<std::string>(ip);

    return os;
}

std::istream& operator>>(std::istream& is, ip::IPv4& ip)
{
    std::array<int, 4> octets;

    for (uint8_t i = 0; i < 4; ++i)
    {
        if (!(is >> octets[i]) ||
            octets[i] < std::numeric_limits<uint8_t>::min() ||
            octets[i] > std::numeric_limits<uint8_t>::max())
        {
            is.setstate(std::ios_base::failbit);
            return is;
        }

        if (i < 3)
        {
            if (is.peek() != '.')
            {
                is.setstate(std::ios_base::failbit);
                return is;
            }

            is.ignore(1);

            if (const auto next_char = is.peek(); !std::isdigit(next_char))
            {
                is.setstate(std::ios_base::failbit);
                return is;
            }
        }
    }

    ip = ip::IPv4(octets[0], octets[1], octets[2], octets[3]);

    return is;
}
