// #include "Flight.hpp"
// #include <iomanip>
// #include "Reservation.hpp"

// string Flight::flightPath = "data/flights.json";
// vector<shared_ptr<Flight>> Flight::flightList = JsonPersistence<Flight>::loadFromJson(flightPath);

// void Flight::showMenu() {
//     cout << "--- Manage Flights ---\n"
//          << "1. Add New Flight\n"
//          << "2. Update Existing Flight\n"
//          << "3. Remove Flight\n"
//          << "4. View All Flights\n"
//          << "5. Back to Main Menu\n";
//     processChoice();
// }

// void Flight::processChoice() {
//     cout << "Enter choice:\n";
//     cin >> flightChoice;
//     switch(flightChoice) {
//         case 1:
//             cout << "--- Add New Flight ---\n";
//             add_flight();
//             break;
//         case 2:
//             cout << "--- Update Existing Flight ---\n";
//             update_flight();
//             break;
//         case 3:
//             cout << "--- Remove Existing Flight ---\n";
//             remove_flight();
//             break;
//         case 4:
//             cout << "--- Existing Flights ---\n";
//             print_flights();
//             break;
//         case 5:
//             return;
//         default:
//             cout << "Invalid choice\n";
//             break;
//     }
//     showMenu();
// }

// void Flight::add_flight() {
//     auto newFlight = make_shared<Flight>();

//     cout << "Enter Flight Number: ";
//     cin >> newFlight->number;
//     cout << "Enter Origin: ";
//     cin.ignore();
//     getline(cin, newFlight->origin);
//     cout << "Enter Destination: ";
//     getline(cin, newFlight->destination);
//     cout << "Enter Departure Date and Time (YYYY-MM-DD HH:MM): ";
//     getline(cin, newFlight->depDateTime);
//     cout << "Enter Arrival Date and Time (YYYY-MM-DD HH:MM): ";
//     getline(cin, newFlight->arrivalDateTime);
//     cout << "Enter Aircraft Type: ";
//     getline(cin, newFlight->type);
//     cout << "Enter Total Seats: ";
//     cin >> newFlight->totalSeats;
//     cin.ignore();
//     cout << "Enter Status (Scheduled/Delayed/Canceled): ";
//     getline(cin, newFlight->status);
//     cout << "Enter Flight Price: ";
//     cin >> flightPrice;
//     cout << "Enter Available seats: ";
//     cin >> availableSeats;

//     flightList.push_back(newFlight);
//     saveFlights();
//     cout << "Flight " << newFlight->number << " has been successfully added to the schedule.\n";
// }

// void Flight::remove_flight() {
//     cout << "Enter Flight Number to remove: \n";
//     cin >> flightNumber;

//     for (auto it = flightList.begin(); it != flightList.end(); ++it) {
//         if (*it && (*it)->number == flightNumber) {
//             flightList.erase(it);
//             saveFlights();
//             cout << "Flight " << flightNumber << " has been successfully removed.\n";
//             print_flights();
//             return;
//         }
//     }
//     cout << "Flight number does not exist.\n";
// }

// void Flight::update_flight() {
//     cout << "Enter Flight Number to Update: \n";
//     cin >> flightNumber;

//     for (auto& flight : flightList) {
//         if (flight && flight->number == flightNumber) {
//             cout << "Select information to update: \n"
//                  << "1. Flight Details \n"
//                  << "2. Crew Assignments \n"
//                  << "3. Status \n"
//                  << "4. Back to Manage Flights \n";
//             cin >> updateChoice;
//             switch(updateChoice) {
//                 case 1:
//                     update_flight_details("details");
//                     return;
//                 case 2:
//                     cout << "2. Crew Assignments (to implement)\n";
//                     assign_crew();
//                     return;
//                 case 3:
//                     update_flight_details("status");
//                     return;
//                 case 4:
//                     return;
//             }
//         }
//     }
//     cout << "Flight number does not exist.\n";
// }

// void Flight::update_flight_details(string type) {
//     for (auto& flight : flightList) {
//         if (flight && flight->number == flightNumber) {
//             int fieldToUpdate;
//             string update;
//             bool updateStatus = false;

