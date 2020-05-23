#ifndef __SERIALIZABLE_FACTORY_H
#define __SERIALIZABLE_FACTORY_H

#include "Serializable.h"
#include <iostream>
#include <string>
#include <exception>

class InvalidSerializableObjectSignatureExcpection : public std::exception
{
private:
    std::string message;
public:
    InvalidSerializableObjectSignatureExcpection(const std::string& _message) : std::exception(), message(_message) {}
    const char* what() const noexcept;
};

class SerializableFactory
{
public:
    static Serializable* generate(std::string signature);
};

#endif