#ifndef __SERIALIZABLE_FACTORY_H
#define __SERIALIZABLE_FACTORY_H

#include "Serializable.h"

class SerializableFactory
{
public:
    static Serializable* generate(std::string signature);
};

#endif