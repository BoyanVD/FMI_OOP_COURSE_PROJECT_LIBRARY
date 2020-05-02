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

    // std::string signature;
    // while(readStringFromBinary(input, signature))
    // {
    //     Serializable* serializable = SerializableFactory::generate(signature);
    //     if (serializable == nullptr)
    //         std::cout << "Invalid object type in binary file !" << std::endl;
    //     serializable->deserialize(input);
    //     this->fileItems.push_back(serializable);
    // }
    
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

#endif