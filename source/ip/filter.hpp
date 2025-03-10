#include <functional>

#include "ipv4.hpp"

namespace ip
{

class Filter final
{
   public:
    using Predicate = std::function<bool(const IPv4&)>;

    explicit Filter(const IpList& ips);

    IpList FilterByMask(
        const std::array<std::optional<uint8_t>, 4>& mask) const;

    IpList FilterByOctetValue(uint8_t octet_value) const;

   private:
    IpList FilterImpl(const Predicate& predicate) const;

    const IpList& ips_;
};

}  // namespace ip