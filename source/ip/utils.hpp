#pragma once

#include <istream>
#include <vector>

#include "ipv4.hpp"

namespace ip
{

std::vector<IPv4> ReadFirstIpFromLines(std::istream& input);

}