#pragma once
#include <map>
#include <string>
#include <vector>

namespace Compressor
{
    struct CompressorOutput
    {
        std::map<std::string, std::string> compressionTable;
        uint64_t initialBitSize;
        std::vector<uint8_t> compressedTextBytes;

        CompressorOutput() = default;

        CompressorOutput(std::map<std::string, std::string> compressionTable, const uint64_t initialBitSize, std::vector<uint8_t> compressedTextBytes)
            : compressionTable(std::move(compressionTable)),
              initialBitSize(initialBitSize),
              compressedTextBytes(std::move(compressedTextBytes))
        {
        }
    };

    CompressorOutput CompressData(const std::string& text);
    std::string DecompressData(CompressorOutput& data);
}
