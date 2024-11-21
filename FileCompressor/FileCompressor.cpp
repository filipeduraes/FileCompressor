#include <iostream>
#include <string>
#include <cstdlib>

#include "Compressor.h"
#include "FileHandler.h"

int main()
{
    std::cout << "Deseja comprimir (0) ou descomprimir (1) o arquivo? ";
    int choice = -1;

    while(choice != 0 && choice != 1)
    {
        std::cin >> choice;
    }

    std::cout << "Insira o caminho do arquivo: \n";
    std::string filePath;
    std::getline(std::cin >> std::ws, filePath);

    FileHandler fileHandler(filePath);
    
    switch(choice)
    {
        case 0:
        {
            const std::string loadedData = fileHandler.LoadTextFile();
            const Compressor::CompressorOutput compressorOutput = Compressor::CompressData(loadedData);

            if(compressorOutput.initialBitSize == 0)
            {
                std::cerr << "Falha na compressao.";
                return EXIT_FAILURE;
            }
                
            fileHandler.SaveBinaryFile(compressorOutput);
            break;
        }
        case 1:
        {
            Compressor::CompressorOutput loadedData = fileHandler.LoadBinaryFile();
            const std::string decompressedData = DecompressData(loadedData);

            if(decompressedData.empty())
            {
                std::cerr << "Falha na descompressao.";
                return EXIT_FAILURE;
            }
                
            fileHandler.SaveTextFile(decompressedData);
            break;
        }
        default:
        {
            std::cerr << "Escolha de operacao (" << choice << ") invalida.";
            return EXIT_FAILURE;
        }
    }
    
    return EXIT_SUCCESS;
}
