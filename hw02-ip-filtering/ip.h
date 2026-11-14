#pragma once

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

std::vector<IpAddress> FilterByFirstByte(const std::vector<IpAddress>& pool, uint8_t first);
std::vector<IpAddress> FilterByFirstTwoBytes(const std::vector<IpAddress>& pool, uint8_t first,
                                             uint8_t second);
std::vector<IpAddress> FilterByAnyByte(const std::vector<IpAddress>& pool, uint8_t byte);
