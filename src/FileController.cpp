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

/*
*   Adds file item to the file controller items vector, after serializing it in the file. It looks for the first
* item in the file that has true value for the isDelete attribute. Otherwise it serializes it at the end of the file.
*/
void FileController::addFileItem(Serializable* item)
{
     std::fstream file; 
    file.open(filepath, std::ios::in | std::ios::binary | std::ios::out);

     if (item->add(file))
     {
         this->fileItems.push_back(item);
     }
     file.close();
}

void FileController::removeFileItem(std::function<bool(Serializable*)> pred)
{
    std::fstream file; 
    file.open(filepath, std::ios::in | std::ios::binary | std::ios::out);

    for (int index = 0; index < fileItems.size(); ++index)
    {
        if (pred(fileItems[index]))
        {
            if (fileItems[index]->del(file))
            {
                fileItems.erase(fileItems.begin() + index);
            }
        }
    }

    file.close();
}

#endif