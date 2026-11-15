#include <iostream>
#include <string>
#include <string_view>
#include <vector>

#include "ip.h"

void PrintIpPool(const std::vector<IpAddress>& pool) {
    for (const auto& ip : pool) {
        std::cout << ip << '\n';
    }
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

    SortIpPoolDescending(ip_pool);

    PrintIpPool(ip_pool);
    PrintIpPool(FilterByPrefix(ip_pool, 1));
    PrintIpPool(FilterByPrefix(ip_pool, 46, 70));
    PrintIpPool(FilterByAnyByte(ip_pool, 46));

    return 0;
}
