#include <iostream>

#include "Book.h"
#include "Application.h"

int main() 
{
    Book::generateBooksFile("./files/books.bin");
    
    Application app;
    app.run();
}