#pragma once
#include <string>

namespace Compressor
{
    class HuffmanNode
    {
    protected:
        int frequency;

        HuffmanNode() = default;
        explicit HuffmanNode(int frequency);

    public:
        virtual ~HuffmanNode() = default;
        int GetFrequency() const;
    };

    class LeafNode final : public HuffmanNode
    {
    public:
        std::string word;
            
        explicit LeafNode(int wordFrequency, std::string word);
    };

    class CompositeNode final : public HuffmanNode
    {
    public:
        HuffmanNode* leftNode;
        HuffmanNode* rightNode;

        CompositeNode(HuffmanNode* left, HuffmanNode* right);
        ~CompositeNode() override;
    };
}
