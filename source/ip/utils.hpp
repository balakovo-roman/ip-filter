#pragma once

#include <istream>
#include <ostream>

#include "ipv4.hpp"

namespace ip
{

class Reader final
{
   public:
    explicit Reader(std::istream& is);

    IpList ReadFirstIpFromLines();

   private:
    std::istream& input_;
};

class Printer final
{
   public:
    explicit Printer(std::ostream& os);

    void Print(const IpList& ip_list);

   private:
    std::ostream& output_;
};

void SortReverseLexicographical(IpList& ip_list);

}  // namespace ip