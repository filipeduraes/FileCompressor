#include "FileHandler.h"

FileHandler::FileHandler(std::string filePath)
    : path(std::move(filePath))
{
}

void FileHandler::SaveTextFile(const std::string& data)
{
    std::string outputPath = GetOutputPath(false);
}

void FileHandler::SaveBinaryFile(const Compressor::CompressorOutput& data)
{
    std::string outputPath = GetOutputPath(true);
}

std::string FileHandler::LoadTextFile()
{
    return "";
}

Compressor::CompressorOutput FileHandler::LoadBinaryFile()
{
    std::map<std::string, std::string> compressionTable;
    uint64_t initialBitSize = 0;
    std::vector<uint8_t> compressedBytes;
    
    return {compressionTable, initialBitSize, compressedBytes};
}

std::string FileHandler::GetOutputPath(const bool isCompressed) const
{
    const uint64_t extensionDotIndex = path.find_last_of('.');
    const std::string extensionlessPath = path.substr(0, extensionDotIndex);
    const std::string finalPath = extensionlessPath + (isCompressed ? "_Compressed.huf" : "_Decompressed.txt");
    
    return finalPath;
}
