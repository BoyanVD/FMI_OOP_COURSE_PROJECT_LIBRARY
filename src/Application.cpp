#ifndef __APPLICATION_CPP
#define __APPLICATION_CPP

#include "Application.h"
#include "FileController.h"
#include "Constants.h"
#include "Book.h"
#include "Sorter.h"

const std::map<std::string, Application::Function> Application::SUPPORTED_FUNCTIONS = {
    {"open", &Application::open},
    {"close", &Application::close},
    {"save", &Application::save},
    {"saveas", &Application::saveas},
    {"help", &Application::help},
    {"books_all", &Application::booksAll},
    {"books_info", &Application::booksInfo},
    {"books_find", &Application::booksFind},
    {"books_sort", &Application::booksSort},
    {"login", &Application::login},
    {"logout", &Application::logout},
    {"users_add", &Application::usersAdd},
    {"users_remove", &Application::usersRemove}
};

// Vector, because some of the commands number of parameters may vary
const std::map<std::string, std::vector<unsigned>> Application::COMMAND_NUMBER_OF_PARAMETERS_MAP = {
    {"open", {1}},
    {"close", {0}},
    {"save", {0}},
    {"saveas", {1}},
    {"help", {0}},
    {"exit", {0}},
    {"books_all", {0}},
    {"books_info", {1}},
    {"books_find", {2}}, // Books find is a little bit different
    {"books_sort", {2, 3}},
    {"login", {2}},
    {"logout", {0}},
    {"users_add", {2}},
    {"users_remove", {1}}
};

const std::map<std::string, BooksPredicate> Application::PREDICATE_MAP = {
    {"title", [](Serializable* book, std::string str)->bool{return dynamic_cast<Book*>(book)->getTitle() == str;}},
    {"author", [](Serializable* book, std::string str)->bool{return dynamic_cast<Book*>(book)->getAuthor() == str;}},
    {"tag", [](Serializable* book, std::string str)->bool{return dynamic_cast<Book*>(book)->hasTag(str);}}
};

const std::map<std::string, BookComparator> Application::BOOK_COMPARATORS_MAP = {
    {"title asc", [](Serializable* book1, Serializable* book2)->bool{return ((Book*)book1)->getTitle() < ((Book*)book2)->getTitle();}},
    {"title desc", [](Serializable* book1, Serializable* book2)->bool{return ((Book*)book1)->getTitle() > ((Book*)book2)->getTitle();}},

    {"author asc", [](Serializable* book1, Serializable* book2)->bool{return ((Book*)book1)->getAuthor() < ((Book*)book2)->getAuthor();}},
    {"author desc", [](Serializable* book1, Serializable* book2)->bool{return ((Book*)book1)->getAuthor() > ((Book*)book2)->getAuthor();}},

    {"year asc", [](Serializable* book1, Serializable* book2)->bool{return ((Book*)book1)->getYear() < ((Book*)book2)->getYear();}},
    {"year desc", [](Serializable* book1, Serializable* book2)->bool{return ((Book*)book1)->getYear() > ((Book*)book2)->getYear();}},

    {"rating asc", [](Serializable* book1, Serializable* book2)->bool{return ((Book*)book1)->getRating() < ((Book*)book2)->getRating();}},
    {"rating desc", [](Serializable* book1, Serializable* book2)->bool{return ((Book*)book1)->getRating() > ((Book*)book2)->getRating();}}
};

bool Application::validateCommand(const Command& command)
{
    std::map<std::string, std::vector<unsigned>>::const_iterator it = COMMAND_NUMBER_OF_PARAMETERS_MAP.find(command.getCommand());
    if (it == COMMAND_NUMBER_OF_PARAMETERS_MAP.end())
    {
        std::cout << "No such command supported !" << std::endl;
        return false;
    }

    std::vector<unsigned> parametersAllowed =  it->second;
    unsigned commandNumberOfParameters = command.getNumberOfParameters();

    for (unsigned numberOfParameters : parametersAllowed)
    {
        if (numberOfParameters == commandNumberOfParameters)
            return true;
    }

    return false;
}

Application::Function Application::getFunction(const std::string key)
{
    std::map<std::string, Application::Function>::const_iterator it = SUPPORTED_FUNCTIONS.find(key);
    if (it == SUPPORTED_FUNCTIONS.end())
    {
        if (key != "exit")
            std::cout << "Invalid command !" << std::endl;
        return nullptr;
    }

    return it->second;
}

