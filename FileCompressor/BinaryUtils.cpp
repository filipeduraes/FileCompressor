#include <cmath>
#include "BinaryUtils.h"

uint8_t BinaryUtils::ConvertBitSizeToByteSize(const uint8_t bitSize)
{
    const uint8_t byteSize = static_cast<uint8_t>(std::ceil(bitSize / 8.0));
    return byteSize;
}

uint8_t BinaryUtils::GetByteFromTextAtIndex(const std::string& text, const uint64_t index)
{
    const uint64_t count = std::min(static_cast<uint64_t>(text.size() - index), static_cast<uint64_t>(8ull));
    std::string byteSizeText = text.substr(index, count);

    if(byteSizeText.size() < 8)
    {
        byteSizeText.append(8 - count, '0');
    }

    const uint8_t substringAsByte = static_cast<uint8_t>(strtol(byteSizeText.c_str(), nullptr, 2));
    return substringAsByte;
}

std::vector<uint8_t> BinaryUtils::ConvertEncodedTextToBytes(const std::string& encodedText)
{
    std::vector<uint8_t> result;
    
    for(uint64_t i = 0; i < encodedText.size(); i += 8)
    {
        uint8_t convertedText = GetByteFromTextAtIndex(encodedText, i);
        result.emplace_back(convertedText);
    }

    return result;
}
