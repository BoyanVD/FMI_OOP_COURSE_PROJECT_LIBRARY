#ifndef __SERIALIZABLE_CPP
#define __SERIALIZABLE_CPP

#include "Serializable.h"
#include "SerializableFactory.h"

// #include <fstream>
// #include <string>

Serializable* Serializable::readSerializable(std::istream &input)
{
    std::string signature;
    if (!readStringFromBinary(input, signature))
    {
        return nullptr;
    }

    Serializable* serializable = nullptr;

    try
    {
        serializable = SerializableFactory::generate(signature);
        serializable->deserialize(input);
    }
    catch(const InvalidSerializableObjectSignatureExcpection& e)
    {
        std::cout << e.what() << std::endl;
    }

    return serializable;
}

bool Serializable::writeSerializable(std::ostream& output, Serializable* serializable)
{
    return serializable->serialize(output);
}

bool writeStringToBinaryFile(std::ostream& output, const std::string& str)
{
    size_t size = str.size();
    output.write((char*)&size, sizeof(size));
    output.write(&str[0], size);

    return output.good();
}

bool readStringFromBinary(std::istream& input, std::string& str)
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