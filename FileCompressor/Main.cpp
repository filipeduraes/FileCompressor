#include <iostream>
#include <string>
#include <cstdlib>

#include "Compressor.h"
#include "FileHandler.h"

int GetUserInput(std::string& filePath)
{
    std::cout << "Deseja comprimir (0) ou descomprimir (1) o arquivo? ";
    int choice = -1;

    while(choice != 0 && choice != 1)
    {
        std::cin >> choice;
    }

    std::cout << "Insira o caminho do arquivo: \n";
    std::getline(std::cin >> std::ws, filePath);
    return choice;
}

int CompressFile(const FileHandler& fileHandler)
{
    const std::string loadedData = fileHandler.LoadTextFile();
    const Compressor::CompressorOutput compressorOutput = Compressor::CompressData(loadedData);

    if(compressorOutput.initialBitSize == 0)
    {
        std::cerr << "Falha na compressao.";
        return EXIT_FAILURE;
    }
                
    fileHandler.SaveBinaryFile(compressorOutput);
    return EXIT_SUCCESS;
}

int DecompressFile(const FileHandler& fileHandler)
{
    Compressor::CompressorOutput loadedData = fileHandler.LoadBinaryFile();
    const std::string decompressedData = DecompressData(loadedData);

    if(decompressedData.empty())
    {
        std::cerr << "Falha na descompressao.";
        return EXIT_FAILURE;
    }
                
    fileHandler.SaveTextFile(decompressedData);
    return EXIT_SUCCESS;
}

int main()
{
    std::string filePath;
    const int choice = GetUserInput(filePath);
    const FileHandler fileHandler(filePath);
    
    switch(choice)
    {
        case 0:
        {
            return CompressFile(fileHandler);
        }
        case 1:
        {
            return DecompressFile(fileHandler);
        }
        default:
        {
            std::cerr << "Escolha de operacao (" << choice << ") invalida.";
            return EXIT_FAILURE;
        }
    }
}
