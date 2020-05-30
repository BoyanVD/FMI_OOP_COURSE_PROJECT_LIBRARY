#ifndef __SIMPLE_ENCRYPTOR_CPP
#define __SIMPLE_ENCRYPTOR_CPP

#include "SimpleEncryptor.h"

std::string SimpleEncryptor::encryptDecrypt(const std::string& str) const
{
    std::string result = str;
    
    for (int i = 0; i < str.size(); i++)
    {
        result[i] = str[i] ^ this->key[i % (this->key.size())];
    }
    
    return result;
}

std::string SimpleEncryptor::encrypt(const std::string& str) const
{
    return this->encryptDecrypt(str);
}

std::string SimpleEncryptor::decrypt(const std::string& str) const
{
    return this->encryptDecrypt(str);
}


#endif