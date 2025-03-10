#include <iostream>

#include "ip/filter.hpp"
#include "ip/utils.hpp"

int main([[maybe_unused]] int arg, [[maybe_unused]] char** args)
{
    ip::Reader reader{std::cin};

    ip::Printer printer{std::cout};

    auto input_ips = reader.ReadFirstIpFromLines();

    ip::Filter filter{input_ips};

    ip::SortReverseLexicographical(input_ips);

    const auto filtered_by_one_octet = filter.FilterByMask({1});

    const auto filtered_by_two_octets = filter.FilterByMask({46, 70});

    const auto filtered_by_any_octet = filter.FilterByOctetValue(46);

    for (const auto& ips :
         std::array{input_ips, filtered_by_one_octet, filtered_by_two_octets,
                    filtered_by_any_octet})
    {
        printer.Print(ips);
    }
}