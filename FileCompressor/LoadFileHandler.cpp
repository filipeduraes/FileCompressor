#include <bitset>
#include "LoadFileHandler.h"
#include "StringUtills.h"

LoadFileHandler::LoadFileHandler(std::filesystem::path filePath)
    : path(std::move(filePath))
{
}

std::string LoadFileHandler::LoadTextFile()
{
    stream = std::ifstream(path);
    std::string line;
    std::string result;

    while (std::getline(stream,line))
    {
        result += line + "\n";
    }

    result = result.substr(0, result.size() - 1);
    stream.close();

    return result;
}

Compressor::CompressorOutput LoadFileHandler::LoadBinaryFile()
{
    stream = std::ifstream(path, std::ios::binary);

    std::unordered_map<std::string, std::string> compressionTable;
    InterpretCompressionTable(compressionTable);

    uint64_t initialBitSize = InterpretInitialBitSize();

    std::vector<uint8_t> compressedBytes;
    InterpretCompressedBytes(compressedBytes);

    stream.close();
    
    return {compressionTable, initialBitSize, compressedBytes};
}

void LoadFileHandler::InterpretCompressionTable(std::unordered_map<std::string, std::string>& compressionTable)
{
    uint8_t maxCodeSizeAsBytes = 0;
    stream.read(reinterpret_cast<char*>(&maxCodeSizeAsBytes), sizeof(maxCodeSizeAsBytes));
    IgnoreSeparator();
    
    uint64_t tableSize = 0;
    stream.read(reinterpret_cast<char*>(&tableSize), sizeof(tableSize));
    IgnoreSeparator();

    for (uint64_t i = 0; i < tableSize; i++)
    {
        uint64_t code = 0;
        uint8_t codeSizeInBits = 0;
        
        stream.read(reinterpret_cast<char*>(&code), maxCodeSizeAsBytes);
        stream.read(reinterpret_cast<char*>(&codeSizeInBits), sizeof(codeSizeInBits));
        std::string value;
        std::getline(stream, value);
        
        std::string key = std::bitset<64>(code).to_string();
        key = key.substr(key.size() - codeSizeInBits, codeSizeInBits);
        StringUtils::ReplaceAll(value, "\\n", "\n");
        
        compressionTable[key] = value;
    }
}

uint64_t LoadFileHandler::InterpretInitialBitSize()
{
    uint64_t initialBitSize = 0;
    stream.read(reinterpret_cast<char*>(&initialBitSize), sizeof(initialBitSize));
    return initialBitSize;
}

void LoadFileHandler::InterpretCompressedBytes(std::vector<uint8_t>& compressedBytes)
{
    IgnoreSeparator();
    uint8_t byte = 0;

    while(stream.read(reinterpret_cast<char*>(&byte), sizeof(byte)))
    {
        compressedBytes.push_back(byte);
    }
}

void LoadFileHandler::IgnoreSeparator()
{
    char separator;
    stream.read(&separator, sizeof(char));
}