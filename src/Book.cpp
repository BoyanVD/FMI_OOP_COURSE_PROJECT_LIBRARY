#ifndef __BOOK_CPP
#define __BOOK_CPP

#include <iostream>
#include <string>
#include <vector>
#include <fstream>

#include "Book.h"
#include "Constants.h"

bool Book::serialize(std::ofstream& output) const 
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

bool Book::deserialize(std::ifstream& input) 
{
    if (!(readStringFromBinary(input, author) &&
        readStringFromBinary(input, title) &&
        readStringFromBinary(input, genre) &&
        readStringFromBinary(input, description)))
    {
        return false;
    }

    // this->print();

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

void Book::print() const 
{
    std::cout << "Author : " << author 
            << "\n Title : " << title 
            << "\n Genre : " << genre 
            << "\n Desc : " << description
            << "\n Year : " << year << std::endl;
    std::cout << "Tags : ";
    for (std::string tag : tags) {
        std :: cout << tag << ", ";
    }
    std::cout << std::endl;
    std::cout << "Rating : " << rating
            << "\n Id : " << id << std::endl;
}

#endif