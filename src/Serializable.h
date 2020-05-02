#ifndef __SERIALIZABLE_H
#define __SERIALIZABLE_H

#include <cstring>
#include <iostream>

class Serializable
{
public:
    virtual bool serialize(std::ofstream& output) const = 0;
    virtual bool deserialize(std::ifstream& input) = 0;
    virtual void print() const = 0;

    static Serializable* readSerializable(std::ifstream &input);
    static bool writeSerializable(std::ofstream& output, Serializable* serializable);

    virtual ~Serializable() {};
};

bool writeStringToBinaryFile(std::ofstream& output, const std::string& str);
bool readStringFromBinary(std::ifstream& input, std::string& str);

#endif