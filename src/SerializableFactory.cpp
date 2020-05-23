#ifndef __SERIALIZABLE_FACTORY_CPP
#define __SERIALIZABLE_FACTORY_CPP

#include "SerializableFactory.h"
#include "Serializable.h"
#include "Book.h"
#include "User.h"
#include "Constants.h"

const char* InvalidSerializableObjectSignatureExcpection::what() const noexcept
{
    return this->message.c_str();
}

Serializable* SerializableFactory::generate(std::string signature)
{
    Serializable* serializable = nullptr;
    
    if (signature == BOOK_OBJECT_SIGNATURE)
        serializable = new Book();
    else if (signature == USER_OBJECT_SIGNATURE)
        serializable = new User();
    else 
        throw InvalidSerializableObjectSignatureExcpection("Ivanlid object signature " + signature + " !");

    return serializable;
}

#endif