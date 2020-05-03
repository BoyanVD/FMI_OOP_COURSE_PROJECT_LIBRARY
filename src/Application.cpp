#ifndef __APPLICATION_CPP
#define __APPLICATION_CPP

#include <iostream>
#include <map>

#include "Application.h"
#include "FileController.h"
#include "Constants.h"
#include "Book.h"
#include "Sorter.h"

bool Application::login(std::string username, std::string password)
{
    if (loggedUser != nullptr)
    {
        std::cout << "You are already logged in !" << std::endl;
        return false;
    }

    for (User user : users)
    {
        if ((user.getUsername() == username) && (user.getPassword() == password))
            loggedUser = &user;
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

void Application::run()
{
    User initialUser(INITIAL_USER_USERNAME, INITIAL_USER_PASSWORD, true);
    this->users.push_back(initialUser);

    login(INITIAL_USER_USERNAME, INITIAL_USER_PASSWORD);
    open("./files/books.bin");

    booksAll();
    std::cout << std::endl;

    booksSort("rating", "asc");
    booksAll();
    std::cout << std::endl;

    booksSort("rating", "desc");
    booksAll();
}

#endif