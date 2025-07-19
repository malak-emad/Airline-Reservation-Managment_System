#include"User.hpp"

std::string path = "users_log.json";


void User :: showMenu(){
    std::cout<<"Welcome to Airline Reservation and Management System\n"
        <<"Please select your role:\n"
        <<"1. Administrator\n"
        <<"2. Booking Agent\n"
        <<"3. Passenger\n";
    processUser();
}

void User :: processUser(){
    cout<<"Enter choice:\n";
    cin>>role;
    if (role == "1") {
        cout<<"--- Administrator Login ---\n";
        userInputs();
        // showAdminDashboard();
        cout<<"ADMIN";
    } else if (role == "2") {
        // showAgentDashboard();
    } else {
        // showPassengerDashboard();
    }

}

void User :: userInputs(){
    cout<<"Username: ";
    cin>>username;
    cout<<"Password: ";
    cin>>password;
    cout<<"\n";
    if(verifyUser()){
        cout<<"Login successful!\n";
    }
    else{
        cout<<"Login failed, wrong username or password!\n";
        showMenu();
    }
}

bool User :: verifyUser(){
    if (!fs::exists(path)) {
        std::cerr << "File not found: " << path << "\n";
        return false;
    }

    std::ifstream file(path);
    json users;
    file >> users;

    for (const auto& user : users) {
        if(user["username"] == username & user["password"] == password ){
            return true;
            break;
        }
    }
    return false;
}