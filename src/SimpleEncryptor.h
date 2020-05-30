/**
 * \class SimpleEncryptor
 *
 * \brief Simple encryption class.
 *
 * Implements simple encryption algorithm, called XOR Encryption.
 * Not pretending for huge safety, but implements the idea of not
 * storing the 'actural' information in files.
 *
 * \author $Author: Boyan Dafov $
 * 
 * Contact: boyandafov123@gmail.com
 *
 */
#ifndef __SIMPLE_ENCRYPTOR_H
#define __SIMPLE_ENCRYPTOR_H

#include <iostream>
#include <string>

class SimpleEncryptor
{
private:

    /**
     * The key used by the encryption and decryption algorithm.
     */
    std::string key;

    /**
     * The encryption and decryption algorithm. In this algorithm's
     * case they are the same, but keeping them in different functions,
     * in order to keep class interface more intuitive.
     * 
     * @param str the string to transform
     * @return the transformed string
     */
    std::string encryptDecrypt(const std::string& str) const;
public:
    SimpleEncryptor(const std::string& _key) : key(_key) {}
    ~SimpleEncryptor() {}

    /**
     * The encryption algorithm. In this algorithm's
     * case they are the same, but keeping them in different functions,
     * in order to keep class interface more intuitive.
     * 
     * @param str the string to encrypt
     * @return the encrypted string
     */
    std::string encrypt(const std::string& str) const;

    /**
     * The decryption algorithm. In this algorithm's
     * case they are the same, but keeping them in different functions,
     * in order to keep class interface more intuitive.
     * 
     * @param str the string to decrypt
     * @return the decrypted string
     */
    std::string decrypt(const std::string& str) const;
};


#endif