/**
 * \class Application
 *
 * \brief The application driving class
 *
 * This is the class, where most of the application features
 * and functionality is maneged. It contains most of the
 * business logic as well.
 *
 * \author $Author: Boyan Dafov $
 * 
 * Contact: boyandafov123@gmail.com
 *
 */
#ifndef __APPLICATION_H
#define __APPLICATION_H

#include "FileController.h"
#include "User.h"
#include "Constants.h"
#include "Command.h"
#include "SimpleEncryptor.h"

#include <map>
#include <string>
#include <vector>

using BookComparator = bool (*) (Serializable*, Serializable*);
using BooksPredicate = bool (*) (Serializable*, std::string);

class Application 
{
private:
    /**
    * Predicate map, used for getting predicate function by option string.
    */
    static const std::map<std::string, BooksPredicate> PREDICATE_MAP;

    /**
    * Book comparators map, used for getting compare function by option string.
    */
    static const std::map<std::string, BookComparator> BOOK_COMPARATORS_MAP;

    /**
    * Map, used as dictionary, giving information about the amount of parameters, that
    * every function accepts. Used only for validation.
    */
    static const std::map<std::string, std::vector<unsigned>> COMMAND_NUMBER_OF_PARAMETERS_MAP;

    /**
    * Encryptor, used for password encryption, when user logs in, or when 
    * the system adds new user. The idea is not to store the actual passwords in file.
    */
    static const SimpleEncryptor ENCRYPTOR;

    typedef void (Application::*Function)(const Command&);
    /**
    * Supported functions map.
    */
    static const std::map<std::string, Function> SUPPORTED_FUNCTIONS;

    /**
    * File controller, used for book entities management.
    */
    FileController booksFileController;

    /**
    * File controller, used for user entities management.
    */
    FileController usersFileController;

    /**
    * Stores pointer to the currently logged user.
    */
    User* loggedUser;

    /**
    * Loads the information from file given, into the system.
    *
    * @param command The user input parsed command.
    */
    void open(const Command& command);

    /**
    * Closes the currently opened file.
    *
    * @param command The user input parsed command.
    */
    void close(const Command& command);

    /**
    * Save the changes made into the initial file.
    *
    * @param command The user input parsed command.
    */
    void save(const Command& command);

    /**
    * Save the changes made into the file provided.
    *
    * @param command The user input parsed command.
    */
    void saveas(const Command& command);

    /**
    * Shows system's functionality information.
    *
    * @param command The user input parsed command.
    */
    void help(const Command& command);

    /**
    * Shows brief information about all books, that are currently  loaded.
    *
    * @param command The user input parsed command.
    */
    void booksAll(const Command& command);

    /**
    * Shows detailed information, about the books with id given in command parameter.
    *
    * @param command The user input parsed command.
    */
    void booksInfo(const Command& command);

    /**
    * Shows all books, that satisfy condition given in command parameter.
    *
    * @param command The user input parsed command.
    */
    void booksFind(const Command& command);

    /**
    * Sorts all books, currently loaded in system by criteria givem in command parameter. Note that it doesn't show them.
    *
    * @param command The user input parsed command.
    */
    void booksSort(const Command& command); // order \in {asc, desc}

    /**
    * If there is user with username and password given in command parameter, it logs the user in the application.
    *
    * @param command The user input parsed command.
    */
    void login(const Command& command);

    /**
    * It logs out the currently logged user in the application.
    *
    * @param command The user input parsed command.
    */
    void logout(const Command& command);

    /**
    * Adds new user into the system, if there is no such user already.
    *
    * @param command The user input parsed command.
    */
    void usersAdd(const Command& command);

    /**
    * Removes user from the application.
    *
    * @param command The user input parsed command.
    */
    void usersRemove(const Command& command);

    /**
    * Helper function, used for checking if there is such user in system.
    *
    * @param username the username string
    * @return bool, representing the answer of the question, is there such user.
    */
    bool isThereSuchUsername(const std::string& username);

    /**
    * Helper function, used for getting application function by key given
    *
    * @param key the key string
    */
    Function getFunction(const std::string key);
    bool validateCommand(const Command& command);

public:
    Application() : loggedUser(nullptr), usersFileController(USERS_FILE_NAME) {};

    /**
    * The Application run method.
    */
    void run();
};

#endif