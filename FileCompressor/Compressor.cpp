#include <bitset>
#include <iostream>

#include "HuffmanNode.h"
#include "StringUtills.h"
#include "Compressor.h"

// Private Global functions
std::vector<Compressor::HuffmanNode*> CreateLeafNodesFromFrequencies(const std::vector<std::string>& words)
{
    std::unordered_map<std::string, int> frequencies;
    
    for(const std::string& word : words)
    {
        if(frequencies.count(word) == 0)
        {
            frequencies[word] = 0;
        }

        frequencies[word]++;
    }

    std::vector<Compressor::HuffmanNode*> result;
    result.reserve(frequencies.size());
    
    for(const std::pair<const std::string, int>& frequency : frequencies)
    {
        result.emplace_back(new Compressor::LeafNode(frequency.second, frequency.first));
    }
    
    return result;
}

std::tuple<uint64_t, uint64_t> FindTwoSmallestIndexesFromNodes(const std::vector<Compressor::HuffmanNode*>& nodes)
{
    uint64_t smallestIndex = 0;
    uint64_t secondSmallestIndex = 0;

    for(uint64_t i = 1; i < nodes.size(); i++)
    {
        if(nodes[i]->GetFrequency() < nodes[smallestIndex]->GetFrequency())
        {
            secondSmallestIndex = smallestIndex;
            smallestIndex = i;
        }
        else if(secondSmallestIndex == smallestIndex || nodes[i]->GetFrequency() < nodes[secondSmallestIndex]->GetFrequency())
        {
            secondSmallestIndex = i;
        }
    }

    return {smallestIndex, secondSmallestIndex};
}

Compressor::HuffmanNode* CreateNodeTree(std::vector<Compressor::HuffmanNode*>& nodeTree)
{
    while(nodeTree.size() > 1)
    {
        std::tuple<uint64_t, uint64_t> twoSmallerIndexes = FindTwoSmallestIndexesFromNodes(nodeTree);

        const uint64_t smallerIndex = std::get<0>(twoSmallerIndexes);
        const uint64_t secondSmallerIndex = std::get<1>(twoSmallerIndexes);

        Compressor::HuffmanNode* smallerNode = nodeTree[smallerIndex];
        Compressor::HuffmanNode* secondSmallerNode = nodeTree[secondSmallerIndex];
        
        nodeTree.erase(nodeTree.begin() + static_cast<uint64_t>(smallerIndex));
        const uint64_t secondSmallerIndexAfterRemoval = secondSmallerIndex < smallerIndex ? secondSmallerIndex : secondSmallerIndex - 1;
        nodeTree.erase(nodeTree.begin() + static_cast<uint64_t>(secondSmallerIndexAfterRemoval));

        Compressor::HuffmanNode* combinedNode = new Compressor::CompositeNode(smallerNode, secondSmallerNode);
        nodeTree.push_back(combinedNode);
    }

    return nodeTree[0];
}

void BuildCompressionTableRecursive(Compressor::HuffmanNode* currentNode, std::unordered_map<std::string, std::string>& binaryWords, const std::string& currentCode = "")
{
    if(const Compressor::CompositeNode* currentComposite = dynamic_cast<Compressor::CompositeNode*>(currentNode))
    {
        BuildCompressionTableRecursive(currentComposite->leftNode, binaryWords, currentCode + '0');
        BuildCompressionTableRecursive(currentComposite->rightNode, binaryWords, currentCode + '1');
    }
    else if(const Compressor::LeafNode* currentLeaf = dynamic_cast<Compressor::LeafNode*>(currentNode))
    {
        binaryWords[currentLeaf->word] = currentCode;
    }
}

std::string EncodeText(const std::vector<std::string>& words, std::unordered_map<std::string, std::string>& compressionTable)
{
    std::string result;
    
    for(const std::string& word : words)
    {
        result += compressionTable[word];
    }
    
    return result;
}

std::vector<uint8_t> ConvertEncodedTextToBytes(const std::string& encodedText)
{
    std::vector<uint8_t> result;
    
    for(uint64_t i = 0; i < encodedText.size(); i += 8)
    {
        const uint64_t count = std::min(encodedText.size() - i, 8ull);
        std::string byteSizeText = encodedText.substr(i, count);

        if(byteSizeText.size() < 8)
        {
            byteSizeText.append(8 - count, '0');
        }

        uint8_t convertedText = static_cast<uint8_t>(strtol(byteSizeText.c_str(), nullptr, 2));
        result.emplace_back(convertedText);
    }

    return result;
}

void ReverseCompressionTable(const std::unordered_map<std::string, std::string>& compressionTable, std::unordered_map<std::string, std::string>& reversedCompressionTable)
{
    for(const std::pair<std::string, std::string> pair : compressionTable)
    {
        reversedCompressionTable[pair.second] = pair.first;
    }
}

std::string ConvertCompressedBytesToBitString(const Compressor::CompressorOutput& data)
{
    std::string bitString;

    for (const uint8_t& byte : data.compressedTextBytes)
    {
        std::bitset<8> bits(byte);
        bitString += bits.to_string();
    }
    
    return bitString;
}

std::string DecodeBitStringWithCompressionTable(Compressor::CompressorOutput& data, const std::string& bitString)
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


// Public API functions
Compressor::CompressorOutput Compressor::CompressData(const std::string& text)
{
    if(!text.empty())
    {
        const std::vector<std::string> words = StringUtils::Split(text);

        if (!words.empty())
        {
            std::vector<HuffmanNode*> nodeTree = CreateLeafNodesFromFrequencies(words);
            HuffmanNode* root = CreateNodeTree(nodeTree);

            std::unordered_map<std::string, std::string> compressionTable;
            BuildCompressionTableRecursive(root, compressionTable);
            const std::string result = EncodeText(words, compressionTable);
            const std::vector<uint8_t> textBytes = ConvertEncodedTextToBytes(result);
            
            std::unordered_map<std::string, std::string> reversedCompressionTable;
            ReverseCompressionTable(compressionTable, reversedCompressionTable);
            compressionTable.clear();
            delete root;

            std::cout << "\nTamanho inicial em bits: " << text.size() * 8 << '\n';
            std::cout << "Tamanho final em bits: " << result.size() << '\n';
            std::cout << "Taxa de compressao: " << static_cast<float>(result.size()) / static_cast<float>(text.size() * 8) << '\n';
            
            return {reversedCompressionTable, result.size(), textBytes};
        }
    }
    
    return {};
}

std::string Compressor::DecompressData(CompressorOutput& data)
{
    std::string bitString = ConvertCompressedBytesToBitString(data);

    // Remover os bits extras com base no tamanho
    bitString = bitString.substr(0, data.initialBitSize);
    
    std::string decompressedText = DecodeBitStringWithCompressionTable(data, bitString);
    
    // Remover o último espaço em branco (se adicionado)
    if (!decompressedText.empty() && decompressedText.back() == ' ')
    {
        decompressedText.pop_back();
    }
    
    return decompressedText; 
}
