#include <iostream>
#include <fstream>
#include <cstring>
#include <vector>

#include "Book.h"
#include "FileController.h"

int main() 
{
    Book b1("Jefferson Michaels", "COOL BOOK", "COMEDY", "The greatest book ever", 2010, {"super", "cool", "book"}, 4.5, 27);
    Book b2("JK Rillins", "Harry Potter", "Adventure", "Magic", 2002, {"magic", "friendship"}, 9.5, 24);
    Book b3("Jack Dann", "Mission Impossible", "Action", "Action", 2017, {"action"}, 1.7, 23);
    std::ofstream output("./files/books.bin", std::ios::binary);
    b1.serialize(output);
    b2.serialize(output);
    b3.serialize(output);
    output.close();

    FileController controller("./files/books.bin");
    controller.open();
    controller.printAllItems();
}