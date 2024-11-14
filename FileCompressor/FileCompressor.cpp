#include <iostream>
#include <string>

#include "Compressor.h"
#include "FileHandler.h"

int main()
{
    std::cout << "Insira o caminho do arquivo: ";
    
    std::string filePath;
    std::getline(std::cin, filePath);

    FileHandler fileHandler(filePath);
    std::string loadedData = fileHandler.LoadFile();
    
    Compressor compressor;
    const std::string& compressedData = compressor.CompressData(loadedData);

    fileHandler.SaveFile(compressedData);
}
