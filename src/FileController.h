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
    bool isFileOpened;

    void deleteFileItems()
    {
        for (Serializable* item : fileItems)
        {
            delete item;
        }
        fileItems.clear();
    }

public:
    //initialize filename with nullptr
    FileController() : isFileOpened(false) {};
    FileController(std::string _filepath) : filepath(_filepath), isFileOpened(true) {};
    ~FileController();

    /*
    * Opens, reads and parse the file information into objects from the type given, and returns vector with all
    * parsed objects. After execution the file is closed and we are not working with it anymore.
    */
    bool open();

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
    * Returns the parsed objects from the file, used by the FileController
    */
   std::vector<Serializable*>& getFileItems()
   {
       return this->fileItems;
   }

    /*
    * Used for debugging
    */
   void printAllItems()
   {
       for (Serializable* serializable : fileItems)
       {
           serializable->printForAll();
       }
   }

   /*
   * DEMO METHOD - MUST REMOVE IT WHEN READY
   */
  void setFileItems(std::vector<Serializable*> items)
  {
      this->fileItems = items;
  }

  /*
  * DEMO METHOD
  */
 void addFileItem(Serializable* item)
 {
     this->fileItems.push_back(item);
 }
};

#endif