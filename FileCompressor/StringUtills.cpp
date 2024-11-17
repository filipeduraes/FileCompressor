﻿#include "StringUtills.h"

std::vector<std::string> StringUtils::Split(const std::string& original, const char separator)
{
    std::vector<std::string> split;
    unsigned long long lastSeparatorOccurrence = 0;

    while(lastSeparatorOccurrence < original.size())
    {
        unsigned long long separatorIndex = original.find(separator, lastSeparatorOccurrence);

        if(separatorIndex == std::string::npos)
        {
            separatorIndex = original.size(); 
        }
        
        std::string substring = original.substr(lastSeparatorOccurrence, separatorIndex - lastSeparatorOccurrence);
        split.push_back(std::move(substring));
        lastSeparatorOccurrence = separatorIndex + 1;
    }

    return split;
}