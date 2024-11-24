#pragma once

#include <string>
#include <filesystem>

#include "Compressor.h"

class FileHandler
{
private:
    std::filesystem::path path;

public:
    explicit FileHandler(const std::string& filePath);

    void SaveTextFile(const std::string& data) const;
    void SaveBinaryFile(const Compressor::CompressorOutput& data) const;
    
    std::string LoadTextFile() const;
    Compressor::CompressorOutput LoadBinaryFile() const;
};