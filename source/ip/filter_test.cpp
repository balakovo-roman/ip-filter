#include "filter.hpp"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "ipv4.hpp"

namespace
{

using ip::IpList;
using ip::IPv4;

class FilterTest : public ::testing::Test
{
   protected:
    void SetUpFilter(IpList&& list_of_ip)
    {
        ips = std::move(list_of_ip);
        filter = std::make_unique<ip::Filter>(ips);
    }

    IpList ips;
    std::unique_ptr<ip::Filter> filter;
};

TEST_F(FilterTest, ShouldReturnAllIpsWhenNoFilterIsApplied)
{
    // Arrange
    SetUpFilter({IPv4(192, 168, 1, 1), IPv4(10, 0, 0, 1), IPv4(182, 16, 0, 1)});

    // Act
    auto result = filter->FilterByMask({});

    // Assert
    EXPECT_THAT(result,
                ::testing::ElementsAre(IPv4(192, 168, 1, 1), IPv4(10, 0, 0, 1),
                                       IPv4(182, 16, 0, 1)));
}

TEST_F(FilterTest, ShouldReturnFilteredIpsWhenFirstOctetIsFiltered)
{
    // Arrange
    SetUpFilter({IPv4(192, 168, 1, 1), IPv4(10, 0, 0, 1), IPv4(182, 16, 0, 1)});

    // Act
    auto result = filter->FilterByMask({192});

    // Assert
    EXPECT_THAT(result, ::testing::ElementsAre(IPv4(192, 168, 1, 1)));
}

TEST_F(FilterTest, ShouldReturnEmptyVectorWhenNoIpsMatchTheFilter)
{
    // Arrange
    SetUpFilter({IPv4(192, 168, 1, 1), IPv4(10, 0, 0, 1), IPv4(182, 16, 0, 1)});

    // Act
    auto result = filter->FilterByMask({192, 168, 1, 2});

    // Assert
    EXPECT_THAT(result, ::testing::IsEmpty());
}

TEST_F(FilterTest, ShouldReturnFilteredIpsWhenSecondOctetIsFiltered)
{
    // Arrange
    SetUpFilter({IPv4(192, 168, 1, 1), IPv4(10, 0, 0, 1), IPv4(182, 16, 0, 1)});

    // Act
    auto result = filter->FilterByMask({std::nullopt, 16});

    // Assert
    EXPECT_THAT(result, ::testing::ElementsAre(IPv4(182, 16, 0, 1)));
}

TEST_F(FilterTest, ShouldReturnFilteredIpsWhenThirdAndFourthOctetsAreFiltered)
{
    // Arrange
    SetUpFilter({IPv4(192, 168, 1, 1), IPv4(10, 0, 0, 1), IPv4(182, 16, 0, 1)});

    // Act
    auto result = filter->FilterByMask({std::nullopt, {}, 0, 1});

    // Assert
    EXPECT_THAT(result,
                ::testing::ElementsAre(IPv4(10, 0, 0, 1), IPv4(182, 16, 0, 1)));
}

TEST_F(FilterTest, ShouldReturnFilteredIpsWhenAllOctetsAreFiltered)
{
    // Arrange
    SetUpFilter({IPv4(192, 168, 1, 1), IPv4(10, 0, 0, 1), IPv4(182, 16, 0, 1)});

    // Act
    auto result = filter->FilterByMask({192, 168, 1, 1});

    // Assert
    EXPECT_THAT(result, ::testing::ElementsAre(IPv4(192, 168, 1, 1)));
}

TEST_F(FilterTest, ShouldReturnFilteredIpsWhenOctetValueIsInFirstOctet)
{
    // Arrange
    SetUpFilter({IPv4(192, 168, 1, 1), IPv4(10, 0, 0, 1), IPv4(182, 16, 0, 1)});

    // Act
    auto result = filter->FilterByOctetValue(192);

    // Assert
    EXPECT_THAT(result, ::testing::ElementsAre(IPv4(192, 168, 1, 1)));
}

TEST_F(FilterTest, ShouldReturnFilteredIpsWhenOctetValueIsInSecondOctet)
{
    // Arrange
    SetUpFilter({IPv4(192, 168, 1, 1), IPv4(10, 0, 0, 1), IPv4(182, 16, 0, 1)});

    // Act
    auto result = filter->FilterByOctetValue(16);

    // Assert
    EXPECT_THAT(result, ::testing::ElementsAre(IPv4(182, 16, 0, 1)));
}

TEST_F(FilterTest, ShouldReturnFilteredIpsWhenOctetValueIsInThirdOctet)
{
    // Arrange
    SetUpFilter({IPv4(192, 168, 1, 1), IPv4(10, 0, 0, 1), IPv4(182, 16, 0, 1)});

    // Act
    auto result = filter->FilterByOctetValue(0);

    // Assert
    EXPECT_THAT(result,
                ::testing::ElementsAre(IPv4(10, 0, 0, 1), IPv4(182, 16, 0, 1)));
}

TEST_F(FilterTest, ShouldReturnFilteredIpsWhenOctetValueIsInFourthOctet)
{
    // Arrange
    SetUpFilter({IPv4(192, 168, 1, 1), IPv4(10, 0, 0, 1), IPv4(182, 16, 0, 1)});

    // Act
    auto result = filter->FilterByOctetValue(1);

    // Assert
    EXPECT_THAT(result,
                ::testing::ElementsAre(IPv4(192, 168, 1, 1), IPv4(10, 0, 0, 1),
                                       IPv4(182, 16, 0, 1)));
}

TEST_F(FilterTest, ShouldReturnEmptyVectorWhenOctetValueIsNotFound)
{
    // Arrange
    SetUpFilter({IPv4(192, 168, 1, 1), IPv4(10, 0, 0, 1), IPv4(182, 16, 0, 1)});

    // Act
    auto result = filter->FilterByOctetValue(255);

    // Assert
    EXPECT_THAT(result, ::testing::IsEmpty());
}

}  // namespace