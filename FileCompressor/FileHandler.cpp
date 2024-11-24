#include "LoadFileHandler.h"
#include "SaveFileHandler.h"
#include "FileHandler.h"

FileHandler::FileHandler(const std::string& filePath)
    : path(filePath)
{
}

void FileHandler::SaveTextFile(const std::string& data) const
{
    SaveFileHandler saveFileHandler(path);
    saveFileHandler.SaveTextFile(data);
}

void FileHandler::SaveBinaryFile(const Compressor::CompressorOutput& data) const
{
    SaveFileHandler saveFileHandler(path);
    saveFileHandler.SaveBinaryFile(data);
}

std::string FileHandler::LoadTextFile() const
{
    LoadFileHandler loadFileHandler(path);
    return loadFileHandler.LoadTextFile();
}

Compressor::CompressorOutput FileHandler::LoadBinaryFile() const
{
    LoadFileHandler loadFileHandler(path);
    return loadFileHandler.LoadBinaryFile();
}

