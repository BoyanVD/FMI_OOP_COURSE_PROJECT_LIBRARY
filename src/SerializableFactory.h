/**
 * \class SerializableFactory
 *
 * \brief Serializable factory design implementation.
 *
 * Used to generate Serializable objects by criteria given.
 *
 * \author $Author: Boyan Dafov $
 * 
 * Contact: boyandafov123@gmail.com
 *
 */
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
    /**
     * Generates Serializable object and returns pointer to it.
     * The criteria is object signature.
     * 
     * @param signature the object signature
     * @return pointer to generated object
     */
    static Serializable* generate(std::string signature);
};

#endif