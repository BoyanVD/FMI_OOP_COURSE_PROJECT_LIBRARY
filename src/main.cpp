#include <iostream>

#include "Book.h"
#include "Application.h"

/**
 * \mainpage Project Description
 * 
 * \section Project idea
 *  This is a project, that implements functionality for user library management. It works with books and users, where
 * books files can be dynamically changed from user throughout application runtime. Users file is static and it's always
 * the same for the application. There are two types of users - admins and regular users. The admin users can use more
 * of the application's commands, supported. User can filter, search, get information abouts books from file chosen.
 * Admins can add and delete other users.
 * 
 * \section Github link :
 * https://github.com/BoyanVD/FMI_OOP_COURSE_PROJECT_LIBRARY
 */

int main() 
{
    Book::generateBooksFile("./files/books.bin");
    
    Application app;
    app.run();
}