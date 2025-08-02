#include "Reservation.hpp"
std::vector<std::shared_ptr<Reservation>> Reservation::reservationList = {};

// Generate unique ReservationID (e.g., R001, R002)
string Reservation::generateReservationID() {
    int count = 1;
    ifstream file(filePath);
    if (file.is_open()) {
        json j;
        file >> j;
        count = j.size() + 1;
    }
    return "R" + to_string(count);
}

// Convert Reservation to JSON
json Reservation::toJson() const {
    return {
        {"reservationID", reservationID},
        {"passengerID", passengerID},
        {"flightNumber", flightNumber},
        {"seatNumber", seatNumber},
        {"price", price},
        {"paymentMethod", paymentMethod}
    };
}

// Load JSON to Reservation
void Reservation::fromJson(const json& j) {
    reservationID = j.value("reservationID", "");
    passengerID   = j.value("passengerID", "");
    flightNumber  = j.value("flightNumber", "");
    seatNumber    = j.value("seatNumber", "");
    price         = j.value("price", "");
    paymentMethod = j.value("paymentMethod", "");
}

// ---------------- CREATE RESERVATION ----------------
bool Reservation::createReservation(const string& pID, const string& fNumber, const string& seat, const Payment& pay) {
    reservationID = generateReservationID();
    passengerID   = pID;
    flightNumber  = fNumber;
    seatNumber    = seat;
    price         = "$" + to_string(static_cast<int>(pay.getAmount()));  // Assuming Payment has getAmount()
    paymentMethod = pay.getMethod();

    // Load existing reservations
    json j;
    ifstream inFile(filePath);
    if (inFile.is_open()) inFile >> j;

    // Append new reservation
    j.push_back(this->toJson());

    // Save back
    ofstream outFile(filePath);
    outFile << setw(4) << j;

    cout << "\nBooking successful! \n"
         << "Reservation ID: " << reservationID << "\n"
         << "Flight: " << flightNumber << "\n"
         << "Seat: " << seatNumber << "\n"
         << "Total Cost: " << price << "\n"
         << "Payment Method: " << paymentMethod << "\n";

    return true;
}

// ---------------- MODIFY RESERVATION ----------------
void Reservation::modifyReservation(const string& resID, const string& newSeat) {
    json j;
    ifstream inFile(filePath);
    if (!inFile.is_open()) {
        cout << "No reservations found.\n";
        return;
    }
    inFile >> j;

    bool found = false;
    for (auto& item : j) {
        if (item["reservationID"] == resID) {
            item["seatNumber"] = newSeat;
            found = true;
            break;
        }
    }

    if (found) {
        ofstream outFile(filePath);
        outFile << setw(4) << j;
        cout << "Reservation " << resID << " updated to seat " << newSeat << ".\n";
    } else {
        cout << "Reservation not found.\n";
    }
}

// ---------------- CANCEL RESERVATION ----------------
void Reservation::cancelReservation(const string& resID) {
    json j;
    ifstream inFile(filePath);
    if (!inFile.is_open()) {
        cout << "No reservations found.\n";
        return;
    }
    inFile >> j;

    size_t beforeSize = j.size();
    j.erase(remove_if(j.begin(), j.end(), [&](const json& item){
        return item["reservationID"] == resID;
    }), j.end());

    if (j.size() < beforeSize) {
        ofstream outFile(filePath);
        outFile << setw(4) << j;
        cout << "Reservation " << resID << " canceled.\n";
    } else {
        cout << "Reservation not found.\n";
    }
}

// ---------------- FIND RESERVATIONS ----------------
void Reservation::findReservations(const string& pID) {
    json j;
    ifstream inFile(filePath);
    if (!inFile.is_open()) {
        cout << "No reservations available.\n";
        return;
    }
    inFile >> j;

    bool found = false;
    for (const auto& item : j) {
        if (item["passengerID"] == pID) {
            cout << "Reservation ID: " << item["reservationID"] << "\n"
                 << "Flight: " << item["flightNumber"] << "\n"
                 << "Seat: " << item["seatNumber"] << "\n"
                 << "Price: " << item["price"] << "\n"
                 << "Payment: " << item["paymentMethod"] << "\n"
                 << "------------------------\n";
            found = true;
        }
    }
    if (!found) cout << "No reservations found for this passenger.\n";
}