void Application::help(const Command& command)
{
    if (!validateCommand(command))
    {
        std::cout << "Inalid number of parameters for command 'help' !" << std::endl;
        return;
    }

    std::cout << "Supported commands : " << std::endl;
}

/*
* TODO - Serializable derived classes must implement copy() method, returning reference to an instance through base class
*/
void Application::login(const Command& command) //username, password
{
    if (!validateCommand(command))
    {
        std::cout << "Inalid number of parameters for command 'login' !" << std::endl;
        return;
    }

    if (loggedUser != nullptr)
    {
        std::cout << "You are already logged in !" << std::endl;
        return;
    }

    std::vector<Serializable*> users = usersFileController.getFileItems();
    for (Serializable* user : users)
    {
        User* parsedPointer = dynamic_cast<User*>(user);
        //Think about checking for nullptr

        if ((parsedPointer->getUsername() == command.getParameter(0)) && (parsedPointer->getPassword() == command.getParameter(1)))
            loggedUser = parsedPointer;
    }

    if (loggedUser == nullptr)
    {
        std::cout << "Wrong username or password !" << std::endl;
        return;
    }

    std::cout << "Welcome, " << command.getParameter(0) << " !" << std::endl;
}

void Application::logout(const Command& command)
{
    if (!validateCommand(command))
    {
        std::cout << "Inalid number of parameters for command 'logout' !" << std::endl;
        return;
    }

    if (loggedUser == nullptr)
    {
        std::cout << NOT_LOGGED_IN_MESSAGE << std::endl;
        return;
    }

    loggedUser = nullptr;
    std::cout << "You successfully logged out !" << std::endl;
}

void Application::open(const Command& command)
{
    if (!validateCommand(command))
    {
        std::cout << "Inalid number of parameters for command 'open' !" << std::endl;
        return;
    }

    booksFileController.setFilepath(command.getParameter(0));
    if (!booksFileController.open())
    {
        std::cout << "Unsuccessfull file opening !" << std::endl;
        return;
    }

    std::cout << "Successfully opened " << command.getParameter(0) << std::endl;
}

void Application::close(const Command& command)
{
    if (!validateCommand(command))
    {
        std::cout << "Inalid number of parameters for command 'close' !" << std::endl;
        return;
    }

    booksFileController.close();
}

void Application::save(const Command& command)
{
    if (!validateCommand(command))
    {
        std::cout << "Inalid number of parameters for command 'save' !" << std::endl;
        return;
    }

    booksFileController.save();
}

void Application::saveas(const Command& command)
{
    if (!validateCommand(command))
    {
        std::cout << "Inalid number of parameters for command 'saveas' !" << std::endl;
        return;
    }

    booksFileController.saveas(command.getParameter(0));
}

void Application::booksAll(const Command& command)
{
    if (!validateCommand(command))
    {
        std::cout << "Inalid number of parameters for command 'books_all' !" << std::endl;
        return;
    }

    if (loggedUser == nullptr)
    {
        std::cout << NOT_LOGGED_IN_MESSAGE << std::endl;
        return;
    }

    std::vector<Serializable*> items = booksFileController.getFileItems();
    for (Serializable* item : items)
    {
        item->printForAll();
    }
}

void Application::booksInfo(const Command& command)
{
    if (!validateCommand(command))
    {
        std::cout << "Inalid number of parameters for command 'books_info' !" << std::endl;
        return;
    }

    if (loggedUser == nullptr)
    {
        std::cout << NOT_LOGGED_IN_MESSAGE << std::endl;
        return;
    }

    unsigned id = 0;
    try
    {
        id = std::stoi(command.getParameter(0));
    }
    catch(const std::invalid_argument& ia)
    {
        std::cout << "Invalid argument !" << std::endl;
        return;
    }

    for (Serializable* item : booksFileController.getFileItems())
    {
        Book* currentBook = (Book*) item;
        if (currentBook->getId() == id)
        {
            currentBook->printDetails();
            return;
        }
    }

    std::cout << "There is no book with id " << id << std ::endl;
}

void Application::booksFind(const Command& command) //option, optionString
{
    if (loggedUser == nullptr)
    {
        std::cout << NOT_LOGGED_IN_MESSAGE << std::endl;
        return;
    }

    std::map<std::string, BooksPredicate>::const_iterator it = PREDICATE_MAP.find(command.getParameter(0));
    if (it == PREDICATE_MAP.end())
    {
        std::cout << "Invalid books find option ! " << std::endl;
        return;
    }
    
    BooksPredicate pred = it->second;
    std::string optionString = command.getCancatenatedParameters(1, command.getNumberOfParameters() - 1);

    for (Serializable* item : booksFileController.getFileItems())
    {
        Book* currentBook = (Book*) item;
        if (pred(currentBook, optionString))
        {
            currentBook->printDetails();
        }
    }
}

