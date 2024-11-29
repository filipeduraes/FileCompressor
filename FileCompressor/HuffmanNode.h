#pragma once
#include <string>

namespace Compressor
{
    //Base para os dois tipos de nó da árvore de Huffman
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

    //Nó folha, que guarda a palavra final
    class LeafNode final : public HuffmanNode
    {
    public:
        std::string word;
            
        explicit LeafNode(int wordFrequency, std::string word);
    };

    //Nó que possui dois filhos, liga dois nós folhas
    class CompositeNode final : public HuffmanNode
    {
    public:
        HuffmanNode* leftNode;
        HuffmanNode* rightNode;

        CompositeNode(HuffmanNode* left, HuffmanNode* right);
        ~CompositeNode() override;
    };
}
