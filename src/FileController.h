/**
 * \class FileController
 *
 * \brief The class, impleneting file management.
 *
 * This is the class, that takes care of all the work with files,
 * that conatin Serializable objects information. In the contexts
 * of this application this is User and Book, but it works for 
 * all classes, that extend Serializable base class.
 *
 * \author $Author: Boyan Dafov $
 * 
 * Contact: boyandafov123@gmail.com
 *
 */
#ifndef __FILE_CONTROLLER_H
#define __FILE_CONTROLLER_H

#include<vector>
#include<string>
#include<functional>
#include "Serializable.h"

class FileController 
{
private:
    /**
     * The file, which controller works with, path.
     */
    std::string filepath;

    /**
     * Items, extracted from the file given.
     */
    std::vector<Serializable*> fileItems;

    /**
     * Helper flag, used to identify, if there is currently opened file.
     */
    bool isFileOpened;

    /**
    * Helper function, that deletes controller's information
    * loaded in memory.
    */
    void deleteFileItems()
    {
        for (Serializable* item : fileItems)
        {
            delete item;
        }
        fileItems.clear();
    }

public:
    FileController() : isFileOpened(false) {};
    FileController(std::string _filepath) : filepath(_filepath), isFileOpened(false) {};
    ~FileController();

    /**
    * Opens, the file given
    * 
    * @return bool, representing the success.
    */
    bool open();

    /**
    * Closes, the currently opened file.
    * 
    * @return bool, representing the success.
    */
    bool close();

    /**
    * Saves the changes done back to the initial file
    * 
    * @return bool, representing the success.
    */
    bool save();

    /**
    * Saves the changes in specific file given
    * 
    * @return bool, representing the success.
    */
    bool saveas(std::string path);

    /**
    * Sets the filepath value.
    * 
    * @param _filepath new file's path
    */
    void setFilepath(std::string _filepath)
    {
        this->filepath = _filepath;
    }

    /**
    * Returns the parsed objects from the file, used by the FileController
    * 
    * @return parsed serializable items, that the controller works with.
    */
   std::vector<Serializable*>& getFileItems()
   {
       return this->fileItems;
   }

    /**
    * Adds new file item to controller's items. Please note,
    * that the FileCntroller is owner of all it's file items, so
    * every item you add, will be deleted in FileController's
    * destructor.
    * 
    * @param item pointer to serializable item.
    */
   void addFileItem(Serializable* item);

   /**
    * Removes all file items, that doesnt satisfy predicate condition given.
    * 
    * @param pred Serializable predicate function
    */
   void removeFileItem(std::function<bool(Serializable*)> pred);
};

#endif