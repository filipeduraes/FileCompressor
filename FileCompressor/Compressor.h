#pragma once
#include <string>

class Compressor
{
public:
    std::string CompressData(std::string& data);
    std::string DecompressData(std::string& data);
};
