#include <iostream>

#include "Book.h"
#include "Application.h"

/**
 * \mainpage Project Description
 * 
 * \section Idea
 *  This is a project, that implements functionality for user library management. It works with books and users, where
 * books files can be dynamically changed from user throughout application runtime. Users file is static and it's always
 * the same for the application. There are two types of users - admins and regular users. The admin users can use more
 * of the application's commands, supported. User can filter, search, get information abouts books from file chosen.
 * Admins can add and delete other users.
 * 
 * \section Github
 * https://github.com/BoyanVD/FMI_OOP_COURSE_PROJECT_LIBRARY
 */

int main() 
{
    /**
     * 
     * Command to compile:
     * g++ main.cpp Book.cpp FileController.cpp SerializableFactory.cpp Serializable.cpp Application.cpp Command.cpp User.cpp SimpleEncryptor.cpp
     * 
     * Example of system usage :
     * 
     * >open ./files/books.bin
     * >login admin i<3c++
     * >books_all
     * >books_info 24
     * >books_find tag super
     * >books_find title Fancy book
     * >books_find author John Michaels
     * >books_sort title asc
     * >books_all
     * >books_sort year desc
     * >books_all
     * >books_sort rating
     * >books_all
     * >users_add ivan 123456
     * >logout
     * >login ivan 123456
     * >users_add georgi fancyPass (not authorized)
     * >logout
     * >login admin i<3c++
     * >users_remove ivan
     * >exit
     */
    Book::generateBooksFile("./files/books.bin");
    
    Application app;
    app.run();
}