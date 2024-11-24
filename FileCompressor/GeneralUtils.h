#pragma once
#include <cstdint>
#include <string>
#include <unordered_map>

namespace GeneralUtils
{
    uint64_t GreatestCommonDenominator(uint64_t first, uint64_t second);
    void ShowCompressionResultsLog(const std::string& text, const std::string& result);

    template<typename TKey, typename TValue>
    void ReverseUnorderedMap(const std::unordered_map<TKey, TValue>& original, std::unordered_map<TValue, TKey>& outReversed)
    {
        for(const std::pair<TKey, TValue> pair : original)
        {
            outReversed[pair.second] = pair.first;
        }
    }
}
