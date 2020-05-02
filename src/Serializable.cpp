#ifndef __SERIALIZABLE_CPP
#define __SERIALIZABLE_CPP

#include "Serializable.h"
#include "SerializableFactory.h"

#include <fstream>
#include <cstring>

Serializable* Serializable::readSerializable(std::ifstream &input)
{
    std::string signature;
    if (!readStringFromBinary(input, signature))
    {
        return nullptr;
    }

    Serializable* serializable = SerializableFactory::generate(signature);
    serializable->deserialize(input);

    return serializable;

}

static bool writeSerializable(std::ofstream& output, Serializable* serializable)
{
    return serializable->serialize(output);
}

bool writeStringToBinaryFile(std::ofstream& output, const std::string& str)
{
    size_t size = str.size();
    output.write((char*)&size, sizeof(size));
    output.write(&str[0], size);

    return output.good();
}

bool readStringFromBinary(std::ifstream& input, std::string& str)
{
    size_t size;
    input.read((char*)&size, sizeof(size));
    if (!input)
        return false;
        
    str.resize(size);
    input.read(&str[0], size);

    return input.good();
}

#endif