void Application::booksSort(const Command& command) // option, order
{
    if (!validateCommand(command))
    {
        std::cout << "Inalid number of parameters for command 'books_sort' !" << std::endl;
        return;
    }

    if (loggedUser == nullptr)
    {
        std::cout << NOT_LOGGED_IN_MESSAGE << std::endl;
        return;
    }

    std::string key = command.getParameter(0) + " " + command.getParameter(1);
    std::map<std::string, BookComparator>::const_iterator it = BOOK_COMPARATORS_MAP.find(key);
    if (it == BOOK_COMPARATORS_MAP.end())
    {
        std::cout << "Invalid books sort option ! " << std::endl;
        return;
    }

    Sorter<Serializable*> sorter;
    sorter.sort(this->booksFileController.getFileItems(), it->second);
}

// TODO - Update logic to write user on top of deleted, must probably add isDeleted to Serializable
void Application::usersAdd(const Command& command) // username, password, isAdmin
{
    if (!validateCommand(command))
    {
        std::cout << "Inalid number of parameters for command 'users_add' !" << std::endl;
        return;
    }

    if (isThereSuchUsername(command.getParameter(0)))
    {
        std::cout << "Username taken !" << std::endl;
        return;
    }

    bool isAdmin = command.getParameter(2) == "1";
    Serializable* user = new User(command.getParameter(0), command.getParameter(1), isAdmin, false);
    usersFileController.addFileItem(user);
}

void Application::usersRemove(const Command& command)
{
    if (!validateCommand(command))
    {
        std::cout << "Inalid number of parameters for command 'users_remove' !" << std::endl;
        return;
    }

    if (loggedUser == nullptr)
    {
        std::cout << NOT_LOGGED_IN_MESSAGE << std::endl;
        return;
    }

    if (!loggedUser->isUserAdmin())
    {
        std::cout << NOT_ADMIN_MESSAGE << std::endl;
        return;
    }


    if (!isThereSuchUsername(command.getParameter(0)))
    {
        std::cout << "No user with such username !" << std::endl;
        return;
    }

    std::string _username = command.getParameter(0);
    usersFileController.removeFileItem([_username](Serializable* user)->bool
    {
        User* userPointer = dynamic_cast<User*>(user);
        return (userPointer->getUsername() == _username);
    });
}

bool Application::isThereSuchUsername(const std::string& username)
{
    std::vector<Serializable*> users = usersFileController.getFileItems();
    for(Serializable* user : users)
    {
        User* userPtr = dynamic_cast<User*>(user);
        if (userPtr->getUsername() == username)
            return true;
    }

    return false;
}

void Application::run()
{
    // User* initialUser = new User(INITIAL_USER_USERNAME, INITIAL_USER_PASSWORD, true, false);
    // this->usersFileController.addFileItem(initialUser);

    std::string initialCommand = "users_add "  + INITIAL_USER_USERNAME + " " + INITIAL_USER_PASSWORD + " 1";
    usersAdd(initialCommand);

    std::string input;
    do
    {
        std::cout << ">";
        getline(std::cin,  input);
        
        Command command(input);
        if (command.getCommand() == "users_add")
            command.addParameter("0"); // you can't add user with role Admin

        Application::Function function = this->getFunction(command.getCommand());
        if (function == nullptr)
            continue;

        (this->*function)(command);

    } while (input != "exit");
    
    std::cout << "Thank you for using the system !" << std::endl;

    // login(INITIAL_USER_USERNAME, INITIAL_USER_PASSWORD);
    // open("./files/books.bin");

    // // logout();
    // // usersRemove(INITIAL_USER_USERNAME);
    // // login(INITIAL_USER_USERNAME, INITIAL_USER_PASSWORD);

    // usersFileController.printAllItems();
    // std::cout << std::endl;

    // usersAdd("BoyanVD", "airbourne2003", false);
    // usersAdd("Gosho", "123456789", false);

    // usersFileController.printAllItems();
    // std::cout << std::endl;

    // usersRemove("Gosho");
    // usersFileController.printAllItems();
    // std::cout << std::endl;

    // usersAdd("Miro", "123456789", false);
    // usersFileController.printAllItems();
    // std::cout << std::endl;

}

#endif