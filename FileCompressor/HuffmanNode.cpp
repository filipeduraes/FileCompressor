#include "HuffmanNode.h"

Compressor::LeafNode::LeafNode(const int wordCount, std::string word)
    : word(std::move(word)), wordCount(wordCount)
{
}

int Compressor::LeafNode::GetCount()
{
    return wordCount;
}


Compressor::CompositeNode::CompositeNode(IHuffmanNode* left, IHuffmanNode* right)
    : leftNode(left), rightNode(right)
{
    count = leftNode->GetCount() + rightNode->GetCount();
}

Compressor::CompositeNode::~CompositeNode()
{
    delete leftNode;
    delete rightNode;
}

int Compressor::CompositeNode::GetCount()
{
    return count;
}