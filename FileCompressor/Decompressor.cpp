#include <algorithm>

#include "Compressor.h"
#include "StringUtills.h"

// Private Implementation functions
namespace Compressor
{
    bool IsCompressedByLetters(const CompressorOutput& data)
    {
        return std::all_of(data.compressionTable.cbegin(), data.compressionTable.cend(),
            [](const std::pair<const std::string, std::string>& pair)
            {
                return pair.second.size() == 1;
            });
    }
    
    std::string DecodeBitStringWithCompressionTable(CompressorOutput& data, const std::string& bitString)
    {
        std::string currentBits;
        std::string decompressedText;

        const bool isCompressedByLetters = IsCompressedByLetters(data);

        for (const char& bit : bitString)
        {
            currentBits += bit;

            if (data.compressionTable.find(currentBits) != data.compressionTable.end())
            {
                decompressedText += data.compressionTable.at(currentBits);

                if(!isCompressedByLetters)
                {
                    decompressedText += ' ';
                }
                
                currentBits.clear();
            }
        }

        return decompressedText;
    }
}


// Public API functions
std::string Compressor::DecompressData(CompressorOutput& data)
{
    const std::string bitString = StringUtils::ConvertBytesToBitString(data.compressedTextBytes, data.initialBitSize);
    std::string decompressedText = DecodeBitStringWithCompressionTable(data, bitString);
    
    // Remover o último espaço em branco (se adicionado)
    if (!decompressedText.empty() && decompressedText.back() == ' ')
    {
        decompressedText.pop_back();
    }
    
    return decompressedText; 
}