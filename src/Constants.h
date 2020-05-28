#ifndef __CONSTANTS_H
#define __CONSTANTS_H

#include <iostream>
#include <string>

const std::string USERS_FILE_NAME = "./files/users.bin";

const std::string BOOK_OBJECT_SIGNATURE = "Book";
const std::string USER_OBJECT_SIGNATURE = "User";

const std::string INITIAL_USER_USERNAME = "admin";
const std::string INITIAL_USER_PASSWORD = "i<3c++";

const std::string NOT_LOGGED_IN_MESSAGE = "Not logged in !";
const std::string NOT_ADMIN_MESSAGE = "User not admin !";

const std::string INPUT_COMMAND_DELIMETER = " ";

const std::string ENCRYPTION_KEY = "FANCY KEY";

#endif