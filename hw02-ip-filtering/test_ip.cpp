#include <gtest/gtest.h>

#include <vector>

#include "ip.h"

TEST(ParseIp, ParsesValidAddress) { EXPECT_EQ(ParseIp("1.2.3.4"), (IpAddress{1, 2, 3, 4})); }

TEST(ParseIp, ParsesBoundaryValues) {
    EXPECT_EQ(ParseIp("0.0.0.0"), (IpAddress{0, 0, 0, 0}));
    EXPECT_EQ(ParseIp("255.255.255.255"), (IpAddress{255, 255, 255, 255}));
}

TEST(ParseIp, RejectsInvalidAddresses) {
    for (const char* input : {"", "256.1.1.1", "1.2.3", "1.2.3.4.5", "1..2.3", ".1.2.3", "1.2.3.4.",
                              "a.b.c.d", "1.2.3.4x", "-1.2.3.4"}) {
        EXPECT_FALSE(ParseIp(input)) << "input: \"" << input << '"';
    }
}

TEST(SortIpPoolDescending, ComparesBytesNumerically) {
    std::vector<IpAddress> pool{{1, 1, 1, 1}, {1, 2, 1, 1}, {1, 10, 1, 1}};

    SortIpPoolDescending(pool);

    EXPECT_EQ(pool, (std::vector<IpAddress>{{1, 10, 1, 1}, {1, 2, 1, 1}, {1, 1, 1, 1}}));
}

TEST(FilterByFirstByte, MatchesFirstByteAndKeepsOrder) {
    std::vector<IpAddress> pool{{1, 9, 9, 9}, {2, 1, 1, 1}, {1, 1, 1, 1}};

    EXPECT_EQ(FilterByFirstByte(pool, 1), (std::vector<IpAddress>{{1, 9, 9, 9}, {1, 1, 1, 1}}));
}

TEST(FilterByFirstTwoBytes, RequiresBothBytes) {
    std::vector<IpAddress> pool{{46, 70, 1, 1}, {46, 71, 1, 1}, {47, 70, 1, 1}};

    EXPECT_EQ(FilterByFirstTwoBytes(pool, 46, 70), (std::vector<IpAddress>{{46, 70, 1, 1}}));
}

TEST(FilterByAnyByte, MatchesAnyPosition) {
    std::vector<IpAddress> pool{
        {46, 1, 1, 1}, {1, 46, 1, 1}, {1, 1, 46, 1}, {1, 1, 1, 46}, {1, 1, 1, 1}};

    EXPECT_EQ(FilterByAnyByte(pool, 46),
              (std::vector<IpAddress>{{46, 1, 1, 1}, {1, 46, 1, 1}, {1, 1, 46, 1}, {1, 1, 1, 46}}));
}
