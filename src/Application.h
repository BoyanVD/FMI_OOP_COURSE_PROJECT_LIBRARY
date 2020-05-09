#ifndef __APPLICATION_H
#define __APPLICATION_H

#include "FileController.h"
#include "User.h"
#include "Constants.h"

#include <vector>

/*
* @TODO - Think of implementing serialization, user deletion via Visitor pattern.
* @TODO - Must add isDeleted field to Serializable class.
* @TODO - Think of Doing the command parsing via Command class.
*/
class Application {
private:
    FileController booksFileController;
    FileController usersFileController;
    User* loggedUser; // shouldn't be deleted in desctructor as it always points to user from (std::vector<User> users)

    bool open(std::string filepath);
    bool close();
    bool save();
    bool saveas(std::string path);
    void help();

    bool booksAll();
    bool booksInfo(unsigned id);
    bool booksFind(std::string option, std::string optionString);
    bool booksSort(std::string option, std::string order); // order \in {asc, desc}

    bool login(std::string username, std::string password);
    bool logout();

    bool usersAdd(std::string username, std::string password, bool isAdmin);
    bool usersRemove(std::string username);

    bool isThereSuchUsername(std::string username);

public:
    Application() : loggedUser(nullptr), usersFileController(USERS_FILE_NAME) {};

    void run();
};

#endif