//             if(type == "details") {
//                 cout << "Choose the field you want to update: \n"
//                      << "1. Origin \n"
//                      << "2. Destination \n"
//                      << "3. Arrival Date and Time (YYYY-MM-DD HH:MM) \n"
//                      << "4. Departure Date and Time (YYYY-MM-DD HH:MM)  \n"
//                      << "5. Aircraft Type \n"
//                      << "6. Total Seats \n"
//                      << "7. Price\n";
//                 cin >> fieldToUpdate;
//                 cin.ignore();
//                 cout << "Enter the update needed: \n";
//                 getline(cin, update);
//                 switch(fieldToUpdate) {
//                     case 1: flight->origin = update; break;
//                     case 2: flight->destination = update; break;
//                     case 3: flight->arrivalDateTime = update; break;
//                     case 4: flight->depDateTime = update; break;
//                     case 5: flight->type = update; break;
//                     case 6: flight->totalSeats = stoi(update); break;
//                     case 7: flight->flightPrice = update; break;
//                     default: cout << "Invalid choice\n"; return;
//                 }
//                 updateStatus = true;
//             }
//             else {
//                 cin.ignore();
//                 cout << "Enter the update needed: \n";
//                 getline(cin, update);
//                 flight->status = update;
//                 updateStatus = true;
//             }

//             if (updateStatus) {
//                 saveFlights();
//                 cout << "Updated Successfully!\n";
//                 print_flights();
//             }
//             return;
//         }
//     }
// }

// bool Flight::is_flight_available(const string& num) {
//     for (const auto& flight : flightList) {
//         if (flight && flight->number == num) return true;
//     }
//     return false;
// }

// void Flight::print_flights() {
//     int count = 1;
//     for (const auto& flight : flightList) {
//         if (!flight) continue;

//         cout << count++ << ". Flight Number: \"" << flight->number << "\"\n"
//              << "   Origin: \"" << flight->origin << "\"\n"
//              << "   Destination: \"" << flight->destination << "\"\n"
//              << "   Departure Date and Time (YYYY-MM-DD HH:MM): \"" << flight->depDateTime << "\"\n"
//              << "   Arrival Date and Time (YYYY-MM-DD HH:MM): \"" << flight->arrivalDateTime << "\"\n"
//              << "   Aircraft Type: \"" << flight->type << "\"\n"
//              << "   Total Seats: \"" << flight->totalSeats << "\"\n"
//              << "   Status: \"" << flight->status << "\"\n"
//              << "   Pilot: \"" << (flight->pilotName.empty() ? "Unassigned" : flight->pilotName) << "\"\n"
//              << "   Flight Attendant: \"" << (flight->attendantName.empty() ? "Unassigned" : flight->attendantName) << "\"\n\n";
//     }
// }

// string Flight :: getDepartTime(){
//     return depDateTime;
// }

// void Flight::get_flights() {
//     cout << "---Flights---\n";
//     int count = 1;
//     for (const auto& flight : flightList) {
//         if (flight) {
//             cout << count++ << ". Flight Number: \"" << flight->number << "\"\n";
//         }
//     }
// }

// shared_ptr<Flight> Flight::getFlightByNumber(const string& number) {
//     loadFlights(); // Ensure flights are up to date
//     for (auto& flight : flightList) {
//         if (flight && flight->number == number) {
//             return flight;
//         }
//     }
//     return nullptr;
// }


// void Flight::saveFlights() {
//     JsonPersistence<Flight>::saveToJson(flightPath, flightList);
// }

// void Flight::loadFlights() {
//     flightList = JsonPersistence<Flight>::loadFromJson(flightPath);
// }

// json Flight::toJson() const {
//     return {
//         {"number", number},
//         {"origin", origin},
//         {"destination", destination},
//         {"depDateTime", depDateTime},
//         {"arrivalDateTime", arrivalDateTime},
//         {"type", type},
//         {"totalSeats", totalSeats},
//         {"status", status},
//         {"pilotID", pilotID},
//         {"pilotName", pilotName},
//         {"attendantID", attendantID},
//         {"attendantName", attendantName},
//         {"Price", flightPrice},
//         {"availableSeats", availableSeats},
//         {"bookedSeats", bookedSeats} 
//     };
// }

// void Flight::fromJson(const json& j) {
//     number = j.value("number", "");
//     origin = j.value("origin", "");
//     destination = j.value("destination", "");
//     depDateTime = j.value("depDateTime", "");
//     arrivalDateTime = j.value("arrivalDateTime", "");
//     type = j.value("type", "");
//     status = j.value("status", "");
//     if (j.contains("totalSeats")) {
//         if (j["totalSeats"].is_number_integer()) {
//             totalSeats = j["totalSeats"];
//         } else if (j["totalSeats"].is_string()) {
//             totalSeats = stoi(j["totalSeats"].get<std::string>());
//         } else {
//             totalSeats = 0;
//         }
//     } else {
//         totalSeats = 0;
//     }

//     pilotID = j.value("pilotID", "");
//     pilotName = j.value("pilotName", "");
//     attendantID = j.value("attendantID", "");
//     attendantName = j.value("attendantName", "");
//     flightPrice = j.value("Price", "");

