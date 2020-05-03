#ifndef __FILECONTROLLER_CPP
#define __FILECONTROLLER_CPP

#include <iostream>
#include <vector>
#include <string>
#include <fstream>

#include "FileController.h"
#include "Serializable.h"
#include "SerializableFactory.h"

FileController::~FileController()
{
    for (Serializable* serializable : fileItems)
    {
        delete serializable;
    }
}

bool FileController::open() 
{
    if (isFileOpened)
    {
        std::cout << "You have opened file already !" << std::endl;
        return false;
    }

    std::ifstream input(filepath, std::ios::binary);
    
    while(!input.eof())
    {
        Serializable* serializable = Serializable::readSerializable(input);
        if (serializable == nullptr)
            break;

        this->fileItems.push_back(serializable);
    }
    
    input.close();
    return true;
}

bool FileController::save()
{
    if (!isFileOpened)
    {
        std::cout << "You don't have file opened !" << std::endl;
        return false;
    }

    return saveas(filepath);
}

bool FileController::saveas(std::string path)
{
    if (!isFileOpened)
    {
        std::cout << "You don't have file opened !" << std::endl;
        return false;
    }

    std::ofstream output(path, std::ios::binary);
    for (Serializable* serializable : fileItems)
    {
        if (!serializable->serialize(output))
            return false;
    }

    output.close();
    return true;
}

bool FileController::close()
{
    if (!isFileOpened)
    {
        std::cout << "You don't have file opened !" << std::endl;
        return false;
    }

    filepath = "";
    isFileOpened = false;
    deleteFileItems();

    return true;
}

#endif