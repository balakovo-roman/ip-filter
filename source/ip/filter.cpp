#include "filter.hpp"

#include <algorithm>

namespace ip
{

Filter::Filter(const std::vector<IPv4>& ips) : ips_(ips) {}

std::vector<IPv4> Filter::FilterByMask(
    const std::array<std::optional<uint8_t>, 4>& mask) const
{
    return FilterImpl([&mask](const IPv4& ip) { return ip.Matches(mask); });
}

std::vector<IPv4> Filter::FilterByOctetValue(uint8_t octet_value) const
{
    return FilterImpl([octet_value](const IPv4& ip) noexcept
                      { return ip.ContainsOctet(octet_value); });
}

std::vector<IPv4> Filter::FilterImpl(const Predicate& predicate) const
{
    std::vector<IPv4> result;

    std::copy_if(ips_.begin(), ips_.end(), std::back_inserter(result),
                 predicate);

    return result;
}

}  // namespace ip