//     if (j.contains("availableSeats")) {
//         if (j["availableSeats"].is_number_integer()) {
//             availableSeats = j["availableSeats"];
//         } else if (j["availableSeats"].is_string()) {
//             availableSeats = stoi(j["availableSeats"].get<std::string>());
//         } else {
//             availableSeats = 0;
//         }
//     } else {
//         availableSeats = 0;
//     }
//     if (j.contains("bookedSeats")) {
//         bookedSeats = j["bookedSeats"].get<std::map<std::string, std::string>>();
//     } else {
//         bookedSeats.clear();
//     }
// }

// void Flight::assign_crew() {
//     // 1. Load crew.json
//     ifstream crewFile("data/crew.json");
//     json crewData;
//     crewFile >> crewData;
//     crewFile.close();

//     // 2. Show available pilots
//     cout << "--- Available Pilots ---\n";
//     for (int i = 0; i < crewData.size(); i++) {
//         if (crewData[i]["available"]) {
//             cout << i + 1 << ". " << crewData[i]["pilotID"]
//                  << " - " << crewData[i]["name"] << "\n";
//         }
//     }

//     int pilotChoice;
//     cout << "Select Pilot by Number: ";
//     cin >> pilotChoice;
//     pilotChoice--;

//     auto& chosenPilot = crewData[pilotChoice];
//     string chosenPilotID = chosenPilot["pilotID"];
//     string chosenPilotName = chosenPilot["name"];

//     // 3. Show available attendants for that pilot
//     cout << "--- Available Flight Attendants ---\n";
//     for (int j = 0; j < chosenPilot["attendants"].size(); j++) {
//         if (chosenPilot["attendants"][j]["available"]) {
//             cout << j + 1 << ". "
//                  << chosenPilot["attendants"][j]["id"]
//                  << " - "
//                  << chosenPilot["attendants"][j]["name"] << "\n";
//         }
//     }

//     int attendantChoice;
//     cout << "Select Flight Attendant by Number: ";
//     cin >> attendantChoice;
//     attendantChoice--;

//     string chosenAttID = chosenPilot["attendants"][attendantChoice]["id"];
//     string chosenAttName = chosenPilot["attendants"][attendantChoice]["name"];

//     // 4. Update Flight object in vector
//     for (auto& flight : flightList) {
//         if (flight && flight->number == flightNumber) {
//             flight->pilotID = chosenPilotID;
//             flight->pilotName = chosenPilotName;
//             flight->attendantID = chosenAttID;
//             flight->attendantName = chosenAttName;
//             break;
//         }
//     }

//     // 5. Mark crew as unavailable in crew.json
//     chosenPilot["available"] = false;
//     chosenPilot["attendants"][attendantChoice]["available"] = false;

//     ofstream outCrew("data/crew.json");
//     outCrew << setw(4) << crewData;
//     outCrew.close();

//     // 6. Save updated flights.json
//     saveFlights();

//     cout << "Crew assigned successfully to Flight " << flightNumber << ".\n";
// }


// void Flight::release_crew(const string& flightNum) {
//     for (auto& flight : flightList) {
//         if (flight && flight->number == flightNum && !flight->pilotID.empty()) {
//             // Load crew.json
//             ifstream crewFile("data/crew.json");
//             json crewData;
//             crewFile >> crewData;
//             crewFile.close();

//             // Find pilot and attendant in crew.json and mark available
//             for (auto& pilot : crewData) {
//                 if (pilot["pilotID"] == flight->pilotID) {
//                     pilot["available"] = true;
//                     for (auto& att : pilot["attendants"]) {
//                         if (att["id"] == flight->attendantID) {
//                             att["available"] = true;
//                             break;
//                         }
//                     }
//                     break;
//                 }
//             }

//             ofstream outCrew("data/crew.json");
//             outCrew << setw(4) << crewData;
//             outCrew.close();

//             // Clear flight crew
//             flight->pilotID = "";
//             flight->pilotName = "";
//             flight->attendantID = "";
//             flight->attendantName = "";

//             saveFlights();
//             break;
//         }
//     }
// }

// bool Flight::operator==(const Flight& other) const {
//     return number == other.number;
// }


// void Flight :: search_flights(const string& searchOrigin,const string& searchDestination,const string& searchDate){
//     loadFlights();
//     cout << "\nAvailable Flights:\n";
//     int count = 1;
//     for (const auto& flight : flightList) {
//         if (!flight) continue;

