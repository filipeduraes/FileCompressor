#pragma once
#include <string>

namespace Compressor
{
    class INode
    {
    public:
        virtual int GetCount() = 0;
        virtual ~INode() = default;
    };

    class LeafNode final : public INode
    {
    public:
        std::string word;
        int wordCount;
            
        explicit LeafNode(int wordCount, std::string word);
        int GetCount() override;
    };

    class CompositeNode final : public INode
    {
    public:
        INode* leftNode;
        INode* rightNode;
        int count;

        CompositeNode(INode* left, INode* right);
        ~CompositeNode() override;

        int GetCount() override;
    };
}
