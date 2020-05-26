#ifndef __BOOK_CPP
#define __BOOK_CPP

#include <iostream>
#include <cstring>
#include <vector>
#include <fstream>

#include "Book.h"
#include "Constants.h"

void Book::generateBooksFile(std::string filename)
{
    Book b1("John Michaels", "COOL BOOK", "COMEDY", "The greatest book ever", 2010, {"super", "cool reading", "book"}, 4.5, 27);
    Book b2("Andy Rillins", "Harry Potter", "Adventure", "Magic", 2002, {"magic", "friendship"}, 9.5, 24);
    Book b3("Oliver Dann", "Mission Impossible", "Action", "Action", 2017, {"action"}, 1.7, 23);
    std::ofstream output(filename, std::ios::binary);
    b1.serialize(output);
    b2.serialize(output);
    b3.serialize(output);
    output.close();
}

bool Book::serialize(std::ostream& output) const 
{
    if (!(writeStringToBinaryFile(output, BOOK_OBJECT_SIGNATURE) &&
        writeStringToBinaryFile(output, author) &&
        writeStringToBinaryFile(output, title) &&
        writeStringToBinaryFile(output, genre) &&
        writeStringToBinaryFile(output, description)))
    {
        return false;
    }

    output.write((char*)&year, sizeof(year));
    if (!output)
        return false;

    size_t numberOfTags = tags.size();
    output.write((char*)&numberOfTags, sizeof(numberOfTags));
    for (std::string tag : tags)
    {
        if(!writeStringToBinaryFile(output, tag))
            return false;
    }

    output.write((char*)&rating, sizeof(rating));
    output.write((char*)&id, sizeof(id));

    return output.good();
}

bool Book::deserialize(std::istream& input) 
{
    if (!(readStringFromBinary(input, author) &&
        readStringFromBinary(input, title) &&
        readStringFromBinary(input, genre) &&
        readStringFromBinary(input, description)))
    {
        return false;
    }

    input.read((char*)&year, sizeof(year));
    if (!input)
        return false;

    size_t numberOfTags;
    input.read((char*)&numberOfTags, sizeof(numberOfTags));
    for (size_t i = 0; i < numberOfTags; ++i) {
        std::string tag;
        if (!readStringFromBinary(input, tag))
            return false;

        tags.push_back(tag);
    }

    input.read((char*)&rating, sizeof(rating));
    input.read((char*)&id, sizeof(id));

    return input.good();
}

void Book::printDetails() const 
{
    std::cout << "Author : " << author << std::endl
            << "Title : " << title << std::endl
            << "Genre : " << genre << std::endl
            << "Desc : " << description << std::endl
            << "Year : " << year << std::endl;
    std::cout << "Tags : ";
    for (std::string tag : tags) {
        std :: cout << tag << ", ";
    }
    std::cout << std::endl;
    std::cout << "Rating : " << rating << std::endl
            << "Id : " << id << std::endl;
}

void Book::printForAll() const
{
    std::cout << "Title : " << title << std::endl
            << "Author : " << author << std::endl
            << "Genre : " << genre << std::endl
            << "ID : " << id << std::endl;
}

bool Book::hasTag(const std::string& _tag) const
{
    for (std::string tag : tags)
    {
        if (tag == _tag)
            return true;
    }

    return false;
}

#endif