//         string depDateOnly = flight->depDateTime.substr(0, 10);
//         if (flight->origin == searchOrigin &&
//             flight->destination == searchDestination &&
//             depDateOnly == searchDate) 
//         {
//             cout << count++ << ". Flight Number: " << flight->number << "\n"
//                 << "   Departure: " << flight->depDateTime << "\n"
//                 << "   Arrival: " << flight->arrivalDateTime << "\n"
//                 << "   Aircraft: " << flight->type << "\n"
//                 << "   Available Seats: " << flight->availableSeats << "\n"
//                 << "   Price: $" << flight->flightPrice << "\n";
//         }
//     }

//     if (count == 1) {
//         cout << "No flights found matching your criteria.\n";
//     }

// }

// bool Flight::isSeatAvailable(const string& flightNumber, const string& seat) const {
//     auto flight = Flight::getFlightByNumber(flightNumber);
//     if (!flight) return false;

//     return flight->bookedSeats.find(seat) == flight->bookedSeats.end();
// }


// bool Flight::bookSeat(const string& flightNumber, const string& seat, const string& passengerID) {
//     auto flight = Flight::getFlightByNumber(flightNumber);
//     if (!flight) return false;

//     if (passengerID.empty()) {
//         // Cancel reservation
//         flight->bookedSeats.erase(seat);
//         flight->availableSeats += 1;
//     } else {
//         // Check availability
//         if (!flight->isSeatAvailable(flightNumber, seat)){
//             return false;
//         }
//         // Book seat
//         flight->bookedSeats[seat] = passengerID;
//         flight->availableSeats -= 1;
//     }

//     saveFlights(); 
//     return true;
// }


// bool Flight::freeSeat(const std::string& seatNumber) {
//     // 1. Check if the seat is currently booked
//     auto it = bookedSeats.find(seatNumber);
//     if (it == bookedSeats.end()) {
//         std::cout << "Error: Seat " << seatNumber << " is not booked.\n";
//         return false;
//     }

//     // 2. Free the seat
//     bookedSeats.erase(it);
//     availableSeats += 1;

//     // 3. Persist flight data
//     saveFlights();

//     std::cout << "Seat " << seatNumber << " has been freed.\n";
//     return true;
// }

// string Flight::getFlightNumber(){
//     return number;
// }

// void Flight::generateOperationalReport(const std::string& monthYear) {
//     std::cout << "\n--- Operational Reports ---\n";
//     std::cout << "Enter Month and Year for Report (MM-YYYY): " << monthYear << "\n\n";
//     std::cout << "Generating Operational Report for " << monthYear << "...\n\n";

//     int totalFlights = 0;
//     int flightsCompleted = 0;
//     int flightsDelayed = 0;
//     int flightsCanceled = 0;
//     int totalReservations = 0;
//     double totalRevenue = 0.0;

//     std::cout << "Detailed Flight Performance:\n";

//     // ✅ Loop through all flights
//     for (auto& flight : flightList) {
//         totalFlights++;

//         // ✅ Get flight status
//         std::string status = flight->getStatus();
//         if (status == "On Time" || status == "Arrived")
//             flightsCompleted++;
//         else if (status == "Delayed")
//             flightsDelayed++;
//         else if (status == "Canceled")
//             flightsCanceled++;

//         // ✅ Calculate bookings & revenue for this flight
//         int bookings = 0;
//         double revenue = 0.0;

//         for (auto& r : Reservation::reservationList) {
//             if (r && r->getFlightNumber() == flight->getFlightNumber()) {
//                 std::string priceStr = r->getPrice();
//                 if (!priceStr.empty() && priceStr[0] == '$')
//                     priceStr = priceStr.substr(1);  // remove '$'

//                 try {
//                     revenue += std::stod(priceStr);
//                 } catch (...) {
//                     std::cerr << "Warning: Could not parse price for reservation "
//                               << r->getReservationID() << "\n";
//                 }
//                 bookings++;
//             }
//         }

//         totalReservations += bookings;
//         totalRevenue += revenue;

//         std::cout << totalFlights << ". Flight " << flight->getFlightNumber()
//                   << ": " << status << " (" << bookings << " Bookings, $"
//                   << std::fixed << std::setprecision(2) << revenue << ")\n";
//     }

//     // ✅ Print summary
//     std::cout << "\nReport Summary:\n";
//     std::cout << "- Total Flights Scheduled: " << totalFlights << "\n";
//     std::cout << "- Flights Completed: " << flightsCompleted << "\n";
//     std::cout << "- Flights Delayed: " << flightsDelayed << "\n";
//     std::cout << "- Flights Canceled: " << flightsCanceled << "\n";
//     std::cout << "- Total Reservations Made: " << totalReservations << "\n";
//     std::cout << "- Total Revenue: $" << std::fixed << std::setprecision(2)
//               << totalRevenue << "\n";
// }

