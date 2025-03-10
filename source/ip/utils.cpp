#include "utils.hpp"

#include <algorithm>
#include <limits>

namespace ip
{

Reader::Reader(std::istream& is) : input_{is} {}

IpList Reader::ReadFirstIpFromLines()
{
    IpList ip_addresses;

    while (!input_.eof())
    {
        if (IPv4 ip; !(input_ >> ip))
        {
            input_.clear();
        }
        else
        {
            ip_addresses.emplace_back(ip);
        }

        input_.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    return ip_addresses;
}

Printer::Printer(std::ostream& os) : output_{os} {}

void Printer::Print(const IpList& ip_list)
{
    for (const auto& ip : ip_list)
    {
        output_ << ip << std::endl;
    }
}

void SortReverseLexicographical(IpList& ip_list)
{
    std::sort(ip_list.begin(), ip_list.end(), std::greater<IPv4>());
}

}  // namespace ip