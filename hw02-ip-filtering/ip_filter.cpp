#include <algorithm>
#include <array>
#include <cstdint>
#include <functional>
#include <iostream>
#include <optional>
#include <string>
#include <string_view>
#include <vector>

using IpAddress = std::array<uint8_t, 4>;

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

        if (pos == str.size() || str[pos++] != '.') {
            return std::nullopt;
        }
    }

    return std::nullopt;
}

int main() {
    std::vector<IpAddress> ip_pool;

    for (std::string line; std::getline(std::cin, line);) {
        std::string_view view = line;
        auto ip = ParseIp(view.substr(0, view.find('\t')));
        if (ip) {
            ip_pool.push_back(*ip);
        }
    }

    std::sort(ip_pool.begin(), ip_pool.end(), std::greater<IpAddress>());

    for (const auto& ip : ip_pool) {
        std::cout << ip << '\n';
    }

    // 222.173.235.246
    // 222.130.177.64
    // 222.82.198.61
    // ...
    // 1.70.44.170
    // 1.29.168.152
    // 1.1.234.8

    for (const auto& ip : ip_pool) {
        if (ip[0] == 1) {
            std::cout << ip << '\n';
        }
    }

    // 1.231.69.33
    // 1.87.203.225
    // 1.70.44.170
    // 1.29.168.152
    // 1.1.234.8

    for (const auto& ip : ip_pool) {
        if (ip[0] == 46 && ip[1] == 70) {
            std::cout << ip << '\n';
        }
    }

    // 46.70.225.39
    // 46.70.147.26
    // 46.70.113.73
    // 46.70.29.76

    for (const auto& ip : ip_pool) {
        if (ip[0] == 46 || ip[1] == 46 || ip[2] == 46 || ip[3] == 46) {
            std::cout << ip << '\n';
        }
    }

    // 186.204.34.46
    // 186.46.222.194
    // 185.46.87.231
    // 185.46.86.132
    // 185.46.86.131
    // 185.46.86.131
    // 185.46.86.22
    // 185.46.85.204
    // 185.46.85.78
    // 68.46.218.208
    // 46.251.197.23
    // 46.223.254.56
    // 46.223.254.56
    // 46.182.19.219
    // 46.161.63.66
    // 46.161.61.51
    // 46.161.60.92
    // 46.161.60.35
    // 46.161.58.202
    // 46.161.56.241
    // 46.161.56.203
    // 46.161.56.174
    // 46.161.56.106
    // 46.161.56.106
    // 46.101.163.119
    // 46.101.127.145
    // 46.70.225.39
    // 46.70.147.26
    // 46.70.113.73
    // 46.70.29.76
    // 46.55.46.98
    // 46.49.43.85
    // 39.46.86.85
    // 5.189.203.46

    return 0;
}
