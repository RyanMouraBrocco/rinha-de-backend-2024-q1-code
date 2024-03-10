#pragma once

#include <filesystem>
#include <string>

inline void CreateFolderWithNotExists(const std::string &path)
{
    if (!std::filesystem::is_directory(path))
    {
        if (!std::filesystem::create_directories(path))
        {
            // std::cout << "Criou" << std::endl;
        }
    }
}