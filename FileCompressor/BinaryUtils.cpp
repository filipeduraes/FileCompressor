#include <cmath>
#include "BinaryUtils.h"

uint8_t BinaryUtils::ConvertBitSizeToByteSize(const uint8_t bitSize)
{
    const uint8_t byteSize = static_cast<uint8_t>(std::ceil(bitSize / 8.0));
    return byteSize;
}
