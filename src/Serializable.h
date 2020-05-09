#ifndef __SERIALIZABLE_H
#define __SERIALIZABLE_H

#include <cstring>
#include <iostream>

class Serializable
{
public:
    virtual bool serialize(std::ostream& output) const = 0;
    virtual bool deserialize(std::istream& input) = 0;

    virtual void printForAll() const = 0;
    virtual void printDetails() const = 0;
    virtual bool del(std::fstream& file) = 0;
    virtual bool add(std::fstream& file) = 0;

    static Serializable* readSerializable(std::istream &input);
    static bool writeSerializable(std::ostream& output, Serializable* serializable);

    virtual ~Serializable() {};
};

bool writeStringToBinaryFile(std::ostream& output, const std::string& str);
bool readStringFromBinary(std::istream& input, std::string& str);

#endif