#pragma once

#include <cstdint>
#include <string>

#include "Compressor.h"

class FileHandler
{
private:
    std::string path;
    
public:
    explicit FileHandler(std::string filePath);
    
    void SaveTextFile(const std::string& data);
    void SaveBinaryFile(const Compressor::CompressorOutput& data);
    
    std::string LoadTextFile() const;
    Compressor::CompressorOutput LoadBinaryFile() const;

private:
    void ReadAllLinesFromFile(std::vector<std::string>& lines) const;
    static void InterpretCompressionTable(std::vector<std::string> lines, std::map<std::string, std::string>& compressionTable);
    static uint64_t InterpretInitialBitSize(const std::string& line);
    static void InterpretCompressedBytes(const std::string& compressedText, std::vector<uint8_t>& compressedBytes);
    std::string GetOutputPath(bool isCompressed) const;
};