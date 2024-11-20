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
    std::ifstream stream (path);
    std::string line;
    std::string result;

    while (std::getline(stream,line))
        {
            result+= line;    
        }

        stream.close();

    return result;
}

Compressor::CompressorOutput FileHandler::LoadBinaryFile()
{
    std::ifstream stream(path);
    std::string line;
    std::vector<std::string> lines;

    while (std::getline(stream,line ))
    {
        lines.push_back(line);
    }

    std::map<std::string, std::string> compressionTable;
    
    for (int i = 0; i < lines.size() - 2; i++)
    {
        line = lines[i];
        uint64_t separatorIndex = line.find_last_of(':');
    
        std::string key = line.substr(0,separatorIndex);
        std::string valor = line.substr(separatorIndex + 1, line.size() - separatorIndex);
    
        compressionTable[key] = valor;

    }
        uint64_t initialBitSize = 0;
        std::stringstream sizeStream (lines[lines.size()-2]);
        sizeStream.read(reinterpret_cast<char*>(&initialBitSize), sizeof(initialBitSize));
    
        std::vector<uint8_t> compressedBytes;
        std::stringstream compressedStream (lines[lines.size()-1]);

        while(!compressedStream.eof())
        {
            uint8_t byte;
            compressedStream.read(reinterpret_cast<char*>(&byte), sizeof(byte));
            compressedBytes.push_back(byte);
        }
        
        stream.close();

        return {compressionTable, initialBitSize, compressedBytes};
    }

std::string FileHandler::GetOutputPath(const bool isCompressed) const
{
    const uint64_t extensionDotIndex = path.find_last_of('.');
    const std::string extensionlessPath = path.substr(0, extensionDotIndex);
    const std::string finalPath = extensionlessPath + (isCompressed ? "_Compressed.huf" : "_Decompressed.txt");
    
    return finalPath;
}
