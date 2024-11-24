#include "Compressor.h"
#include "StringUtills.h"

// Private Implementation functions
namespace Compressor
{
    std::string DecodeBitStringWithCompressionTable(CompressorOutput& data, const std::string& bitString)
    {
        std::string currentBits;
        std::string decompressedText;
        
        for (const char& bit : bitString)
        {
            currentBits += bit;

            if (data.compressionTable.find(currentBits) != data.compressionTable.end())
            {
                decompressedText += data.compressionTable.at(currentBits) + " ";
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