#include "Flight.hpp"
#include <iomanip>
#include "Reservation.hpp"

// Static variable: Path to JSON file storing flight data
string Flight::flightPath = "data/flights.json";

// Static vector of all flights, loaded from JSON at startup
vector<shared_ptr<Flight>> Flight::flightList = JsonPersistence<Flight>::loadFromJson(flightPath);

void Flight::showMenu() {
    // Display the Manage Flights menu
    cout << "--- Manage Flights ---\n"
         << "1. Add New Flight\n"
         << "2. Update Existing Flight\n"
         << "3. Remove Flight\n"
         << "4. View All Flights\n"
         << "5. Back to Main Menu\n";
    processChoice(); // Process user's choice
}

void Flight::processChoice() {
    // Handle the menu choice for flight management
    cout << "Enter choice:\n";
    cin >> flightChoice;
    switch(flightChoice) {
        case 1:
            cout << "--- Add New Flight ---\n";
            add_flight();
            break;
        case 2:
            cout << "--- Update Existing Flight ---\n";
            update_flight();
            break;
        case 3:
            cout << "--- Remove Existing Flight ---\n";
            remove_flight();
            break;
        case 4:
            cout << "--- Existing Flights ---\n";
            print_flights();
            break;
        case 5:
            return; // Back to main menu
        default:
            cout << "Invalid choice\n";
            break;
    }
    showMenu(); // Show menu again after completing action
}

void Flight::add_flight() {
    // Create and populate a new Flight object
    auto newFlight = make_shared<Flight>();

    cout << "Enter Flight Number: ";
    cin >> newFlight->number;
    cout << "Enter Origin: ";
    cin.ignore();
    getline(cin, newFlight->origin);
    cout << "Enter Destination: ";
    getline(cin, newFlight->destination);
    cout << "Enter Departure Date and Time (YYYY-MM-DD HH:MM): ";
    getline(cin, newFlight->depDateTime);
    cout << "Enter Arrival Date and Time (YYYY-MM-DD HH:MM): ";
    getline(cin, newFlight->arrivalDateTime);
    cout << "Enter Aircraft Type: ";
    getline(cin, newFlight->type);
    cout << "Enter Total Seats: ";
    cin >> newFlight->totalSeats;
    cin.ignore();
    cout << "Enter Status (Scheduled/Delayed/Canceled): ";
    getline(cin, newFlight->status);
    cout << "Enter Flight Price: ";
    cin >> flightPrice;
    cout << "Enter Available seats: ";
    cin >> availableSeats;

    // Add to static flight list and save to JSON
    flightList.push_back(newFlight);
    saveFlights();
    cout << "Flight " << newFlight->number << " has been successfully added to the schedule.\n";
}

void Flight::remove_flight() {
    // Remove flight by number
    cout << "Enter Flight Number to remove: \n";
    cin >> flightNumber;

    for (auto it = flightList.begin(); it != flightList.end(); ++it) {
        if (*it && (*it)->number == flightNumber) {
            flightList.erase(it);
            saveFlights();
            cout << "Flight " << flightNumber << " has been successfully removed.\n";
            print_flights();
            return;
        }
    }
    cout << "Flight number does not exist.\n";
}

void Flight::update_flight() {
    // Update flight info by flight number
    cout << "Enter Flight Number to Update: \n";
    cin >> flightNumber;

    for (auto& flight : flightList) {
        if (flight && flight->number == flightNumber) {
            cout << "Select information to update: \n"
                 << "1. Flight Details \n"
                 << "2. Crew Assignments \n"
                 << "3. Status \n"
                 << "4. Back to Manage Flights \n";
            cin >> updateChoice;
            switch(updateChoice) {
                case 1:
                    update_flight_details("details");
                    return;
                case 2:
                    cout << "2. Crew Assignments (to implement)\n";
                    assign_crew();
                    return;
                case 3:
                    update_flight_details("status");
                    return;
                case 4:
                    return;
            }
        }
    }
    cout << "Flight number does not exist.\n";
}

