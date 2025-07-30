#ifndef MENUINTERFACE_H
#define MENUINTERFACE_H

class MenuInterface {
public:
    virtual void showMenu() = 0;
    virtual void processChoice() = 0;
    virtual ~MenuInterface() = default;
};


#endif