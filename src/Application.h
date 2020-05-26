#ifndef __APPLICATION_H
#define __APPLICATION_H

#include "FileController.h"
#include "User.h"
#include "Constants.h"
#include "Command.h"

#include <map>
#include <string>
#include <vector>

using BookComparator = bool (*) (Serializable*, Serializable*);
using BooksPredicate = bool (*) (Serializable*, std::string);

/*
* @TODO - Think of implementing serialization, user deletion via Visitor pattern.
* @TODO - Must add isDeleted field to Serializable class.
* @TODO - Think of Doing the command parsing via Command class.
* @TODO - add virtual method 'clone()' to Serializable class, and use it when adding Serializable to vector
* @TODO - Check dynamic memory
* @TODO - Implement Clone idea
* @TODO - Think of inputStream and logStream
*/
class Application {
private:
    static const std::map<std::string, BooksPredicate> PREDICATE_MAP;
    static const std::map<std::string, BookComparator> BOOK_COMPARATORS_MAP;
    static const std::map<std::string, std::vector<unsigned>> COMMAND_NUMBER_OF_PARAMETERS_MAP;

    typedef void (Application::*Function)(const Command&);
    static const std::map<std::string, Function> SUPPORTED_FUNCTIONS;

    FileController booksFileController;
    FileController usersFileController;
    User* loggedUser; // shouldn't be deleted in desctructor as it always points to user from (std::vector<User> users)

    void open(const Command& command);
    void close(const Command& command);
    void save(const Command& command);
    void saveas(const Command& command);
    void help(const Command& command);

    void booksAll(const Command& command);
    void booksInfo(const Command& command);
    void booksFind(const Command& command);
    void booksSort(const Command& command); // order \in {asc, desc}

    void login(const Command& command);
    void logout(const Command& command);

    void usersAdd(const Command& command);
    void usersRemove(const Command& command);

    bool isThereSuchUsername(const std::string& username);

    Function getFunction(const std::string key);
    bool validateCommand(const Command& command);

public:
    Application() : loggedUser(nullptr), usersFileController(USERS_FILE_NAME) {};

    void run();
};

#endif