#include"User.hpp"
#include "Administrator.hpp"
#include "BookingAgent.hpp"

std::string path = "users_log.json";


void User :: showDashboard(){
    std::cout<<"Welcome to Airline Reservation and Management System\n"
        <<"Please select your role:\n"
        <<"1. Administrator\n"
        <<"2. Booking Agent\n"
        <<"3. Passenger\n";
    process();
}

void User :: process(){
    cout<<"Enter choice:\n";
    cin>>role;
    switch(role) {
        case(1):
        cout<<"--- Administrator Login ---\n";
        user_Inputs();
        if(user_verify()){
            cout<<"Login successful!\n";
            userInterface = std::make_unique<Administrator>();
        }
        else{
            cout<<"Login failed, wrong username or password!\n";
            showDashboard();
        }
        cout<<"ADMIN";
        break;
        case(2):
            cout<<"--- Booking Agent Login ---\n";
            user_Inputs();
        if(user_verify()){
            cout<<"Login successful!\n";
            userInterface = std::make_unique<BookingAgent>();
        }
        else{
            cout<<"Login failed, wrong username or password!\n";
            showDashboard();
        }
        break;
        case(3):
            cout<<"--- Booking Agent Login ---\n";
            user_Inputs();
        if(user_verify()){
            cout<<"Login successful!\n";
            // userInterface = std::make_unique<Passenger>();
        }
        else{
            cout<<"Login failed, wrong username or password!\n";
            showDashboard();
        }
        break;
        default:
        break;
    }
    if(userInterface){
        userInterface->showDashboard();
    }
    showDashboard();
}

void User :: user_Inputs(){
    cout<<"Username: ";
    cin>>username;
    cout<<"Password: ";
    cin>>password;
    cout<<"\n";
}

bool User :: user_verify(){
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