#pragma once

#include <algorithm>
#include <array>
#include <cstdint>
#include <optional>
#include <ostream>
#include <string_view>
#include <vector>

using IpAddress = std::array<uint8_t, 4>;
std::ostream& operator<<(std::ostream& os, const IpAddress& ip);

std::optional<IpAddress> ParseIp(std::string_view str);

void SortIpPoolDescending(std::vector<IpAddress>& pool);

template <typename... Bytes>
std::vector<IpAddress> FilterByPrefix(const std::vector<IpAddress>& pool, Bytes... bytes) {
    static_assert(sizeof...(bytes) <= std::tuple_size_v<IpAddress>,
                  "Too many bytes specified for IP address filtering");
    const std::array<uint8_t, sizeof...(bytes)> prefix{static_cast<uint8_t>(bytes)...};

    std::vector<IpAddress> result;
    for (const auto& ip : pool) {
        if (std::equal(prefix.begin(), prefix.end(), ip.begin())) {
            result.push_back(ip);
        }
    }
    return result;
}

std::vector<IpAddress> FilterByAnyByte(const std::vector<IpAddress>& pool, uint8_t byte);
