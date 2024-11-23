#pragma once

#include <unordered_map>
#include <string>
#include <vector>
#include <cstdint>

namespace Compressor
{
    struct CompressorOutput
    {
        std::unordered_map<std::string, std::string> compressionTable;
        uint64_t initialBitSize;
        std::vector<uint8_t> compressedTextBytes;

        CompressorOutput() = default;

        CompressorOutput(std::unordered_map<std::string, std::string> compressionTable, const uint64_t initialBitSize, std::vector<uint8_t> compressedTextBytes)
            : compressionTable(std::move(compressionTable)),
              initialBitSize(initialBitSize),
              compressedTextBytes(std::move(compressedTextBytes))
        {
        }
    };

    CompressorOutput CompressData(const std::string& text);
    std::string DecompressData(CompressorOutput& data);
}
