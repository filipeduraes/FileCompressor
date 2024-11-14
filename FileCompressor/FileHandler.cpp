#include "FileHandler.h"

FileHandler::FileHandler(std::string filePath)
    : path(std::move(filePath))
{
}

void FileHandler::SaveFile(std::string data)
{
}

std::string FileHandler::LoadFile()
{
    return "";
}
