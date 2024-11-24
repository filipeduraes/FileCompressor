#pragma once
#include <fstream>
#include <unordered_map>
#include <cstdint>
#include <filesystem>

#include "Compressor.h"

class SaveFileHandler
{
private:
    std::filesystem::path path;
    std::ofstream stream;
    
public:
    explicit SaveFileHandler(std::filesystem::path filePath);
    
    void SaveTextFile(const std::string& data);
    void SaveBinaryFile(const Compressor::CompressorOutput& data);
    
private:
    void WriteCompressionTable(const std::unordered_map<std::string, std::string>& compressionTable);
    void WriteInitialBitSize(uint64_t initialBitSize);
    void WriteCompressedTextBytes(const std::vector<uint8_t>& compressedTextBytes);
    static uint8_t GetMaxBitSizeFromCompressionTableCodes(const std::unordered_map<std::string, std::string>& compressionTable);
    std::filesystem::path GetOutputPath(bool isCompressed) const;
};
