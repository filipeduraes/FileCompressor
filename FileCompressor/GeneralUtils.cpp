#include "GeneralUtils.h"

#include <iostream>

uint64_t GeneralUtils::GreatestCommonDenominator(const uint64_t first, const uint64_t second)
{
    if (second == 0)
        return first;
    
    return GreatestCommonDenominator(second, first % second);
}

void GeneralUtils::ShowCompressionResultsLog(const std::string& text, const std::string& result)
{
    const uint64_t originalSize = text.size();
    const uint64_t resultSize = result.size() / 8;
        
    std::cout << "\nTamanho inicial: " << text.size() * 8 << "b, " << originalSize << "B" << '\n';
    std::cout << "Tamanho final: " << result.size() << "b, " << resultSize << "B" << '\n';

    const uint64_t greatestCommonDenominator = GreatestCommonDenominator(text.size() * 8, result.size());

    std::cout << "Razao de Compressao: " << originalSize / greatestCommonDenominator << ':' << resultSize / greatestCommonDenominator << '\n';
    std::cout << "Taxa de compressao: " << (1.0 - static_cast<double>(resultSize) / static_cast<double>(originalSize)) * 100.0 << "%\n";
}
