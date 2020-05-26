#include <iostream>
#include <fstream>
#include <cstring>
#include <vector>

#include "Book.h"
#include "FileController.h"
#include "Application.h"

int main() 
{
    Book::generateBooksFile("./files/books.bin");
    
    Application app;
    app.run();
}