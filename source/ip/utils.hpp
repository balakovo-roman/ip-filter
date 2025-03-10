#pragma once

#include <istream>
#include <ostream>
#include <vector>

#include "ipv4.hpp"

namespace ip
{

std::vector<IPv4> ReadFirstIpFromLines(std::istream& input);

class Printer final
{
   public:
    explicit Printer(std::ostream& os);

    void Print(const std::vector<IPv4>& ip_list);

   private:
    std::ostream& os_;
};

void SortReverseLexicographical(std::vector<IPv4>& ip_list);

}  // namespace ip