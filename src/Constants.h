#ifndef __CONSTANTS_H
#define __CONSTANTS_H

#include <iostream>
#include <cstring>
#include <map>

#include "Book.h"

const std::string BOOK_OBJECT_SIGNATURE = "Book";

const std::string INITIAL_USER_USERNAME = "admin";
const std::string INITIAL_USER_PASSWORD = "i<3c++";

const std::string NOT_LOGGED_IN_MESSAGE = "Not logged in !";

using BooksPredicate = bool (*) (const Book*, std::string);
const std::map<std::string, BooksPredicate> predicateMap = {
    {"title", [](const Book* book, std::string str)->bool{return book->getTitle() == str;}},
    {"author", [](const Book* book, std::string str)->bool{return book->getAuthor() == str;}},
    {"tag", [](const Book* book, std::string str)->bool{return book->hasTag(str);}}
};

#endif