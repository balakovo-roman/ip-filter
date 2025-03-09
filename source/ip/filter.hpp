#include <functional>
#include <vector>

#include "ipv4.hpp"

namespace ip
{

class Filter final
{
   public:
    using Predicate = std::function<bool(const IPv4&)>;

    explicit Filter(const std::vector<IPv4>& ips);

    std::vector<IPv4> FilterByMask(
        const std::array<std::optional<uint8_t>, 4>& mask) const;

    std::vector<IPv4> FilterByOctetValue(uint8_t octet_value) const;

   private:
    std::vector<IPv4> FilterImpl(const Predicate& predicate) const;

    const std::vector<IPv4>& ips_;
};

}  // namespace ip