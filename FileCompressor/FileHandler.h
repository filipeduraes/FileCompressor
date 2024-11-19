#pragma once

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
    
    std::string LoadTextFile();
    Compressor::CompressorOutput LoadBinaryFile();

private:
    std::string GetOutputPath(bool isCompressed) const;
};