void Flight::update_flight_details(string type) {
    // Update either flight details or status based on type
    for (auto& flight : flightList) {
        if (flight && flight->number == flightNumber) {
            int fieldToUpdate;
            string update;
            bool updateStatus = false;

            if(type == "details") {
                // Show fields for details update
                cout << "Choose the field you want to update: \n"
                     << "1. Origin \n"
                     << "2. Destination \n"
                     << "3. Arrival Date and Time (YYYY-MM-DD HH:MM) \n"
                     << "4. Departure Date and Time (YYYY-MM-DD HH:MM)  \n"
                     << "5. Aircraft Type \n"
                     << "6. Total Seats \n"
                     << "7. Price\n";
                cin >> fieldToUpdate;
                cin.ignore();
                cout << "Enter the update needed: \n";
                getline(cin, update);
                switch(fieldToUpdate) {
                    case 1: flight->origin = update; break;
                    case 2: flight->destination = update; break;
                    case 3: flight->arrivalDateTime = update; break;
                    case 4: flight->depDateTime = update; break;
                    case 5: flight->type = update; break;
                    case 6: flight->totalSeats = stoi(update); break;
                    case 7: flight->flightPrice = update; break;
                    default: cout << "Invalid choice\n"; return;
                }
                updateStatus = true;
            }
            else {
                // Status update
                cin.ignore();
                cout << "Enter the update needed: \n";
                getline(cin, update);
                flight->status = update;
                updateStatus = true;
            }

            if (updateStatus) {
                saveFlights();
                cout << "Updated Successfully!\n";
                print_flights();
            }
            return;
        }
    }
}

bool Flight::is_flight_available(const string& num) {
    // Check if a flight exists by number
    for (const auto& flight : flightList) {
        if (flight && flight->number == num) return true;
    }
    return false;
}

void Flight::print_flights() {
    // Print all flights in the list
    int count = 1;
    for (const auto& flight : flightList) {
        if (!flight) continue;

        cout << count++ << ". Flight Number: \"" << flight->number << "\"\n"
             << "   Origin: \"" << flight->origin << "\"\n"
             << "   Destination: \"" << flight->destination << "\"\n"
             << "   Departure Date and Time (YYYY-MM-DD HH:MM): \"" << flight->depDateTime << "\"\n"
             << "   Arrival Date and Time (YYYY-MM-DD HH:MM): \"" << flight->arrivalDateTime << "\"\n"
             << "   Aircraft Type: \"" << flight->type << "\"\n"
             << "   Total Seats: \"" << flight->totalSeats << "\"\n"
             << "   Status: \"" << flight->status << "\"\n"
             << "   Pilot: \"" << (flight->pilotName.empty() ? "Unassigned" : flight->pilotName) << "\"\n"
             << "   Flight Attendant: \"" << (flight->attendantName.empty() ? "Unassigned" : flight->attendantName) << "\"\n\n";
    }
}

string Flight :: getDepartTime(){
    return depDateTime; // Return departure time of this flight
}

void Flight::get_flights() {
    // Print flight numbers only
    cout << "---Flights---\n";
    int count = 1;
    for (const auto& flight : flightList) {
        if (flight) {
            cout << count++ << ". Flight Number: \"" << flight->number << "\"\n";
        }
    }
}

shared_ptr<Flight> Flight::getFlightByNumber(const string& number) {
    // Return a flight pointer by flight number
    loadFlights(); // Ensure flights are up to date
    for (auto& flight : flightList) {
        if (flight && flight->number == number) {
            return flight;
        }
    }
    return nullptr;
}

// ------------------------- JSON Persistence -------------------------

void Flight::saveFlights() {
    // Save flights vector to JSON
    JsonPersistence<Flight>::saveToJson(flightPath, flightList);
}

void Flight::loadFlights() {
    // Load flights from JSON file
    flightList = JsonPersistence<Flight>::loadFromJson(flightPath);
}

json Flight::toJson() const {
    // Serialize Flight object to JSON
    return {
        {"number", number},
        {"origin", origin},
        {"destination", destination},
        {"depDateTime", depDateTime},
        {"arrivalDateTime", arrivalDateTime},
        {"type", type},
        {"totalSeats", totalSeats},
        {"status", status},
        {"pilotID", pilotID},
        {"pilotName", pilotName},
        {"attendantID", attendantID},
        {"attendantName", attendantName},
        {"Price", flightPrice},
        {"availableSeats", availableSeats},
        {"bookedSeats", bookedSeats} 
    };
}

