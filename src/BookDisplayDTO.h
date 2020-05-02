#ifndef __BOOKDISPLAYDTO_H
#define __BOOKDISPLAYDTO_H

#include "Book.h"

class BookDisplayDTO {
    private:
    std::string title;
    std::string author;
    std::string genre;
    unsigned id;

    public:
    BookDisplayDTO(Book book);
};

#endif