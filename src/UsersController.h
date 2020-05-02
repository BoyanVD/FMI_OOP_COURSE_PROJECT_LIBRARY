#ifndef __USERSCONTROLLER_H
#define __USERSCONTROLLER_H

#include<vector>
#include<string>
#include "User.h"

class UsersController {
    private:
    std::string fileName;
    public:
    UsersController();

    // It could be getUser(), and login in application
    User login(const std::string username, const std::string password) const;
    
    bool usersAdd(const std::string username, const std::string password) const;

    bool usersRemove(const std::string username) const;
};

#endif