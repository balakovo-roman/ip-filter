#pragma once

#include <istream>
#include <ostream>
#include <vector>

#include "ipv4.hpp"

namespace ip
{

class Reader final
{
   public:
    explicit Reader(std::istream& is);

    std::vector<IPv4> ReadFirstIpFromLines();

   private:
    std::istream& input_;
};

class Printer final
{
   public:
    explicit Printer(std::ostream& os);

    void Print(const std::vector<IPv4>& ip_list);

   private:
    std::ostream& output_;
};

void SortReverseLexicographical(std::vector<IPv4>& ip_list);

}  // namespace ip