#include "HuffmanNode.h"

Compressor::HuffmanNode::HuffmanNode(const int frequency)
    : frequency(frequency)
{
}

int Compressor::HuffmanNode::GetFrequency() const
{
    return frequency;
}


Compressor::LeafNode::LeafNode(const int wordFrequency, std::string word)
    : HuffmanNode(wordFrequency), word(std::move(word))
{
}


Compressor::CompositeNode::CompositeNode(HuffmanNode* left, HuffmanNode* right)
    : leftNode(left), rightNode(right)
{
    frequency = leftNode->GetFrequency() + rightNode->GetFrequency();
}

Compressor::CompositeNode::~CompositeNode()
{
    delete leftNode;
    delete rightNode;
}