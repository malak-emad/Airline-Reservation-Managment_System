#include"BookingAgent.hpp"
#include"Flight.hpp"


void BookingAgent :: showDashboard(){
    std::cout<<"--- Booking Agent Menu ---\n"
        <<"1. Search Flights\n"
        <<"2. Book a Flight\n"
        <<"3. Modify Reservation\n"
        <<"4. Cancel Reservation\n"
        <<"5. Logout\n";

    process();
}

void BookingAgent :: process(){
    cout<<"Enter choice:\n";
    cin>>bookingChoice;
    Flight flightManager;
    switch(bookingChoice) {
        case(1):
        flightManager.get_flights();
        break;
        case(2):
        cout<<"2. Book a Flight\n";
        // reservation.bookFlight(); reservation should access the users and flight files 
        break;
        case(3):
        cout<<"3. Modify Reservation\n";
        // reservation.modifyReservation(); reservation should access the users and flight files 
        break;
        case(4):
        cout<<"4. Cancel Reservation\n";
        // reservation.cancelReservation(); reservation should access the users and flight files 
        break;
        case(5):
        return;
        break;
        default:
        cout<<"default";
        break;
    }
showDashboard();
}

