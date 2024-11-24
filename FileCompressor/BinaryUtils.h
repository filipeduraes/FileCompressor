#pragma once
#include <cstdint>
#include <string>
#include <vector>

namespace BinaryUtils
{
    uint8_t ConvertBitSizeToByteSize(uint8_t bitSize);
    uint8_t GetByteFromTextAtIndex(const std::string& text, uint64_t index);
    std::vector<uint8_t> ConvertEncodedTextToBytes(const std::string& encodedText);
}
