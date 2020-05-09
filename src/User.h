#ifndef __USER_H
#define __USER_H

#include <string>
#include <fstream>
#include "Serializable.h"

class User : public Serializable
{
private:
    std::string username;
    std::string password;
    bool isAdmin;
    bool isDeleted;
public:
    User() : username(""), password(""), isAdmin(false), isDeleted(false) {};
    User(const std::string& _username, const std::string& _password, bool _isAdmin, bool _isDeleted) : 
    username(_username), password(_password), isAdmin(_isAdmin), isDeleted(_isDeleted) {};

    std::string getUsername() const
    {
        return username;
    }

    std::string getPassword() const
    {
        return password;
    }

    bool isUserAdmin() const
    {
        return isAdmin;
    }

    bool isUserDeleted() const
    {
        return isDeleted;
    }

    bool serialize(std::ostream& output) const;
    bool deserialize(std::istream& input);

    void printForAll() const;
    void printDetails() const;

    bool del(std::fstream& file);
    bool add(std::fstream& file);
};

#endif