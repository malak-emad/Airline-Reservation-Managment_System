#include "Administrator.hpp"
#include "Flight.hpp"



void Administrator :: showDashboard(){
    std::cout<<"--- Administrator Menu ---\n"
        <<"1. Manage Flights\n"
        <<"2. Manage Aircraft\n"
        <<"3. Manage Users\n"
        <<"4. Generate Reports\n"
        <<"5. Logout\n";

    process();
}

void Administrator :: process(){
    cout<<"Enter choice:\n";
    cin>>adminChoice;
    if (adminChoice == 1) {
        menu = std::make_unique<Flight>();
        menu ->showMenu();
        cout<<"manage flight";
    } else if (adminChoice == 2) {
        // aircraft_showDashboard();
        cout<<"manage aircraft";
    } else if (adminChoice == 3) {
        // user_showDashboard();
        cout<<"manage users";
    } else {
        cout<<"logout";
        return ;
    }
    showDashboard();

}