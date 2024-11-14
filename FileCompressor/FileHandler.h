#pragma once
#include <string>

class FileHandler
{
private:
    std::string path;
    
public:
    FileHandler(std::string filePath);
    
    void SaveFile(std::string data);
    std::string LoadFile();
};
