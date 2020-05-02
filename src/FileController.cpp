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

std::vector<Serializable*> FileController::open() 
{
    std::ifstream input(filepath, std::ios::binary);
    
    while(!input.eof())
    {
        Serializable* serializable = Serializable::readSerializable(input);
        if (serializable == nullptr)
            break;

        this->fileItems.push_back(serializable);
    }

    input.close();
    return this->fileItems;
}

bool FileController::save()
{
    std::ofstream output(filepath, std::ios::binary);
    for (Serializable* serializable : fileItems)
    {
        if (!serializable->serialize(output))
            return false;
    }

    output.close();
    return true;
}

#endif