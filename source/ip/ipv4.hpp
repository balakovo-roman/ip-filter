#pragma once

#include <array>
#include <cstdint>
#include <istream>
#include <ostream>

namespace ip
{

class IPv4 final
{
   public:
    IPv4(uint8_t first_octet = 0, uint8_t second_octet = 0,
         uint8_t third_octet = 0, uint8_t fourth_octet = 0) noexcept;

    explicit operator std::string() const;

    bool operator==(const IPv4& other) const noexcept;
    bool operator!=(const IPv4& other) const noexcept;
    bool operator<(const IPv4& other) const noexcept;
    bool operator>(const IPv4& other) const noexcept;
    bool operator<=(const IPv4& other) const noexcept;
    bool operator>=(const IPv4& other) const noexcept;

   private:
    std::array<uint8_t, 4> octets_;
};

}  // namespace ip

std::ostream& operator<<(std::ostream& os, const ip::IPv4& ip);
std::istream& operator>>(std::istream& is, ip::IPv4& ip);
