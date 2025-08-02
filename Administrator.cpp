#include "Administrator.hpp"
#include "Flight.hpp"
#include "Aircraft.hpp"
#include "Maintenance.hpp"

// Display the Administrator menu options
void Administrator :: showMenu(){
    std::cout<<"--- Administrator Menu ---\n"
        <<"1. Manage Flights\n"
        <<"2. Manage Aircraft\n"
        <<"3. Manage Users\n"
        <<"4. Generate Reports\n"
        <<"5. Logout\n";

    processChoice(); // Process the admin's selection
}

// Handle the administrator's menu choices
void Administrator :: processChoice(){
    cout<<"Enter choice:\n";
    cin>>adminChoice; // Get admin choice from input

    // Option 1: Manage Flights
    if (adminChoice == 1) {
        menu = std::make_unique<Flight>();  // Create a Flight object
        menu ->showMenu();                  // Show Flight management menu
    } 
    // Option 2: Manage Aircraft
    else if (adminChoice == 2) {
        menu = std::make_unique<Aircraft>(); // Create an Aircraft object
        menu ->showMenu();                   // Show Aircraft management menu
    } 
    // Option 3: Manage Users
    else if (adminChoice == 3) {
        menu = std::make_unique<User>();     // Create a User object
        menu ->showMenu();                   // Show User management menu
    } 
    // Option 4: Generate Reports
    else if (adminChoice == 4) {
        User::logActivity(getID(), "Generated Reports"); // Log the action
        
        // Display report generation options
        std::cout << "\n--- Generate Reports ---\n"
                << "1. Operational Reports\n"
                << "2. Maintenance Reports\n"
                << "3. User Activity Reports\n"
                << "4. Back to Main Menu\n"
                << "Enter choice: ";

        int reportChoice;
        std::cin >> reportChoice; // Get report type choice

        // Generate Operational Report
        if (reportChoice == 1) {
            std::string monthYear;
            std::cout << "\n--- Operational Reports ---\n";
            std::cout << "Enter Month and Year for Report (MM-YYYY): ";
            std::cin >> monthYear;

            Flight::generateOperationalReport(monthYear); // Implemented in Flight
        } 
        // Generate Maintenance Report
        else if (reportChoice == 2) {
            Maintenance m;
            m.generateMaintenanceReport(); // Display all maintenance logs
        } 
        // Generate User Activity Report
        else if (reportChoice == 3) {
            // User::generateUserActivityReport(); // Old function placeholder
            User::showUserActivityReport(); // Display logs from user activity
        } 
        // Option 4: Go back to main admin menu
        else {
            return; // Exit report menu and return to main menu
        }
    }
    // Option 5: Logout
    else{
        cout<<"logout";
        return ; // End admin session
    }

    // Show the menu again after completing an action
    showMenu();
}
