#pragma once
#include <string>

namespace Compressor
{
    class IHuffmanNode
    {
    public:
        virtual ~IHuffmanNode() = default;
        virtual int GetCount() = 0;
    };

    class LeafNode final : public IHuffmanNode
    {
    public:
        std::string word;
        int wordCount;
            
        explicit LeafNode(int wordCount, std::string word);
        int GetCount() override;
    };

    class CompositeNode final : public IHuffmanNode
    {
    public:
        IHuffmanNode* leftNode;
        IHuffmanNode* rightNode;
        int count;

        CompositeNode(IHuffmanNode* left, IHuffmanNode* right);
        ~CompositeNode() override;

        int GetCount() override;
    };
}
