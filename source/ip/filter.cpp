#include "filter.hpp"

#include <algorithm>

namespace ip
{

Filter::Filter(const IpList& ips) : ips_(ips) {}

IpList Filter::FilterByMask(
    const std::array<std::optional<uint8_t>, 4>& mask) const
{
    return FilterImpl([&mask](const IPv4& ip) { return ip.Matches(mask); });
}

IpList Filter::FilterByOctetValue(uint8_t octet_value) const
{
    return FilterImpl([octet_value](const IPv4& ip) noexcept
                      { return ip.ContainsOctet(octet_value); });
}

IpList Filter::FilterImpl(const Predicate& predicate) const
{
    IpList result;

    std::copy_if(ips_.begin(), ips_.end(), std::back_inserter(result),
                 predicate);

    return result;
}

}  // namespace ip
