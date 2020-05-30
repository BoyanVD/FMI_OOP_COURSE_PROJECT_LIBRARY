/**
 * \class Serializable
 *
 * \brief Serializable base class.
 *
 * This is the class, that every entity, which implements
 * serialization logic, must implement.
 *
 * \author $Author: Boyan Dafov $
 * 
 * Contact: boyandafov123@gmail.com
 *
 */
#ifndef __SERIALIZABLE_H
#define __SERIALIZABLE_H

#include <string>
#include <iostream>
#include <fstream>

class Serializable
{
protected:
    /**
     * Flag used, to mark if object is deleted.
     */
    bool isDeleted;

    /**
     * Helper static function
     */
    static bool writeStringToBinaryFile(std::ostream& output, const std::string& str);

    /**
     * Helper static function
     */
    static bool readStringFromBinary(std::istream& input, std::string& str);
public:
    Serializable() : isDeleted(false) {}
    Serializable(bool _isDeleted) : isDeleted(_isDeleted) {}

    /**
    * Serializes object into file given.
    *
    * @param output destionation ostream
    */
    virtual bool serialize(std::ostream& output) const = 0;

    /**
    * Loads object from file given.
    *
    * @param input destionation istream
    */
    virtual bool deserialize(std::istream& input) = 0;

    /**
    * Prints brief information.
    */
    virtual void printForAll() const = 0;

    /**
    * Prints details.
    */
    virtual void printDetails() const = 0;

    /**
    * Deletes, object from file given.
    */
    virtual bool del(std::fstream& file) = 0;

    /**
    * Adds object to file given.
    */
    virtual bool add(std::fstream& file) = 0;

    /**
    * Reads serializable from file given.
    * 
    * @param input file input stream
    * @return pointer to generated object
    */
    static Serializable* readSerializable(std::istream &input);

    /**
    * Writes serializable to file given.
    * 
    * @param output file output stream
    * @param serializable pointer to serializable object to write
    * @return bool, representing the success.
    */
    static bool writeSerializable(std::ostream& output, Serializable* serializable);

    virtual ~Serializable() {};
};

#endif