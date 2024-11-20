#include <stack>
#include <bitset>
#include "Compressor.h"
#include "HuffmanNode.h"
#include "StringUtills.h"

std::vector<Compressor::IHuffmanNode*> GetInitialWordCounts(const std::vector<std::string>& words)
{
    std::map<std::string, int> wordCounts;
    
    for(const std::string& word : words)
    {
        if(wordCounts.count(word) == 0)
        {
            wordCounts[word] = 0;
        }

        wordCounts[word]++;
    }

    std::vector<Compressor::IHuffmanNode*> result;
    result.reserve(wordCounts.size());
    
    for(const std::pair<const std::string, int>& wordCount : wordCounts)
    {
        result.push_back(new Compressor::LeafNode(wordCount.second, wordCount.first));
    }
    
    return result;
}

std::tuple<uint64_t, uint64_t> GetTwoSmallerIndexes(const std::vector<Compressor::IHuffmanNode*>& nodes)
{
    uint64_t smallestIndex = 0;
    uint64_t secondSmallestIndex = 0;

    for(uint64_t i = 1; i < nodes.size(); i++)
    {
        if(nodes[i]->GetCount() < nodes[smallestIndex]->GetCount())
        {
            secondSmallestIndex = smallestIndex;
            smallestIndex = i;
        }
        else if(secondSmallestIndex == smallestIndex || nodes[i]->GetCount() < nodes[secondSmallestIndex]->GetCount())
        {
            secondSmallestIndex = i;
        }
    }

    return {smallestIndex, secondSmallestIndex};
}

Compressor::IHuffmanNode* CreateNodeTree(std::vector<Compressor::IHuffmanNode*>& nodeTree)
{
    while(nodeTree.size() > 1)
    {
        std::tuple<uint64_t, uint64_t> twoSmallerIndexes = GetTwoSmallerIndexes(nodeTree);

        const uint64_t smallerIndex = std::get<0>(twoSmallerIndexes);
        const uint64_t secondSmallerIndex = std::get<1>(twoSmallerIndexes);

        Compressor::IHuffmanNode* smallerNode = nodeTree[smallerIndex];
        Compressor::IHuffmanNode* secondSmallerNode = nodeTree[secondSmallerIndex];
        
        nodeTree.erase(nodeTree.begin() + static_cast<size_t>(smallerIndex));
        const uint64_t secondSmallerIndexAfterRemoval = secondSmallerIndex < smallerIndex ? secondSmallerIndex : secondSmallerIndex - 1;
        nodeTree.erase(nodeTree.begin() + static_cast<size_t>(secondSmallerIndexAfterRemoval));

        Compressor::IHuffmanNode* combinedNode = new Compressor::CompositeNode(smallerNode, secondSmallerNode);
        nodeTree.push_back(combinedNode);
    }

    return nodeTree[0];
}

void BuildEncodingTableRecursive(Compressor::IHuffmanNode* currentNode, std::map<std::string, std::string>& binaryWords, const std::string& currentCode = "")
{
    if(const Compressor::CompositeNode* currentComposite = dynamic_cast<Compressor::CompositeNode*>(currentNode))
    {
        BuildEncodingTableRecursive(currentComposite->leftNode, binaryWords, currentCode + '0');
        BuildEncodingTableRecursive(currentComposite->rightNode, binaryWords, currentCode + '1');
    }
    else if(const Compressor::LeafNode* currentLeaf = dynamic_cast<Compressor::LeafNode*>(currentNode))
    {
        binaryWords[currentLeaf->word] = currentCode;
    }
}

std::string EncodeText(const std::vector<std::string>& words, std::map<std::string, std::string>& compressionTable)
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
        result.push_back(convertedText);
    }

    return result;
}

Compressor::CompressorOutput Compressor::CompressData(const std::string& text)
{
    if(!text.empty())
    {
        const std::vector<std::string> words = StringUtils::Split(text);

        if (!words.empty())
        {
            std::vector<IHuffmanNode*> nodeTree = GetInitialWordCounts(words);
            IHuffmanNode* root = CreateNodeTree(nodeTree);

            std::map<std::string, std::string> compressionTable;
            BuildEncodingTableRecursive(root, compressionTable);
            const std::string result = EncodeText(words, compressionTable);
            const std::vector<uint8_t> textBytes = ConvertEncodedTextToBytes(result);

            return {compressionTable, result.size(), textBytes};
        }
    }
    
    return {};
}

std::string Compressor::DecompressData(CompressorOutput& data)
{
   std::string decompressedText;
    std::string bitString;
    //Conversão dos bytes comprimidos para uma string de bits
    for (const auto& byte : data.compressedTextBytes)
    {
        std::bitset<8> bits(byte);
        bitString += bits.to_string();
    }
    // Remover os bits extras com base no tamanho
    bitString = bitString.substr(0, data.initialBitSize);
    // Descomprimir os dados utilizando a tabela de compressão
    std::string currentBits;
    for (size_t i = 0; i < bitString.size(); ++i)
    {
        currentBits += bitString[i]; // Adicionar o bit ao bloco de bits

        // Ve se o bloco de bits existe na tabela de compressão
        if (data.compressionTable.find(currentBits) != data.compressionTable.end())
        {
            // Se encontrar, adicionar a palavra ao texto descomprimido
            decompressedText += data.compressionTable.at(currentBits) + " ";

            // Resetar o bloco de bits
            currentBits.clear();
        }
    }
    // Remover o último espaço em branco (se adicionado)
    if (!decompressedText.empty() && decompressedText.back() == ' ')
    {
        decompressedText.pop_back();
    }
    return decompressedText; 
}