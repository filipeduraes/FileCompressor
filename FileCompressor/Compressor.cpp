#include <bitset>
#include <iostream>

#include "HuffmanNode.h"
#include "StringUtills.h"
#include "Compressor.h"

#include "BinaryUtils.h"
#include "GeneralUtils.h"

// Private Implementation functions
namespace Compressor
{
    std::vector<HuffmanNode*> CreateLeafNodesFromFrequencies(const std::vector<std::string>& words)
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

        std::vector<HuffmanNode*> result;
        result.reserve(frequencies.size());
    
        for(const std::pair<const std::string, int>& frequency : frequencies)
        {
            result.emplace_back(new LeafNode(frequency.second, frequency.first));
        }
    
        return result;
    }

    std::tuple<uint64_t, uint64_t> FindTwoSmallestIndexesFromNodes(const std::vector<HuffmanNode*>& nodes)
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

    HuffmanNode* CreateNodeTree(std::vector<HuffmanNode*>& nodeTree)
    {
        while(nodeTree.size() > 1)
        {
            std::tuple<uint64_t, uint64_t> twoSmallerIndexes = FindTwoSmallestIndexesFromNodes(nodeTree);

            const uint64_t smallerIndex = std::get<0>(twoSmallerIndexes);
            const uint64_t secondSmallerIndex = std::get<1>(twoSmallerIndexes);

            HuffmanNode* smallerNode = nodeTree[smallerIndex];
            HuffmanNode* secondSmallerNode = nodeTree[secondSmallerIndex];
        
            nodeTree.erase(nodeTree.begin() + (size_t) smallerIndex);
            const uint64_t secondSmallerIndexAfterRemoval = secondSmallerIndex < smallerIndex ? secondSmallerIndex : secondSmallerIndex - 1;
            nodeTree.erase(nodeTree.begin() + (size_t) secondSmallerIndexAfterRemoval);

            HuffmanNode* combinedNode = new CompositeNode(smallerNode, secondSmallerNode);
            nodeTree.push_back(combinedNode);
        }

        return nodeTree[0];
    }

    void BuildCompressionTableRecursive(HuffmanNode* currentNode, std::unordered_map<std::string, std::string>& binaryWords, const std::string& currentCode = "")
    {
        if(const CompositeNode* currentComposite = dynamic_cast<CompositeNode*>(currentNode))
        {
            BuildCompressionTableRecursive(currentComposite->leftNode, binaryWords, currentCode + '0');
            BuildCompressionTableRecursive(currentComposite->rightNode, binaryWords, currentCode + '1');
        }
        else if(const LeafNode* currentLeaf = dynamic_cast<LeafNode*>(currentNode))
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
}

// Public API function
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
            delete root;
            
            const std::string result = EncodeText(words, compressionTable);
            const std::vector<uint8_t> textBytes = BinaryUtils::ConvertEncodedTextToBytes(result);
            
            std::unordered_map<std::string, std::string> reversedCompressionTable;
            GeneralUtils::ReverseUnorderedMap(compressionTable, reversedCompressionTable);
            compressionTable.clear();

            GeneralUtils::ShowCompressionResultsLog(text, result);
            
            return {reversedCompressionTable, result.size(), textBytes};
        }
    }
    
    return {};
}