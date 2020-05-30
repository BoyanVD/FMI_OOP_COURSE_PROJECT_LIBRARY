/**
 * \class User
 *
 * \brief The class, used to represent application's user entities.
 *
 * User class is used to extend Serializable base class. Stores the information
 * about the users in application. Only implements user serealization and
 * deserealization methods.
 *
 * \author $Author: Boyan Dafov $
 * 
 * Contact: boyandafov123@gmail.com
 *
 */
#ifndef __USER_H
#define __USER_H

#include <string>
#include <fstream>
#include "Serializable.h"

class User : public Serializable
{
private:
    /**
     * Username
     */
    std::string username;

    /**
     * Password
     */
    std::string password;

    /**
     * Flag to mark if user is admin
     */
    bool isAdmin;
    
public:
    User() : Serializable(false), username(""), password(""), isAdmin(false) {};
    User(const std::string& _username, const std::string& _password, bool _isAdmin, bool _isDeleted) : 
    Serializable(_isDeleted), username(_username), password(_password), isAdmin(_isAdmin) {};

    std::string getUsername() const;

    std::string getPassword() const;

    bool isUserAdmin() const;

    bool isUserDeleted() const;

    /**
    * Serializes user object into file given.
    *
    * @param output destionation ostream
    */
    bool serialize(std::ostream& output) const;

    /**
    * Loads user object from file given
    *
    * @param input destionation istream
    */
    bool deserialize(std::istream& input);

    /**
    * Prints brief information.
    */
    void printForAll() const;

    /**
    * Prints details about user.
    */
    void printDetails() const;

    /**
     * Deletes user from file
     * 
     * @param file destination
     * @return bool, representing the success
     */
    bool del(std::fstream& file);

    /**
     * Adds user to file
     * 
     * @param file destination
     * @return bool, representing the success
     */
    bool add(std::fstream& file);
};

#endif