/**
 * \class Book
 *
 * \brief The class, used to represent application's book entities.
 *
 * Book class is used to extend Serializable base class. Stores the information
 * about the books in application. Only implements books serealization and
 * deserealization methods.
 *
 * \author $Author: Boyan Dafov $
 * 
 * Contact: boyandafov123@gmail.com
 *
 */
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
    /**
    * Book author's name string.
    */
    std::string author;
    
    /**
    * Book title's string.
    */
    std::string title;

    /**
    * Book genre string.
    */
    std::string genre;

    /**
    * Book's description string.
    */
    std::string description;

    /**
    * Book's year.
    */
    unsigned year;

    /**
    * Vector, containing book tags strings.
    */
    std::vector<std::string> tags;

    /**
    * Book's rating.
    */
    double rating;

    /**
    * Book id.
    */
    unsigned id;

public:
    Book() : Serializable(false), author(""), title(""), genre(""), description(""), year(0), tags(), rating(0.0), id(0) {};
    Book(const std::string& _author, const std::string& _title, const std::string& _genre, const std::string& _description, const unsigned _year, const std::vector<std::string>& _tags, double _rating, unsigned _id) :
    author(_author), title(_title), genre(_genre), description(_description), year(_year), tags(_tags), rating(_rating), id(_id) {}

    /**
    * Method used only for demonstration purposes. Generates file with books information.
    * Note, that the books generated are not real books :)
    *
    * @param filename The file where you want to generate books information.
    */
    static void generateBooksFile(std::string filename); // This method is only with demonstration purpose

    /**
    * Serializes book object into file given.
    *
    * @param output destionation ostream
    */
    bool serialize(std::ostream& output) const override;

    /**
    * Loads book object from file given
    *
    * @param input destionation istream
    */
    bool deserialize(std::istream& input) override;

    /**
    * Prints brief information.
    */
    void printForAll() const override;

    /**
    * Prints details about book.
    */
    void printDetails() const override;

    /**
     * Empty methods as system doesn't still support delete functionality for books
     */
    bool del(std::fstream& file) override {return true;}

    /**
     * Empty methods as system doesn't still support add functionality for books
     */
    bool add(std::fstream& file) override {return true;}

    /**
    * Helper function, used for checking if there is such tag for book.
    *
    * @param _tag tag string
    * @return bool
    */
    bool hasTag(const std::string& _tag) const;

    /**
    * Getter
    * 
    * @return book's id 
    */
    unsigned getId() const;

    /**
    * Getter
    * 
    * @return book's title 
    */
    std::string getTitle() const;

    /**
    * Getter
    * 
    * @return book's author name 
    */
    std::string getAuthor() const;

    /**
    * Getter
    * 
    * @return book's year 
    */
    unsigned getYear() const;

    /**
    * Getter
    * 
    * @return book's rating 
    */
    double getRating() const;
};

#endif