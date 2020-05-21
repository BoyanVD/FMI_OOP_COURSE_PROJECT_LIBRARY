#ifndef __SERIALIZABLE_FACTORY_H
#define __SERIALIZABLE_FACTORY_H

#include "Serializable.h"
#include <iostream>
#include <string>

class SerializableFactory
{
public:
    static Serializable* generate(std::string signature);
};

#endif