#include"BookingAgent.hpp"
#include"Flight.hpp"
#include "Payment.hpp"
#include "Reservation.hpp"

// Display the booking agent menu and handle choices
void BookingAgent :: showMenu(){
    std::cout<<"--- Booking Agent Menu ---\n"
        <<"1. Search Flights\n"
        <<"2. Book a Flight\n"
        <<"3. Modify Reservation\n"
        <<"4. Cancel Reservation\n"
        <<"5. Logout\n";
    processChoice(); // Immediately process user input after showing the menu
}

// Handles the actions chosen by the booking agent
void BookingAgent :: processChoice(){
    cout<<"Enter choice:\n";
    cin>>bookingChoice;

    // Local objects for handling flights and reservations
    Flight flightManager;
    Reservation res;

    // Temporary variables to store input values
    std::string pID, pName, fNumber, seat;
    std::string method;
    string resID, newSeat;
    double amount;

    // Switch statement to handle each menu option
    switch(bookingChoice) {
        case(1):
            // Search Flights
            cin.ignore(); // Clear newline before getline
            cout<<"Enter origin of flight: \n";
            getline(cin, origin);
            cout<<"Enter Destination of the flight: \n";
            getline(cin, dest);
            cout<<"Enter departure date of the flight: \n";
            cin>>date;
            flightManager.search_flights(origin, dest, date);
            break;

        case(2):{
            // Book a Flight - Create Reservation
            std::cout << "--- Create Reservation ---\n";
            std::cout << "Enter Passenger ID: ";
            std::cin >> pID;
            std::cin.ignore(); // Clear newline before getline
            std::cout << "Enter Passenger Name: ";
            std::getline(std::cin, pName);
            std::cout << "Enter Flight Number: ";
            std::cin >> fNumber;
            std::cout << "Enter Seat Number: ";
            std::cin >> seat;

            // Collect Payment Information
            std::cout << "Enter Payment Method (e.g., Card/Cash): ";
            std::cin >> method;

            // Create Payment object
            Payment pay(method, amount);

            // Create Reservation
            if (res.createReservation(pID, fNumber, seat, pay)) {
                std::cout << "Reservation successfully created!\n";
            } else {
                std::cout << "Reservation failed.\n";
            }
            break;
        }

        case (3): 
            // Modify an existing reservation
            cout << "--- Modify Reservation ---\n";
            cout << "Enter Reservation ID to modify: ";
            cin >> resID;
            cout << "Enter New Seat Number: ";
            cin >> newSeat;
            res.modifyReservation(resID, newSeat);
            break;

        case (4): 
            // Cancel an existing reservation
            cout << "--- Cancel Reservation ---\n";
            cout << "Enter Reservation ID to cancel: ";
            cin >> resID;
            res.cancelReservation(resID);
            break;

        case(5):
            // Logout and log activity
            User::logActivity(getID(), "Logged Out");
            return;
            break;

        default:
            // Handle invalid choices
            cout<<"default";
            break;
    }

    // Show the menu again after completing an action
    showMenu();
}
