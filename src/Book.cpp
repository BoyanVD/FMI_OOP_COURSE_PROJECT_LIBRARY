#ifndef __BOOK_CPP
#define __BOOK_CPP

#include <iostream>
#include <string>
#include <vector>
#include <fstream>

#include "Book.h"
#include "Constants.h"

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

bool Book::hasTag(std::string _tag)const
{
    for (std::string tag : tags)
    {
        if (tag == _tag)
            return true;
    }

    return false;
}

#endif