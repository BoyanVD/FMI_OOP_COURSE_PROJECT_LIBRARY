#ifndef __FILECONTROLLER_H
#define __FILECONTROLLER_H

#include<vector>
#include<string>
#include "Serializable.h"

/*
Books file format expected : 
    <std::string author>, <std::string title>, <std::string genre>, <std::string description>, <unsigned year>, <std::vector<std::string> tags>, <double rating>, <unsigned id>
    Books file is considered binary !
*/


/*
* For the purpose of the system, it is not necessary to user the abstract class Serializable, but idea os to make the code more
* extencible for future functionality addition.
*/
class FileController {
private:
    std::string filepath;
    std::vector<Serializable*> fileItems;

public:
    //initialize filename with nullptr
    FileController();
    FileController(std::string _filepath) : filepath(_filepath) {};
    ~FileController();

    /*
    * Opens, reads and parse the file information into objects from the type given, and returns vector with all
    * parsed objects. After execution the file is closed and we are not working with it anymore.
    */
    std::vector<Serializable*> open();

    /*
    * Closes the currently opened document 
    */
    bool close();

    /*
    * Saves the changes done back to the initial file
    */
    bool save();

    /*
    * Saves the changes in specific file given
    */
    bool saveas(std::string path);

    /*
    * Sets the filepath value
    */
    void setFilepath(std::string _filepath)
    {
        this->filepath = _filepath;
    }

    /*
    * Used for debugging
    */
   void printAllItems()
   {
       for (Serializable* serializable : fileItems)
       {
           serializable->print();
       }
   }
};

#endif