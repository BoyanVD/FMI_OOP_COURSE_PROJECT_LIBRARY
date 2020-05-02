#ifndef __BOOK_H
#define __BOOK_H

#include<string>
#include<vector>

#include "Serializable.h"

class Book : public Serializable
{
private:
    std::string author;
    std::string title;
    std::string genre;
    std::string description;
    unsigned year;
    std::vector<std::string> tags; // tags == keywords
    double rating;
    unsigned id;

public:
    Book() : author(""), title(""), genre(""), description(""), year(0), tags(), rating(0.0), id(0) {};
    Book(const std::string& _author, const std::string& _title, const std::string& _genre, const std::string& _description, const unsigned _year, const std::vector<std::string>& _tags, double _rating, unsigned _id) :
    author(_author), title(_title), genre(_genre), description(_description), year(_year), tags(_tags), rating(_rating), id(_id) {};

    bool serialize(std::ofstream& output) const;
    bool deserialize(std::ifstream& input);

    void print() const;
};

#endif