void Flight::fromJson(const json& j) {
    // Deserialize Flight object from JSON
    number = j.value("number", "");
    origin = j.value("origin", "");
    destination = j.value("destination", "");
    depDateTime = j.value("depDateTime", "");
    arrivalDateTime = j.value("arrivalDateTime", "");
    type = j.value("type", "");
    status = j.value("status", "");
    if (j.contains("totalSeats")) {
        if (j["totalSeats"].is_number_integer()) {
            totalSeats = j["totalSeats"];
        } else if (j["totalSeats"].is_string()) {
            totalSeats = stoi(j["totalSeats"].get<std::string>());
        } else {
            totalSeats = 0;
        }
    } else {
        totalSeats = 0;
    }

    pilotID = j.value("pilotID", "");
    pilotName = j.value("pilotName", "");
    attendantID = j.value("attendantID", "");
    attendantName = j.value("attendantName", "");
    flightPrice = j.value("Price", "");

    if (j.contains("availableSeats")) {
        if (j["availableSeats"].is_number_integer()) {
            availableSeats = j["availableSeats"];
        } else if (j["availableSeats"].is_string()) {
            availableSeats = stoi(j["availableSeats"].get<std::string>());
        } else {
            availableSeats = 0;
        }
    } else {
        availableSeats = 0;
    }
    if (j.contains("bookedSeats")) {
        bookedSeats = j["bookedSeats"].get<std::map<std::string, std::string>>();
    } else {
        bookedSeats.clear();
    }
}

// ------------------------- Crew Management -------------------------

void Flight::assign_crew() {
    // Assign pilot and attendant to a flight
    ifstream crewFile("data/crew.json");
    json crewData;
    crewFile >> crewData;
    crewFile.close();

    // Show available pilots
    cout << "--- Available Pilots ---\n";
    for (int i = 0; i < crewData.size(); i++) {
        if (crewData[i]["available"]) {
            cout << i + 1 << ". " << crewData[i]["pilotID"]
                 << " - " << crewData[i]["name"] << "\n";
        }
    }

    int pilotChoice;
    cout << "Select Pilot by Number: ";
    cin >> pilotChoice;
    pilotChoice--;

    auto& chosenPilot = crewData[pilotChoice];
    string chosenPilotID = chosenPilot["pilotID"];
    string chosenPilotName = chosenPilot["name"];

    // Show available attendants for the chosen pilot
    cout << "--- Available Flight Attendants ---\n";
    for (int j = 0; j < chosenPilot["attendants"].size(); j++) {
        if (chosenPilot["attendants"][j]["available"]) {
            cout << j + 1 << ". "
                 << chosenPilot["attendants"][j]["id"]
                 << " - "
                 << chosenPilot["attendants"][j]["name"] << "\n";
        }
    }

    int attendantChoice;
    cout << "Select Flight Attendant by Number: ";
    cin >> attendantChoice;
    attendantChoice--;

    string chosenAttID = chosenPilot["attendants"][attendantChoice]["id"];
    string chosenAttName = chosenPilot["attendants"][attendantChoice]["name"];

    // Update the flight's crew
    for (auto& flight : flightList) {
        if (flight && flight->number == flightNumber) {
            flight->pilotID = chosenPilotID;
            flight->pilotName = chosenPilotName;
            flight->attendantID = chosenAttID;
            flight->attendantName = chosenAttName;
            break;
        }
    }

    // Mark crew as unavailable in crew.json
    chosenPilot["available"] = false;
    chosenPilot["attendants"][attendantChoice]["available"] = false;

    ofstream outCrew("data/crew.json");
    outCrew << setw(4) << crewData;
    outCrew.close();

    // Save updated flights.json
    saveFlights();

    cout << "Crew assigned successfully to Flight " << flightNumber << ".\n";
}

void Flight::release_crew(const string& flightNum) {
    // Release assigned crew back to availability
    for (auto& flight : flightList) {
        if (flight && flight->number == flightNum && !flight->pilotID.empty()) {
            ifstream crewFile("data/crew.json");
            json crewData;
            crewFile >> crewData;
            crewFile.close();

            // Mark pilot and attendant as available
            for (auto& pilot : crewData) {
                if (pilot["pilotID"] == flight->pilotID) {
                    pilot["available"] = true;
                    for (auto& att : pilot["attendants"]) {
                        if (att["id"] == flight->attendantID) {
                            att["available"] = true;
                            break;
                        }
                    }
                    break;
                }
            }

            ofstream outCrew("data/crew.json");
            outCrew << setw(4) << crewData;
            outCrew.close();

            // Clear flight's crew info
            flight->pilotID = "";
            flight->pilotName = "";
            flight->attendantID = "";
            flight->attendantName = "";

            saveFlights();
            break;
        }
    }
}

// ------------------------- Booking & Seat Management -------------------------

bool Flight::operator==(const Flight& other) const {
    return number == other.number; // Compare flights by number
}

