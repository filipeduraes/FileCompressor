#pragma once

#include <unordered_map>
#include <string>
#include <vector>
#include <cstdint>

namespace Compressor
{
    struct CompressorOutput
    {
        std::unordered_map<std::string, std::string> compressionTable;
        uint64_t initialBitSize;
        std::vector<uint8_t> compressedTextBytes;

        CompressorOutput() = default;

        CompressorOutput(std::unordered_map<std::string, std::string> compressionTable, const uint64_t initialBitSize, const std::vector<uint8_t>& compressedTextBytes)
            : compressionTable(std::move(compressionTable)),
              initialBitSize(initialBitSize),
              compressedTextBytes(compressedTextBytes)
        {
        }

        /*
         * Tamanho aproximado do arquivo final
         * Leva em consideração o tamanho total da tabela de compressão
         * e o tamanho em bits do texto comprimido
         * Ignora as outras informações de tamanho fixo
         * Usado para a comparação entre os métodos
         */
        uint64_t GetTotalSize() const
        {
            uint64_t totalTableSize = 0;

            for(std::pair<std::string, std::string> pair : compressionTable)
            {
                totalTableSize += pair.first.size() + pair.second.size() * 8;
            }
            
            return totalTableSize + initialBitSize;
        }
    };

    /* Implementa a compressão do texto
     * Separa o texto a partir de um separador (palavras = ' ', letras = '\0')
     * Para cada unidade de texto separada, é contada a frequência e criado um nó
     * A árvore então é criada de acordo com as especificações do algoritmo
     * A partir da árvore, é montada a tabela de compressão
     * O texto então é comprimido usando os códigos da tabela
     * O texto comprimido é convertido em um vetor de bytes (uint8_t)
     * É retornado todas as informações necessárias para a leitura do arquivo
     */
    CompressorOutput CompressData(const std::string& text, char separator = ' ');

    /* Implementa a descompressão do texto
     * Recebe a tabela de compressão e o texto em bytes
     * Converte o texto de bytes para uma string em binário
     * Vai lendo a string até casar com um dos códigos da tabela
     * Limpa o código atual e concatena o texto decodificado no final
     * Caso seja compressão por palavras, adiciona um espaço entre eles
     */    
    std::string DecompressData(CompressorOutput& data);
}
