#ifndef __APPLICATION_H
#define __APPLICATION_H

#include "FileController.h"
#include "UsersController.h"
#include "User.h"

class Application {
private:
    FileController fileController;
    UsersController usersController;
    User currentUser;
public:
    Application();

    void run();
};

#endif