void Flight :: search_flights(const string& searchOrigin,const string& searchDestination,const string& searchDate){
    // Search for flights matching origin, destination, and departure date
    loadFlights();
    cout << "\nAvailable Flights:\n";
    int count = 1;
    for (const auto& flight : flightList) {
        if (!flight) continue;

        string depDateOnly = flight->depDateTime.substr(0, 10);
        if (flight->origin == searchOrigin &&
            flight->destination == searchDestination &&
            depDateOnly == searchDate) 
        {
            cout << count++ << ". Flight Number: " << flight->number << "\n"
                << "   Departure: " << flight->depDateTime << "\n"
                << "   Arrival: " << flight->arrivalDateTime << "\n"
                << "   Aircraft: " << flight->type << "\n"
                << "   Available Seats: " << flight->availableSeats << "\n"
                << "   Price: $" << flight->flightPrice << "\n";
        }
    }

    if (count == 1) {
        cout << "No flights found matching your criteria.\n";
    }

}

bool Flight::isSeatAvailable(const string& flightNumber, const string& seat) const {
    // Check if a seat is free on a specific flight
    auto flight = Flight::getFlightByNumber(flightNumber);
    if (!flight) return false;

    return flight->bookedSeats.find(seat) == flight->bookedSeats.end();
}

bool Flight::bookSeat(const string& flightNumber, const string& seat, const string& passengerID) {
    // Book or free a seat on a flight
    auto flight = Flight::getFlightByNumber(flightNumber);
    if (!flight) return false;

    if (passengerID.empty()) {
        // Cancel reservation
        flight->bookedSeats.erase(seat);
        flight->availableSeats += 1;
    } else {
        // Check availability
        if (!flight->isSeatAvailable(flightNumber, seat)){
            return false;
        }
        // Book seat
        flight->bookedSeats[seat] = passengerID;
        flight->availableSeats -= 1;
    }

    saveFlights(); 
    return true;
}

bool Flight::freeSeat(const std::string& seatNumber) {
    // Free a seat in the current flight instance
    auto it = bookedSeats.find(seatNumber);
    if (it == bookedSeats.end()) {
        std::cout << "Error: Seat " << seatNumber << " is not booked.\n";
        return false;
    }

    bookedSeats.erase(it);
    availableSeats += 1;
    saveFlights();

    std::cout << "Seat " << seatNumber << " has been freed.\n";
    return true;
}

string Flight::getFlightNumber(){
    return number; // Return flight number
}

// ------------------------- Reports -------------------------

void Flight::generateOperationalReport(const std::string& monthYear) {
    // Generate an operational report for the specified month-year
    std::cout << "\n--- Operational Reports ---\n";
    std::cout << "Enter Month and Year for Report (MM-YYYY): " << monthYear << "\n\n";
    std::cout << "Generating Operational Report for " << monthYear << "...\n\n";

    int totalFlights = 0;
    int flightsCompleted = 0;
    int flightsDelayed = 0;
    int flightsCanceled = 0;
    int totalReservations = 0;
    double totalRevenue = 0.0;

    std::cout << "Detailed Flight Performance:\n";

    // Loop through all flights to calculate stats
    for (auto& flight : flightList) {
        totalFlights++;

        std::string status = flight->getStatus();
        if (status == "On Time" || status == "Arrived")
            flightsCompleted++;
        else if (status == "Delayed")
            flightsDelayed++;
        else if (status == "Canceled")
            flightsCanceled++;

        int bookings = 0;
        double revenue = 0.0;

        for (auto& r : Reservation::reservationList) {
            if (r && r->getFlightNumber() == flight->getFlightNumber()) {
                std::string priceStr = r->getPrice();
                if (!priceStr.empty() && priceStr[0] == '$')
                    priceStr = priceStr.substr(1);

                try {
                    revenue += std::stod(priceStr);
                } catch (...) {
                    std::cerr << "Warning: Could not parse price for reservation "
                              << r->getReservationID() << "\n";
                }
                bookings++;
            }
        }

        totalReservations += bookings;
        totalRevenue += revenue;

        std::cout << totalFlights << ". Flight " << flight->getFlightNumber()
                  << ": " << status << " (" << bookings << " Bookings, $"
                  << std::fixed << std::setprecision(2) << revenue << ")\n";
    }

    // Print summary
    std::cout << "\nReport Summary:\n";
    std::cout << "- Total Flights Scheduled: " << totalFlights << "\n";
    std::cout << "- Flights Completed: " << flightsCompleted << "\n";
    std::cout << "- Flights Delayed: " << flightsDelayed << "\n";
    std::cout << "- Flights Canceled: " << flightsCanceled << "\n";
    std::cout << "- Total Reservations Made: " << totalReservations << "\n";
    std::cout << "- Total Revenue: $" << std::fixed << std::setprecision(2)
              << totalRevenue << "\n";
}
