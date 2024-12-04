#pragma once
#include <string>
#include <unordered_map>
#include <cstdint>
#include <filesystem>
#include <fstream>
#include <vector>
#include "Compressor.h"

//Cuida do carregamento de arquivos
class LoadFileHandler
{
private:
    std::filesystem::path path;
    std::ifstream stream;
    
public:
    explicit LoadFileHandler(std::filesystem::path filePath);
    
    std::string LoadTextFile();
    Compressor::CompressorOutput LoadBinaryFile();

private:    
    void InterpretCompressionTable(std::unordered_map<std::string, std::string>& compressionTable);
    uint64_t InterpretInitialBitSize();
    void InterpretCompressedBytes(std::vector<uint8_t>& compressedBytes);
};
