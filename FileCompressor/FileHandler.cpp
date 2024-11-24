#include <fstream>
#include <sstream>

#include "FileHandler.h"

FileHandler::FileHandler(const std::string& filePath)
    : path(filePath)
{
}

void FileHandler::SaveTextFile(const std::string& data)
{
    std::filesystem::path outputPath = GetOutputPath(false);
    std::ofstream stream(outputPath);
    stream << data;
    stream.close();
}

void FileHandler::SaveBinaryFile(const Compressor::CompressorOutput& data)
{
    std::filesystem::path outputPath = GetOutputPath(true);
    std::ofstream stream(outputPath, std::ios::binary);

    for(std::pair<std::string, std::string> pair : data.compressionTable )
    {
        stream << pair.first << ":" << pair.second << "\n";
    }

    stream.write(reinterpret_cast<const char*>(&data.initialBitSize), sizeof(data.initialBitSize));
    stream << "\n";

    for(uint8_t textByte : data.compressedTextBytes)
    {
        stream.write(reinterpret_cast<const char*>(&textByte), sizeof(textByte));
    } 

    stream.close();
}

std::string FileHandler::LoadTextFile() const
{
    std::ifstream stream(path);
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

    std::unordered_map<std::string, std::string> compressionTable;
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
        lines.push_back(std::move(line));
    }

    stream.close();
}

void FileHandler::InterpretCompressionTable(std::vector<std::string>& lines, std::unordered_map<std::string, std::string>& compressionTable)
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

std::filesystem::path FileHandler::GetOutputPath(const bool isCompressed) const
{
    const std::filesystem::path directory = path.parent_path();
    const std::string fileName = "Saida";
    const std::string fileExtension = isCompressed ? ".huf" : ".txt";

    std::filesystem::path outputPath = directory / (fileName + fileExtension);
    return outputPath;
}