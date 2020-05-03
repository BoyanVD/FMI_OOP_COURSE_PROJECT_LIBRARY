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

using BookComparator = bool (*) (Serializable*, Serializable*);
const std::map<std::string, BookComparator> bookComparatorsMap = {
    {"title asc", [](Serializable* book1, Serializable* book2)->bool{return ((Book*)book1)->getTitle() < ((Book*)book2)->getTitle();}},
    {"title desc", [](Serializable* book1, Serializable* book2)->bool{return ((Book*)book1)->getTitle() > ((Book*)book2)->getTitle();}},

    {"author asc", [](Serializable* book1, Serializable* book2)->bool{return ((Book*)book1)->getAuthor() < ((Book*)book2)->getAuthor();}},
    {"author desc", [](Serializable* book1, Serializable* book2)->bool{return ((Book*)book1)->getAuthor() > ((Book*)book2)->getAuthor();}},

    {"year asc", [](Serializable* book1, Serializable* book2)->bool{return ((Book*)book1)->getYear() < ((Book*)book2)->getYear();}},
    {"year desc", [](Serializable* book1, Serializable* book2)->bool{return ((Book*)book1)->getYear() > ((Book*)book2)->getYear();}},

    {"rating asc", [](Serializable* book1, Serializable* book2)->bool{return ((Book*)book1)->getRating() < ((Book*)book2)->getRating();}},
    {"rating desc", [](Serializable* book1, Serializable* book2)->bool{return ((Book*)book1)->getRating() > ((Book*)book2)->getRating();}}
};

#endif