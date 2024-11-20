#include "FileHandler.h"

#include <fstream>
#include <sstream>

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

std::string FileHandler::LoadTextFile() const
{
    std::ifstream stream (path);
    std::string line;
    std::string result;

    while (std::getline(stream,line))
    {
        result += line;
    }

    stream.close();

    return result;
}

Compressor::CompressorOutput FileHandler::LoadBinaryFile() const
{
    std::vector<std::string> lines;
    ReadAllLinesFromFile(lines);

    std::map<std::string, std::string> compressionTable;
    InterpretCompressionTable(lines, compressionTable);

    uint64_t initialBitSize = InterpretInitialBitSize(lines[lines.size() - 2]);

    std::vector<uint8_t> compressedBytes;
    InterpretCompressedBytes(lines[lines.size() - 1], compressedBytes);
    
    return {compressionTable, initialBitSize, compressedBytes};
}


void FileHandler::ReadAllLinesFromFile(std::vector<std::string>& lines) const
{
    std::ifstream stream(path);
    std::string line;

    while (std::getline(stream, line))
    {
        lines.push_back(line);
    }

    stream.close();
}

void FileHandler::InterpretCompressionTable(std::vector<std::string> lines, std::map<std::string, std::string>& compressionTable)
{
    for (uint64_t i = 0; i < lines.size() - 2; i++)
    {
        std::string& line = lines[i];
        const uint64_t separatorIndex = line.find_last_of(':');
    
        std::string key = line.substr(0,separatorIndex);
        const std::string value = line.substr(separatorIndex + 1, line.size() - separatorIndex);
    
        compressionTable[key] = value;
    }
}

uint64_t FileHandler::InterpretInitialBitSize(const std::string& line)
{
    uint64_t initialBitSize;
    std::stringstream sizeStream(line);
    sizeStream.read(reinterpret_cast<char*>(&initialBitSize), sizeof(initialBitSize));
    return initialBitSize;
}

void FileHandler::InterpretCompressedBytes(const std::string& compressedText, std::vector<uint8_t>& compressedBytes)
{
    std::stringstream compressedStream(compressedText);

    while(!compressedStream.eof())
    {
        uint8_t byte;
        compressedStream.read(reinterpret_cast<char*>(&byte), sizeof(byte));
        compressedBytes.push_back(byte);
    }
}

std::string FileHandler::GetOutputPath(const bool isCompressed) const
{
    const uint64_t extensionDotIndex = path.find_last_of('.');
    const std::string extensionlessPath = path.substr(0, extensionDotIndex);
    const std::string finalPath = extensionlessPath + (isCompressed ? "_Compressed.huf" : "_Decompressed.txt");
    
    return finalPath;
}