#include "utils.hpp"

#include <algorithm>
#include <limits>

namespace ip
{

Reader::Reader(std::istream& is) : input_{is} {}

std::vector<IPv4> Reader::ReadFirstIpFromLines()
{
    std::vector<IPv4> ip_addresses;

    while (!input_.eof())
    {
        IPv4 ip;
        input_ >> ip;

        if (input_.fail())
        {
            input_.clear();
            input_.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }

        ip_addresses.emplace_back(ip);
        input_.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    return ip_addresses;
}

Printer::Printer(std::ostream& os) : output_{os} {}

void Printer::Print(const std::vector<IPv4>& ip_list)
{
    for (const auto& ip : ip_list)
    {
        output_ << ip << std::endl;
    }
}

void SortReverseLexicographical(std::vector<IPv4>& ip_list)
{
    std::sort(ip_list.begin(), ip_list.end(), std::greater<IPv4>());
}

}  // namespace ip