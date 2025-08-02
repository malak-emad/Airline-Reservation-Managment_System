#ifndef DASHBOARD_H
#define DASHBOARD_H

#include<iostream>
#include<string>

#include <fstream>
#include <string>
#include <filesystem> 
#include <nlohmann/json.hpp>
#include <functional>  
#include <memory>
#include "MenuInterface.hpp"

// Forward declaration of the User class
class User;

using namespace std;
namespace fs = std::filesystem;
using json = nlohmann::json;

// ------------------------------------------------------------
// Global shared pointer to store the currently logged-in user
// ------------------------------------------------------------
inline std::shared_ptr<User> currentUser = nullptr;

// ------------------------------------------------------------
// Function to get the currently logged-in user
// ------------------------------------------------------------
inline std::shared_ptr<User> getCurrentUser() {
    return currentUser;
}

// ------------------------------------------------------------
// DashBoard class
// Responsible for displaying the initial menu, handling user
// login, verifying credentials, and forwarding the user to the
// corresponding interface (Administrator / BookingAgent / Passenger).
// ------------------------------------------------------------
class DashBoard {
    private:
        // Stores the username and password entered by the user
        string username, password;

        // Stores the user's menu choice (1 = Admin, 2 = Agent, 3 = Passenger)
        int choice;

    public:
        // Display the initial dashboard menu
        void run();

        // Process the user's menu choice and handle login
        void process();

        // Prompt for username and password input
        void user_Inputs();

        // Verify the entered credentials against the JSON file
        bool user_verify();

        // Pointer to the currently logged-in User object
        std::shared_ptr<User> currentUser;

    protected:
        // Pointer to the specific menu interface for the logged-in user
        // (Administrator, BookingAgent, or Passenger)
        std::unique_ptr<MenuInterface> userInterface;
};

#endif
