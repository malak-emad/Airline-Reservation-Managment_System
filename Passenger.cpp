#include "Passenger.hpp"
#include "Reservation.hpp"
#include "Flight.hpp"

// --- Passenger Menu Display ---
void Passenger::showMenu() {
    std::cout << "--- Passenger Menu ---\n"
              << "1. Search Flights\n"
              << "2. View My Reservations\n"
              << "3. Check-In\n"
              << "4. Logout\n";
    processChoice();
}

// --- Passenger Menu Logic ---
void Passenger::processChoice() {
    cout << "Enter choice:\n";
    cin >> passengerChoice;

    // Declare all needed variables
    string flightNumber;
    string seatNum, method, paymentDetails, passengerID, dest, origin, date;
    double amount = 0.0;  // Initialize amount to avoid undefined behavior

    Reservation res;      // Object to manage reservations
    Flight flightManager; // Object to search and manage flights

    switch (passengerChoice) {

        // --- Case 1: Search & Book Flight ---
        case 1: {
            cout << "--- Searching for Flights ---\n";
            cin.ignore();

            // Get search criteria from the user
            cout << "Enter origin of flight: \n";
            getline(cin, origin);
            cout << "Enter Destination of the flight: \n";
            getline(cin, dest);
            cout << "Enter departure date of the flight (YYYY-MM-DD): \n";
            cin >> date;

            // Search flights based on origin, destination, and date
            flightManager.search_flights(origin, dest, date);

            // Ask the user to choose a flight
            cout << "Enter the Flight Number you wish to book (or '0' to cancel): \n";
            cin >> flightNumber;
            if (flightNumber == "0") {
                return;  // Cancel booking
            }

            // Get the selected flight and extract its price
            auto selectedFlight = Flight::getFlightByNumber(flightNumber);
            if (selectedFlight) {
                try {
                    std::string priceStr = selectedFlight->getPrice();
                    if (!priceStr.empty() && priceStr[0] == '$')
                        priceStr = priceStr.substr(1);  // remove '$' if present
                    amount = std::stod(priceStr);       // convert to double
                } catch (...) {
                    amount = 0.0;
                    std::cerr << "Warning: Could not parse flight price, defaulting to $0.0\n";
                }
            } else {
                std::cout << "Invalid Flight Number.\n";
                return;
            }

            // Collect booking details
            cout << "Enter Seat Number (e.g., 14C): \n";
            cin >> seatNum;
            cout << "Enter Payment Method (Credit Card/Cash/PayPal): \n";
            cin >> method;
            cout << "Enter Payment Details: \n";
            cin >> paymentDetails;

            // Create a payment object
            passengerID = getID();
            Payment pay(method, amount);

            // Attempt to create reservation
            if (res.createReservation(passengerID, flightNumber, seatNum, pay)) {
                std::cout << "Reservation successfully created!\n";
                User::logActivity(passengerID, "Booked Flight " + flightNumber);
            } else {
                std::cout << "Reservation failed.\n";
            }
            break;
        }

        // --- Case 2: View My Reservations ---
        case 2:
            passengerID = getID();
            cout << " --- View Reservations ---\n";
            res.findReservations(passengerID);
            User::logActivity(passengerID, "Viewed Reservations");
            break;

        // --- Case 3: Check-In (to implement later) ---
        case 3:
            cout << "3. Check-In\n";
            break;

        // --- Case 4: Logout ---
        case 4:
            cout << "4. Logout\n";
            User::logActivity(getID(), "Logged Out");
            return;

        // --- Default: Invalid Choice ---
        default:
            cout << "Invalid choice. Please try again.\n";
            break;
    }
}
