#include <iostream>
#include <string>

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

    std::cout << "Insira o caminho do arquivo: ";
    std::string filePath;
    std::getline(std::cin, filePath);
    
    FileHandler fileHandler = filePath;
    
    switch(choice)
    {
    case 0:
        {
            const std::string loadedData = fileHandler.LoadTextFile();
            const Compressor::CompressorOutput compressorOutput = Compressor::CompressData(loadedData);
            fileHandler.SaveBinaryFile(compressorOutput);
            break;
        }
    case 1:
        {
            Compressor::CompressorOutput loadedData = fileHandler.LoadBinaryFile();
            const std::string decompressedData = DecompressData(loadedData);
            fileHandler.SaveTextFile(decompressedData);
            break;
        }
    }
}
