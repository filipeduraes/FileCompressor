#pragma once
#include <string>
#include <vector>
#include <cstdint>

//Implementa funções de utilidades para manipulação de strings
namespace StringUtils
{
    std::vector<std::string> Split(const std::string& original, char separator = ' ');
    std::string ConvertBytesToBitString(const std::vector<uint8_t>& bytes, uint64_t bitSize);
    void ReplaceAll(std::string& original, const std::string&& replaceWord, const std::string&& replaceBy);
}
