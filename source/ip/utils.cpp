#include "utils.hpp"

#include <algorithm>
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

Printer::Printer(std::ostream& os) : os_{os} {}

void Printer::Print(const std::vector<IPv4>& ip_list)
{
    for (const auto& ip : ip_list)
    {
        os_ << ip << std::endl;
    }
}

void SortReverseLexicographical(std::vector<IPv4>& ip_list)
{
    std::sort(ip_list.begin(), ip_list.end(), std::greater<IPv4>());
}

}  // namespace ip