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

        CompressorOutput(std::unordered_map<std::string, std::string> compressionTable, const uint64_t initialBitSize, const std::vector<uint8_t>& compressedTextBytes)
            : compressionTable(std::move(compressionTable)),
              initialBitSize(initialBitSize),
              compressedTextBytes(compressedTextBytes)
        {
        }

        uint64_t GetTotalSize() const
        {
            uint64_t totalTableSize = 0;

            for(std::pair<std::string, std::string> pair : compressionTable)
            {
                totalTableSize += pair.first.size() + pair.second.size() * 8;
            }
            
            return totalTableSize + initialBitSize;
        }
    };

    CompressorOutput CompressData(const std::string& text, char separator = ' ');
    std::string DecompressData(CompressorOutput& data);
}
