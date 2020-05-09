#ifndef __APPLICATION_CPP
#define __APPLICATION_CPP

#include <iostream>
#include <map>

#include "Application.h"
#include "FileController.h"
#include "Constants.h"
#include "Book.h"
#include "Sorter.h"

/*
* TODO - Serializable derived classes must implement copy() method, returning reference to an instance through base class
*/
bool Application::login(std::string username, std::string password)
{
    if (loggedUser != nullptr)
    {
        std::cout << "You are already logged in !" << std::endl;
        return false;
    }

    std::vector<Serializable*> users = usersFileController.getFileItems();
    for (Serializable* user : users)
    {
        User* parsedPointer = dynamic_cast<User*>(user);
        //Think about checking for nullptr

        if ((parsedPointer->getUsername() == username) && (parsedPointer->getPassword() == password))
            loggedUser = parsedPointer;
    }

    if (loggedUser == nullptr)
    {
        std::cout << "Wrong username or password !" << std::endl;
        return false;
    }

    std::cout << "Welcome, " << username << " !" << std::endl;
    return true;
}

bool Application::logout()
{
    if (loggedUser == nullptr)
    {
        std::cout << NOT_LOGGED_IN_MESSAGE << std::endl;
        return false;
    }

    loggedUser = nullptr;
    std::cout << "You successfully logged out !" << std::endl;
    return true;
}

bool Application::open(std::string filepath)
{
    booksFileController.setFilepath(filepath);
    if (!booksFileController.open())
    {
        std::cout << "Unsuccessfull file opening !" << std::endl;
        return false;
    }

    std::cout << "Successfully opened " << filepath << std::endl;
    return true;
}

bool Application::close()
{
    return booksFileController.close();
}

bool Application::save()
{
    return booksFileController.save();
}

bool Application::saveas(std::string path)
{
    return booksFileController.saveas(path);
}

bool Application::booksAll()
{
    if (loggedUser == nullptr)
    {
        std::cout << NOT_LOGGED_IN_MESSAGE << std::endl;
        return false;
    }

    std::vector<Serializable*> items = booksFileController.getFileItems();
    for (Serializable* item : items)
    {
        item->printForAll();
    }

    return true;
}

bool Application::booksInfo(unsigned id)
{
    if (loggedUser == nullptr)
    {
        std::cout << NOT_LOGGED_IN_MESSAGE << std::endl;
        return false;
    }

    for (Serializable* item : booksFileController.getFileItems())
    {
        Book* currentBook = (Book*) item;
        if (currentBook->getId() == id)
        {
            currentBook->printDetails();
            return true;
        }
    }

    std::cout << "There is no book with id " << id << std ::endl;
    return false;
}

bool Application::booksFind(std::string option, std::string optionString)
{
    if (loggedUser == nullptr)
    {
        std::cout << NOT_LOGGED_IN_MESSAGE << std::endl;
        return false;
    }

    std::map<std::string, BooksPredicate>::const_iterator it = predicateMap.find(option);
    if (it == predicateMap.end())
    {
        std::cout << "Invalid books find option ! " << std::endl;
        return false;
    }
    
    BooksPredicate pred = it->second;

    for (Serializable* item : booksFileController.getFileItems())
    {
        Book* currentBook = (Book*) item;
        if (pred(currentBook, optionString))
        {
            currentBook->printDetails();
        }
    }

    return true;
}

bool Application::booksSort(std::string option, std::string order)
{
    if (loggedUser == nullptr)
    {
        std::cout << NOT_LOGGED_IN_MESSAGE << std::endl;
        return false;
    }

    std::string key = option + " " + order;
    std::map<std::string, BookComparator>::const_iterator it = bookComparatorsMap.find(key);
    if (it == bookComparatorsMap.end())
    {
        std::cout << "Invalid books sort option ! " << std::endl;
        return false;
    }

    Sorter<Serializable*> sorter;
    sorter.sort(this->booksFileController.getFileItems(), it->second);
    return true;
}

// TODO - Update logic to write user on top of deleted, must probably add isDeleted to Serializable
bool Application::usersAdd(std::string username, std::string password, bool isAdmin)
{
    if (isThereSuchUsername(username))
    {
        std::cout << "Username taken !" << std::endl;
        return false;
    }

    Serializable* user = new User(username, password, isAdmin, false);
    usersFileController.addFileItem(user);
    return true;
}

bool Application::usersRemove(std::string _username)
{
    if (loggedUser == nullptr)
    {
        std::cout << NOT_LOGGED_IN_MESSAGE << std::endl;
        return false;
    }

    if (!loggedUser->isUserAdmin())
    {
        std::cout << NOT_ADMIN_MESSAGE << std::endl;
        return false;
    }


    if (!isThereSuchUsername(_username))
    {
        std::cout << "No user with such username !" << std::endl;
        return false;
    }

    usersFileController.removeFileItem([_username](Serializable* user)->bool
    {
        User* userPointer = dynamic_cast<User*>(user);
        return (userPointer->getUsername() == _username);
    });

    return true;
}

bool Application::isThereSuchUsername(std::string username)
{
    std::vector<Serializable*> users = usersFileController.getFileItems();
    for(Serializable* user : users)
    {
        if (((User*)user)->getUsername() == username)
            return true;
    }

    return false;
}

void Application::run()
{
    // User* initialUser = new User(INITIAL_USER_USERNAME, INITIAL_USER_PASSWORD, true, false);
    // this->usersFileController.addFileItem(initialUser);
    usersAdd(INITIAL_USER_USERNAME, INITIAL_USER_PASSWORD, true);

    login(INITIAL_USER_USERNAME, INITIAL_USER_PASSWORD);
    open("./files/books.bin");

    // logout();
    // usersRemove(INITIAL_USER_USERNAME);
    // login(INITIAL_USER_USERNAME, INITIAL_USER_PASSWORD);

    usersFileController.printAllItems();
    std::cout << std::endl;

    usersAdd("BoyanVD", "airbourne2003", false);
    usersAdd("Gosho", "123456789", false);

    usersFileController.printAllItems();
    std::cout << std::endl;

    usersRemove("Gosho");
    usersFileController.printAllItems();
    std::cout << std::endl;

    usersAdd("Miro", "123456789", false);
    usersFileController.printAllItems();
    std::cout << std::endl;

}

#endif