#include "ipv4.hpp"

#include <gtest/gtest.h>

#include <sstream>
#include <string_view>

namespace
{

using namespace std::string_view_literals;
using namespace std::string_literals;

using ip::IPv4;

class IPv4ToStringTest
    : public ::testing::TestWithParam<std::tuple<IPv4, std::string_view>>
{
};

TEST_P(IPv4ToStringTest, ShouldConvertToStringWhenIPv4IsValid)
{
    // Arrange
    const auto& [ip, expected_string] = GetParam();

    // Act
    const auto result = static_cast<std::string>(ip);

    // Assert
    EXPECT_EQ(result, expected_string);
}

INSTANTIATE_TEST_SUITE_P(
    IPv4ToStringCases, IPv4ToStringTest,
    ::testing::Values(std::make_tuple(IPv4(0, 0, 0, 0), "0.0.0.0"sv),
                      std::make_tuple(IPv4(255, 255, 255, 255),
                                      "255.255.255.255"sv)));

TEST(IPv4ComparisonTest, ShouldBeEqualWhenOctetsAreSame)
{
    // Arrange
    IPv4 ip1(192, 168, 1, 1);
    IPv4 ip2(192, 168, 1, 1);

    // Act, Assert
    EXPECT_TRUE(ip1 == ip2);
}

TEST(IPv4ComparisonTest, ShouldNotBeEqualWhenOctetsAreDifferent)
{
    // Arrange
    IPv4 ip1(192, 168, 1, 1);
    IPv4 ip2(192, 168, 1, 2);

    // Act, Assert
    EXPECT_TRUE(ip1 != ip2);
}

TEST(IPv4ComparisonTest, ShouldBeLessWhenFirstOctetIsLess)
{
    // Arrange
    IPv4 ip1(192, 168, 1, 1);
    IPv4 ip2(193, 168, 1, 1);

    // Act, Assert
    EXPECT_TRUE(ip1 < ip2);
}

TEST(IPv4ComparisonTest, ShouldNotBeLessWhenFirstOctetIsGreater)
{
    // Arrange
    IPv4 ip1(193, 168, 1, 1);
    IPv4 ip2(192, 168, 1, 1);

    // Act, Assert
    EXPECT_FALSE(ip1 < ip2);
}

TEST(IPv4ComparisonTest, ShouldBeGreaterWhenFirstOctetIsGreater)
{
    // Arrange
    IPv4 ip1(193, 168, 1, 1);
    IPv4 ip2(192, 168, 1, 1);

    // Act, Assert
    EXPECT_TRUE(ip1 > ip2);
}

TEST(IPv4ComparisonTest, ShouldNotBeGreaterWhenFirstOctetIsLess)
{
    // Arrange
    IPv4 ip1(192, 168, 1, 1);
    IPv4 ip2(193, 168, 1, 1);

    // Act, Assert
    EXPECT_FALSE(ip1 > ip2);
}

TEST(IPv4ComparisonTest, ShouldBeLessOrEqualWhenFirstOctetIsLess)
{
    // Arrange
    IPv4 ip1(192, 168, 1, 1);
    IPv4 ip2(193, 168, 1, 1);

    // Act, Assert
    EXPECT_TRUE(ip1 <= ip2);
}

TEST(IPv4ComparisonTest, ShouldBeLessOrEqualWhenOctetsAreSame)
{
    // Arrange
    IPv4 ip1(192, 168, 1, 1);
    IPv4 ip2(192, 168, 1, 1);

    // Act, Assert
    EXPECT_TRUE(ip1 <= ip2);
}

TEST(IPv4ComparisonTest, ShouldNotBeLessOrEqualWhenFirstOctetIsGreater)
{
    // Arrange
    IPv4 ip1(193, 168, 1, 1);
    IPv4 ip2(192, 168, 1, 1);

    // Act, Assert
    EXPECT_FALSE(ip1 <= ip2);
}

TEST(IPv4ComparisonTest, ShouldBeGreaterOrEqualWhenFirstOctetIsGreater)
{
    // Arrange
    IPv4 ip1(193, 168, 1, 1);
    IPv4 ip2(192, 168, 1, 1);

    // Act, Assert
    EXPECT_TRUE(ip1 >= ip2);
}

TEST(IPv4ComparisonTest, ShouldBeGreaterOrEqualWhenOctetsAreSame)
{
    IPv4 ip1(192, 168, 1, 1);
    IPv4 ip2(192, 168, 1, 1);

    EXPECT_TRUE(ip1 >= ip2);
}

TEST(IPv4ComparisonTest, ShouldNotBeGreaterOrEqualWhenFirstOctetIsLess)
{
    // Arrange
    IPv4 ip1(192, 168, 1, 1);
    IPv4 ip2(193, 168, 1, 1);

    // Act, Assert
    EXPECT_FALSE(ip1 >= ip2);
}

class IPv4InputOperatorFailTest
    : public ::testing::TestWithParam<std::tuple<std::string_view, std::string>>
{
};

TEST_P(IPv4InputOperatorFailTest, ShouldSetFailBitWhenInputIsInvalid)
{
    // Arrange
    const auto& [description, input] = GetParam();

    IPv4 ip;
    std::istringstream iss{input};

    // Act
    iss >> ip;

    // Assert
    EXPECT_TRUE(iss.fail()) << "Test case: "sv << description;
}

INSTANTIATE_TEST_SUITE_P(
    IPv4InputOperatorFailCases, IPv4InputOperatorFailTest,
    ::testing::Values(
        std::make_tuple("Empty input"sv, std::string{}),
        std::make_tuple("Less than four octets"sv, "192.168.1"s),
        std::make_tuple("Octet greater than 255"sv, "192.168.256.1"s),
        std::make_tuple("Negative octet"sv, "192.168.-1.1"s),
        std::make_tuple("Missing dots"sv, "192.16811"s),
        std::make_tuple("Dots in wrong places"sv, "192.168.1."s),
        std::make_tuple("Non-numeric characters"sv, "192.168.a.1"s),
        std::make_tuple("Missing last octet"sv, "192.168."s),
        std::make_tuple("Missing first octet"sv, ".168.1.1"s),
        std::make_tuple("Extra spaces"sv, "192 .168.1.1"s)));

class IPv4InputOperatorSuccessTest
    : public ::testing::TestWithParam<std::tuple<std::string_view, std::string>>
{
};

TEST_P(IPv4InputOperatorSuccessTest, ShouldReadIPv4AddressWhenInputIsValid)
{
    // Arrange
    const auto& [description, input] = GetParam();

    IPv4 ip;
    std::istringstream iss(input);

    // Act
    iss >> ip;

    // Assert
    EXPECT_FALSE(iss.fail()) << "Test case: "sv << description;
}

INSTANTIATE_TEST_SUITE_P(
    IPv4InputOperatorSuccessCases, IPv4InputOperatorSuccessTest,
    ::testing::Values(
        std::make_tuple("Valid IPv4 address"sv, "192.168.1.1"s),
        std::make_tuple("Leading spaces"sv, " 192.168.1.1"s),
        std::make_tuple("Trailing spaces"sv, "192.168.1.1 "s),
        std::make_tuple("Data after last octet"sv, "192.168.1.1extra"s),
        std::make_tuple("Minimal IPv4 address"sv, "0.0.0.0"s),
        std::make_tuple("Maximal IPv4 address"sv, "255.255.255.255"s)));

class IPv4OutputOperatorTest
    : public ::testing::TestWithParam<std::tuple<IPv4, std::string>>
{
};

TEST_P(IPv4OutputOperatorTest, ShouldOutputCorrectFormatWhenIPv4IsValid)
{
    // Arrange
    const auto& [ip, expected_output] = GetParam();
    std::ostringstream oss;

    // Act
    oss << ip;

    // Assert
    EXPECT_EQ(oss.str(), expected_output);
}

INSTANTIATE_TEST_SUITE_P(
    IPv4OutputOperatorCases, IPv4OutputOperatorTest,
    ::testing::Values(std::make_tuple(IPv4(0, 0, 0, 0), "0.0.0.0"sv),
                      std::make_tuple(IPv4(255, 255, 255, 255),
                                      "255.255.255.255"sv)));

}  // namespace