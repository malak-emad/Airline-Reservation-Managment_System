#ifndef PASSENGER_H
#define PASSENGER_H

#include <iostream>
#include <string>
#include <fstream>
#include <filesystem> 
#include <nlohmann/json.hpp>
#include <functional>
#include "User.hpp"

using namespace std;
namespace fs = std::filesystem;
using json = nlohmann::json;

// ------------------------------------------------------------
// Passenger Class
// ------------------------------------------------------------
// Represents a passenger in the airline system.
// Inherits from User and provides functionalities for:
// - Displaying passenger menu
// - Searching flights & booking
// - Viewing reservations
// - Checking in
// ------------------------------------------------------------
class Passenger : public User {
private:
    int passengerChoice;                       // Stores current menu choice
    std::shared_ptr<User> loggedInUser;        // Holds the logged-in passenger

public:
    // --- MenuInterface (inherited from User) ---
    void showMenu() override;                  // Displays the passenger menu
    void processChoice() override;             // Handles the passenger's menu choice

    // --- User Management ---
    void setCurrentUser(const std::shared_ptr<User>& user) { 
        loggedInUser = user; 
    }

    // Returns the passenger's unique ID if logged in
    std::string getID() const {
        return loggedInUser ? loggedInUser->getID() : "";
    }
};

#endif
