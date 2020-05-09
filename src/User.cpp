#ifndef __USER_CPP
#define __USER_CPP

#include <iostream>
#include <cstring>
#include <vector>
#include <fstream>

#include "Constants.h"
#include "User.h"

bool User::serialize(std::ostream& output) const
{
    if (!(writeStringToBinaryFile(output, USER_OBJECT_SIGNATURE) &&
        writeStringToBinaryFile(output, username) &&
        writeStringToBinaryFile(output, password)))
    {
        return false;
    }

    output.write((char*)&isAdmin, sizeof(isAdmin));
    output.write((char*)&isDeleted, sizeof(isDeleted));

    return output.good();
}

bool User::deserialize(std::istream& input)
{
    if (!(readStringFromBinary(input, username) &&
        readStringFromBinary(input, password)))
    {
        return false;
    }

    input.read((char*)&isAdmin, sizeof(isAdmin));
    input.read((char*)&isDeleted, sizeof(isDeleted));

    return input.good();
}

void User::printForAll() const
{
    std::cout << username << std::endl;
}

void User::printDetails() const
{
    std::cout << username << std::endl
            << password << std::endl
            << isAdmin << std::endl
            << isDeleted << std::endl;
}

bool User::del(std::fstream& file)
{
    int position;
  
    while (!file.eof()) { 
        position = file.tellg(); 
  
        // user.deserialize(file);
        User* user = dynamic_cast<User*>(Serializable::readSerializable(file));
        if(user == nullptr)
        {
            std::cout << "Problem while reading user !" << std::endl;
            return false;
        }
        
        if (file) {
            if (user->getUsername() == this->username) {
                this->isDeleted = true;
                file.seekp(position);
                serialize(file);

                std::cout << "User " << this->username << " successfully deleted !" << std::endl;
                return true;
            } 
        } 
    }

    std::cout << "Cannot delete user " << this->username << std::endl;
    return false;
}

bool User::add(std::fstream& file)
{
    int position;
  
    while (!file.eof()) { 
        position = file.tellg(); 

        User* user = dynamic_cast<User*>(Serializable::readSerializable(file));
        if(user == nullptr)
        {
            break;
        }
        
        if (file) {
            if (user->isUserDeleted()) {
                file.seekp(position);
                serialize(file);

                std::cout << "User " << this->username << " successfully added !" << std::endl;
                return true;
            } 
        } 
    }

    std::ofstream out(USERS_FILE_NAME, std::ios::app | std::ios::binary);
    Serializable::writeSerializable(out, this);
    out.close();

    return true;
}

#endif