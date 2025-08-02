// #ifndef RESERVATION_H
// #define RESERVATION_H

// // Reservation.hpp

// #include <string>
// #include <vector>
// #include <memory>
// #include <nlohmann/json.hpp>
// #include "JsonPersistence.hpp"
// #include "Payment.hpp"

// using std::string;
// using std::vector;
// using std::shared_ptr;
// using json = nlohmann::json;


// class Reservation : public JsonPersistence<Reservation>{
//     private:
//         string reservationID ;
//         string passengerID;
//         string passengerName;
//         string flightNumber;
//         string origin;
//         string destination;
//         string seatNumber;
//         string price;
//         Payment payment;
//         string status = "Confirmed";
//         string depTime;

//         static string reservationPath;

//     public:
//         static bool createReservation(
//             const string& passengerID,
//             const string& flightNumber,
//             const string& seatNumber,
//             const Payment& payment
//         );
//         static vector<shared_ptr<Reservation>> reservationList;

//         static bool modifyReservation(const string& resID, const string& newSeat);
//         static bool cancelReservation(const string& resID);
//         static void saveCleanedReservations();
//         bool operator==(const Reservation& other) const;
//         json toJson() const override;
//         void fromJson(const json& j) override;
//         static void saveReservations();
//         static void reloadReservationsInPlace();
//         void findReservations(const string& ID);
//         void setStatus(string stat);
//         static const std::vector<std::shared_ptr<Reservation>>& getReservations();
//         const std::string& getFlightNumber() const { return flightNumber; }
//         const std::string& getPrice() const { return price; }
//         std::string getReservationID() const { return reservationID; }


// };

// #endif

#ifndef RESERVATION_H
#define RESERVATION_H

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <nlohmann/json.hpp>
#include <filesystem>
#include <iomanip>

#include "Payment.hpp"

namespace fs = std::filesystem;
using json = nlohmann::json;
using namespace std;

class Reservation {
private:
    string reservationID;
    string passengerID;
    string flightNumber;
    string seatNumber;
    string price;
    string paymentMethod;

    static inline const string filePath = "Data/reservations.json";

    static string generateReservationID();

protected: 

public:
    Reservation() = default;
    Reservation(string resID, string pID, string fNumber, string seat, string price, string method)
        : reservationID(resID), passengerID(pID), flightNumber(fNumber),
          seatNumber(seat), price(price), paymentMethod(method) {}
    
    static std::vector<std::shared_ptr<Reservation>> reservationList; // Add this
    // ✅ Public getters
    std::string getReservationID() const { return reservationID; }
    std::string getFlightNumber() const { return flightNumber; }
    std::string getPrice() const { return price; }

    bool createReservation(const string& pID, const string& fNumber, const string& seat, const Payment& pay);
    void modifyReservation(const string& resID, const string& newSeat);
    void cancelReservation(const string& resID);
    void findReservations(const string& pID);

    json toJson() const;
    void fromJson(const json& j);
};

#endif
