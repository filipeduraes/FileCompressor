#pragma once
#include <string>
#include <vector>
#include <cstdint>

namespace StringUtils
{
    std::vector<std::string> Split(const std::string& original, char separator = ' ');
    std::string ConvertBytesToBitString(const std::vector<uint8_t>& bytes, uint64_t bitSize);
}
