#include "utils.hpp"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <sstream>

namespace
{

using ip::IPv4;
using ip::ReadFirstIpFromLines;

TEST(ReadFirstWordFromLinesTest, ShouldReadFirstWordFromLinesWithNewlines)
{
    // Arrange
    std::istringstream input(R"(
        192.168.1.1
        10.0.0.1
        255.255.255.255
    )");

    // Act
    const auto result = ReadFirstIpFromLines(input);

    // Assert
    EXPECT_THAT(result,
                ::testing::ElementsAre(IPv4(192, 168, 1, 1), IPv4(10, 0, 0, 1),
                                       IPv4(255, 255, 255, 255)));
}

TEST(ReadFirstWordFromLinesTest, ShouldReadFirstWordFromLinesWithExtraData)
{
    // Arrange
    std::istringstream input(R"(
        192.168.1.1foo bar
        10.0.0.1test
        255.255.255.255
    )");

    // Act
    const auto result = ReadFirstIpFromLines(input);

    // Assert
    EXPECT_THAT(result,
                ::testing::ElementsAre(IPv4(192, 168, 1, 1), IPv4(10, 0, 0, 1),
                                       IPv4(255, 255, 255, 255)));
}

TEST(ReadFirstWordFromLinesTest, ShouldSkipInvalidLines)
{
    // Arrange
    std::istringstream input(R"(
        1.2.3.
        10.20.30.40
        256.256.256.256
    )");

    // Act
    const auto result = ReadFirstIpFromLines(input);

    // Assert
    EXPECT_THAT(result, ::testing::ElementsAre(IPv4(10, 20, 30, 40)));
}

TEST(ReadFirstWordFromLinesTest, ShouldHandleEmptyInput)
{
    // Arrange
    std::istringstream input("");

    // Act
    const auto result = ReadFirstIpFromLines(input);

    // Assert
    EXPECT_THAT(result, ::testing::IsEmpty());
}

TEST(ReadFirstWordFromLinesTest, ShouldReadFirstWordFromLinesWithTabs)
{
    // Arrange
    std::istringstream input(R"(
        192.168.1.1 text   text
        10.0.0.1	text    text
        255.255.255.255	text	text
    )");

    // Act
    const auto result = ReadFirstIpFromLines(input);

    // Assert
    EXPECT_THAT(result,
                ::testing::ElementsAre(IPv4(192, 168, 1, 1), IPv4(10, 0, 0, 1),
                                       IPv4(255, 255, 255, 255)));
}

class PrinterTest : public ::testing::Test
{
   protected:
    void Print(const std::vector<IPv4>& ip_list) { printer.Print(ip_list); }

    std::ostringstream oss;
    ip::Printer printer{oss};
};

TEST_F(PrinterTest, ShouldPrintIpListWhenListIsNotEmpty)
{
    // Act
    Print({IPv4(192, 168, 1, 1), IPv4(10, 0, 0, 1), IPv4(192, 16, 0, 1)});

    // Assert
    EXPECT_EQ(oss.str(),
              "192.168.1.1\n"
              "10.0.0.1\n"
              "192.16.0.1\n");
}

TEST_F(PrinterTest, ShouldPrintNothingWhenListIsEmpty)
{
    // Act
    Print({});

    // Assert
    EXPECT_TRUE(oss.str().empty());
}

}  // namespace