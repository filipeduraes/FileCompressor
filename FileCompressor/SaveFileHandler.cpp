#include "SaveFileHandler.h"

#include <iostream>

#include "BinaryUtils.h"
#include "StringUtills.h"

SaveFileHandler::SaveFileHandler(std::filesystem::path filePath)
    : path(std::move(filePath))
{
}

void SaveFileHandler::SaveTextFile(const std::string& data)
{
    const std::filesystem::path outputPath = GetOutputPath(false);
    stream = std::ofstream(outputPath);

    if(!stream.is_open())
    {
        std::cout << "Arquivo nao pode ser aberto.\n";
        return;
    }
    
    stream << data;
    stream.close();

    std::cout << "\nArquivo salvo em: " << outputPath.string() << "\n";
}

void SaveFileHandler::SaveBinaryFile(const Compressor::CompressorOutput& data)
{
    const std::filesystem::path outputPath = GetOutputPath(true);
    stream = std::ofstream(outputPath, std::ios::binary);

    if(!stream.is_open())
    {
        std::cout << "Arquivo nao pode ser aberto.\n";
        return;
    }
    
    WriteCompressionTable(data.compressionTable);
    WriteInitialBitSize(data.initialBitSize);
    WriteCompressedTextBytes(data.compressedTextBytes);

    stream.close();
    std::cout << "Arquivo salvo em: " << outputPath.string() << "\n";
}

void SaveFileHandler::WriteCompressionTable(const std::unordered_map<std::string, std::string>& compressionTable)
{
    const uint8_t maxBitSize = GetMaxBitSizeFromCompressionTableCodes(compressionTable);
    const uint8_t maxCodeSizeAsBytes = BinaryUtils::ConvertBitSizeToByteSize(maxBitSize);
    
    stream.write(reinterpret_cast<const char*>(&maxCodeSizeAsBytes), sizeof(maxCodeSizeAsBytes));
    stream << '\n';

    const uint64_t tableSize = compressionTable.size();
    stream.write(reinterpret_cast<const char*>(&tableSize), sizeof(tableSize));
    stream << '\n';
    
    for(std::pair<std::string, std::string> pair : compressionTable)
    {
        StringUtils::ReplaceAll(pair.second, "\n", "\\n");
        uint64_t codeAsBinary = strtol(pair.first.c_str(), nullptr, 2);
        uint8_t codeSizeInBits = static_cast<uint8_t>(pair.first.size());
        
        stream.write(reinterpret_cast<const char*>(&codeAsBinary), maxCodeSizeAsBytes);
        stream.write(reinterpret_cast<const char*>(&codeSizeInBits), sizeof(codeSizeInBits));
        stream << pair.second << '\n';
    }
}

void SaveFileHandler::WriteInitialBitSize(const uint64_t initialBitSize)
{
    stream.write(reinterpret_cast<const char*>(&initialBitSize), sizeof(initialBitSize));
    stream << "\n";
}

void SaveFileHandler::WriteCompressedTextBytes(const std::vector<uint8_t>& compressedTextBytes)
{
    for(uint8_t textByte : compressedTextBytes)
    {
        stream.write(reinterpret_cast<const char*>(&textByte), sizeof(textByte));
    }
}

uint8_t SaveFileHandler::GetMaxBitSizeFromCompressionTableCodes(const std::unordered_map<std::string, std::string>& compressionTable)
{
    uint8_t maxBitSize = 0;

    for(std::pair<std::string, std::string> pair : compressionTable)
    {
        if(pair.first.size() > maxBitSize)
        {
            maxBitSize = static_cast<uint8_t>(pair.first.size());
        }
    }
    return maxBitSize;
}

std::filesystem::path SaveFileHandler::GetOutputPath(const bool isCompressed) const
{
    const std::filesystem::path directory = path.parent_path();
    const std::string fileName = isCompressed ? "saida.huf" : "entrada.txt";

    std::filesystem::path outputPath = directory / fileName;
    return outputPath;
}