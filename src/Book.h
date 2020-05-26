#ifndef __BOOK_H
#define __BOOK_H

#include<string>
#include<vector>
#include<fstream>
#include<iostream>

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
    Book() : Serializable(false), author(""), title(""), genre(""), description(""), year(0), tags(), rating(0.0), id(0) {};
    Book(const std::string& _author, const std::string& _title, const std::string& _genre, const std::string& _description, const unsigned _year, const std::vector<std::string>& _tags, double _rating, unsigned _id) :
    author(_author), title(_title), genre(_genre), description(_description), year(_year), tags(_tags), rating(_rating), id(_id) {}

    static void generateBooksFile(std::string filename); // This method is only with demonstration purpose

    bool serialize(std::ostream& output) const override;
    bool deserialize(std::istream& input) override;

    void printForAll() const override;
    void printDetails() const override;
    bool del(std::fstream& file) override {return true;} // Empty methods as system doesn't still support delete functionality
    bool add(std::fstream& file) override {return true;} // Empty methods as system doesn't still support add functionality

    bool hasTag(const std::string& _tag) const;

    unsigned getId() const
    {
        return this->id;
    }

    std::string getTitle() const
    {
        return this->title;
    }

    std::string getAuthor() const
    {
        return this->author;
    }

    unsigned getYear() const
    {
        return this->year;
    }

    double getRating() const
    {
        return this->rating;
    }
};

#endif