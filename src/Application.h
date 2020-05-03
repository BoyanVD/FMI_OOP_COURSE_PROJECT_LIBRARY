#ifndef __APPLICATION_H
#define __APPLICATION_H

#include "FileController.h"
#include "User.h"

#include <vector>

class Application {
private:
    FileController booksFileController;
    User* loggedUser; // shouldn't be deleted in desctructor as it always points to user from (std::vector<User> users)
    std::vector<User> users;

    bool open(std::string filepath);
    bool close();
    bool save();
    bool saveas(std::string path);
    void help();

    bool booksAll();
    bool booksInfo(unsigned id);
    bool booksFind(std::string option, std::string optionString);

    bool login(std::string username, std::string password);
    bool logout();

public:
    Application() : loggedUser(nullptr) {};

    void run();
};

#endif