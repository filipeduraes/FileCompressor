#include "FileHandler.h"

FileHandler::FileHandler(std::string filePath)
    : path(std::move(filePath))
{
}

void FileHandler::SaveTextFile(const std::string& data)
{
    
}

void FileHandler::SaveBinaryFile(const Compressor::CompressorOutput& data)
{
    
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
