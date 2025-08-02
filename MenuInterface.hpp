#ifndef MENUINTERFACE_H
#define MENUINTERFACE_H
#include <memory> // for std::shared_ptr

class User;  // Forward declaration

class MenuInterface {
public:
    virtual void showMenu() = 0;
    virtual void processChoice() = 0;


    // Add this:
    virtual void setCurrentUser(std::shared_ptr<User> user) {
        currentUser = user;
    }

    virtual ~MenuInterface() = default;

protected:
    std::shared_ptr<User> currentUser; // store the logged-in user
};

#endif
