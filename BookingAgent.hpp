#ifndef BOOKINGAGENT_H
#define BOOKINGAGENT_H

#include<iostream>
#include<string>

#include <fstream>
#include <string>
#include <filesystem> 
#include <nlohmann/json.hpp>
#include <functional>  
#include "User.hpp"

using namespace std;
namespace fs = std::filesystem;
using json = nlohmann::json;

// The BookingAgent class represents a booking agent user in the airline system.
// A BookingAgent can search flights, create reservations, modify or cancel them,
// and logout from the system. Inherits from User.
class BookingAgent : public User {
    private:
        int bookingChoice;      // Stores the menu option chosen by the booking agent
        string origin, dest, date; // Used for storing flight search input (origin, destination, date)

    public:
        // Display the booking agent menu
        void showMenu() override;

        // Process the selected booking agent menu choice
        void processChoice() override;


};

#endif
