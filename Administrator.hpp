#ifndef ADMINISTRATOR_H
#define ADMINISTRATOR_H

#include<iostream>
#include<string>

#include <fstream>
#include <string>
#include <filesystem> 
#include <nlohmann/json.hpp>
#include <functional>  
#include "User.hpp"
#include "MenuInterface.hpp"

// Use standard namespace for convenience
using namespace std;

// Create an alias for the filesystem namespace
namespace fs = std::filesystem;

// Create an alias for the nlohmann JSON library
using json = nlohmann::json;

// Administrator class inherits from User
// This class handles administrative functionalities
class Administrator : public User {
    private:
        int adminChoice; // Stores the administrator's menu choice
        std::unique_ptr<MenuInterface> menu; // Pointer to the active menu (Flight, Aircraft, or User)

    public:
        // Display the administrator menu
        void showMenu() override;

        // Process the selected menu option
        void processChoice() override;
};

#endif
