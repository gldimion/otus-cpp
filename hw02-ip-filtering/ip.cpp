#include "ip.h"

#include <functional>

std::ostream& operator<<(std::ostream& os, const IpAddress& ip) {
    return os << static_cast<int>(ip[0]) << '.' << static_cast<int>(ip[1]) << '.'
              << static_cast<int>(ip[2]) << '.' << static_cast<int>(ip[3]);
}

std::optional<IpAddress> ParseIp(std::string_view str) {
    IpAddress ip{};
    size_t pos = 0;

    for (size_t i = 0; i < ip.size(); ++i) {
        int value = 0;
        size_t start = pos;

        while (pos < str.size() && str[pos] >= '0' && str[pos] <= '9') {
            value = value * 10 + str[pos++] - '0';

            if (value > 255) {
                return std::nullopt;
            }
        }

        if (pos == start) {
            return std::nullopt;
        }

        ip[i] = static_cast<uint8_t>(value);

        if (i == ip.size() - 1) {
            return pos == str.size() ? std::optional<IpAddress>{ip} : std::nullopt;
        }

        if (pos == str.size() || str[pos] != '.') {
            return std::nullopt;
        }
        ++pos;
    }

    return std::nullopt;
}

void SortIpPoolDescending(std::vector<IpAddress>& pool) {
    std::sort(pool.begin(), pool.end(), std::greater<>());
}

std::vector<IpAddress> FilterByAnyByte(const std::vector<IpAddress>& pool, uint8_t byte) {
    std::vector<IpAddress> result;
    for (const auto& ip : pool) {
        if (ip[0] == byte || ip[1] == byte || ip[2] == byte || ip[3] == byte) {
            result.push_back(ip);
        }
    }
    return result;
}
