#ifndef __SERIALIZABLE_FACTORY_CPP
#define __SERIALIZABLE_FACTORY_CPP

#include "SerializableFactory.h"
#include "Serializable.h"
#include "Book.h"
#include "Constants.h"

Serializable* SerializableFactory::generate(std::string signature)
{
    Serializable* serializable = nullptr;
    
    if (signature == BOOK_OBJECT_SIGNATURE)
        serializable = new Book();
    else 
        std::cout << "Ivanlid object signature !" << std::endl;

    return serializable;
}

#endif