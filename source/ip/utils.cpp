#include "utils.hpp"

#include <limits>

namespace ip
{

std::vector<IPv4> ReadFirstIpFromLines(std::istream& input)
{
    std::vector<IPv4> ip_addresses;

    while (!input.eof())
    {
        IPv4 ip;
        input >> ip;

        if (input.fail())
        {
            input.clear();
            input.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }

        ip_addresses.emplace_back(ip);
        input.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    return ip_addresses;
}

}  // namespace ip