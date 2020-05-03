#ifndef __USER_CPP
#define __USER_CPP

#include <string>

class User 
{
private:
    std::string username;
    std::string password;
    bool isAdmin;
public:
    User() : username(""), password(""), isAdmin(false) {};
    User(const std::string& _username, const std::string& _password, bool _isAdmin) : username(_username), password(_password), isAdmin(_isAdmin) {};

    std::string getUsername()
    {
        return username;
    }

    std::string getPassword()
    {
        return password;
    }

    bool isUserAdmin()
    {
        return isAdmin;
    }
};

#endif