#include "Dashboard.hpp"
#include "User.hpp"
#include "Administrator.hpp"
#include "BookingAgent.hpp"
#include "Passenger.hpp"

// Path to the JSON file that stores user login data
static std::string path = "data/users_log.json";

// Show the initial dashboard/menu where the user selects their role
void DashBoard :: run(){
    std::cout<<"Welcome to Airline Reservation and Management System\n"
        <<"Please select your role:\n"
        <<"1. Administrator\n"
        <<"2. Booking Agent\n"
        <<"3. Passenger\n";
    process(); // Proceed to process the chosen role
}

// Handles the user's role selection and login process
void DashBoard :: process(){
    cout<<"Enter choice:\n";
    cin>>choice;

    switch(choice) {
        case(1):
            // --- Administrator login ---
            cout<<"--- Administrator Login ---\n";
            user_Inputs(); // Ask for username & password

            if(user_verify()){ 
                // If login is successful
                User::logActivity(currentUser->getID(), "Logged In");

                // Create a User object for the logged-in user
                currentUser = std::make_shared<User>();
                currentUser->setUsername(username);
                currentUser->setPassword(password);

                // Search in user list to get the correct user ID
                for (auto& user : User::getUserList()) {
                    if(user->getUsername() == username && user->getPassword() == password) {
                        currentUser->setID(user->getID());
                        break;
                    }
                }

                // Create an Administrator interface for the logged-in user
                userInterface = std::make_unique<Administrator>();
            }
            else{
                // Login failed
                cout<<"Login failed, wrong username or password!\n";
                run(); // Show dashboard again
            }
            break;

        case(2):
            // --- Booking Agent login ---
            cout<<"--- Booking Agent Login ---\n";
            user_Inputs(); 

            if(user_verify()){
                cout<<"Login successful!\n";
                userInterface = std::make_unique<BookingAgent>();
            }
            else{
                cout<<"Login failed, wrong username or password!\n";
                run();
            }
            break;

        case(3):
            // --- Passenger login ---
            cout<<"--- Passenger Login ---\n";
            user_Inputs();

            if(user_verify()){
                cout<<"Login successful!\n";
                userInterface = std::make_unique<Passenger>();
                userInterface->setCurrentUser(currentUser); // Assign current user to interface
            }
            else{
                cout<<"Login failed, wrong username or password!\n";
                run();
            }
            break;

        default:
            // If the user enters an invalid choice, simply break
            break;
    }

    // If a userInterface has been created (successful login), show its menu
    if(userInterface){
        userInterface->showMenu();
    }

    // After menu execution, return to dashboard
    run();
}

// Ask the user to input their username and password
void DashBoard :: user_Inputs(){
    cout<<"Username: ";
    cin>>username;
    cout<<"Password: ";
    cin>>password;
    cout<<"\n";
}

// Verify the entered username and password against the JSON file
bool DashBoard :: user_verify(){
    // Check if the JSON file exists
    if (!fs::exists(path)) {
        std::cerr << "File not found: " << path << "\n";
        return false;
    }

    // Read the JSON file containing user data
    std::ifstream file(path);
    json users;
    file >> users;

    // Iterate over all users in the JSON
    for (const auto& user : users) {
        if(user["username"] == username && user["password"] == password ){
            // Create a User object for the authenticated user
            currentUser = std::make_shared<User>();
            currentUser->fromJson(user); // Load user data from JSON
            return true;
            break;
        }
    }
    return false; // No match found
}
