#ifndef __SIMPLE_ENCRYPTOR_H
#define __SIMPLE_ENCRYPTOR_H

#include <iostream>
#include <string>

/*
 * Simple XOR encryption and decryption. Not pretending for huge safety, implemented it about the idea :)
 */
class SimpleEncryptor
{
private:
    std::string key;

    std::string encryptDecrypt(const std::string& str) const;
public:
    SimpleEncryptor(const std::string& _key) : key(_key) {}
    ~SimpleEncryptor() {}

    std::string encrypt(const std::string& str) const;
    std::string decrypt(const std::string& str) const;
};


#endif