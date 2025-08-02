#ifndef AIRCRAFT_H
#define AIRCRAFT_H

#include<iostream>
#include<string>

#include <fstream>
#include <string>
#include <filesystem> 
#include <nlohmann/json.hpp>
#include <functional>  

#include "MenuInterface.hpp"
#include "jsonpersistence.hpp"

using namespace std;
namespace fs = std::filesystem;
using json = nlohmann::json;

// Aircraft class represents an aircraft entity in the airline system.
// It allows adding, viewing, updating, deleting, and managing aircraft records.
// It also integrates JSON persistence for saving and loading aircraft data.
class Aircraft : public MenuInterface, public JsonPersistence<Aircraft> {
private:
    // Stores the user's menu choice in aircraft management
    int aircraftChoice;

    // Basic aircraft attributes
    std::string aircraftID;             // Unique ID of the aircraft
    std::string model;                  // Model of the aircraft (e.g., Boeing 737)
    int totalSeats;                     // Total number of seats available
    bool available;                     // Availability status for assignment to flights
    std::string lastMaintenanceDate;    // Last maintenance date in YYYY-MM-DD format

    // Static vector that stores all aircraft in memory
    static std::vector<std::shared_ptr<Aircraft>> aircraftFleet;

    // CRUD operations for aircraft management
    static void addAircraft();                 // Add a new aircraft to the fleet
    static void viewAircraft();                // View all aircraft in the fleet
    static void updateAircraft(const std::string& id);  // Update details of a specific aircraft
    static void deleteAircraft(const std::string& id);  // Delete an aircraft by ID

public:
    // Menu interface functions
    void showMenu() override;          // Display the aircraft management menu
    void processChoice() override;     // Handle the user's menu choice

    // JSON persistence functions
    json toJson() const override;                // Convert aircraft object to JSON
    void fromJson(const json& j) override;       // Populate aircraft object from JSON
    static void saveAircrafts();                 // Save all aircraft to JSON file
    static void loadAircrafts();                 // Load all aircraft from JSON file

    // Utility functions
    std::string getID() const;                   // Return the aircraft ID
    bool operator==(const Aircraft& other) const; // Compare aircraft by ID

    // Status and maintenance functions
    void setAvailability(bool status);          // Set the availability status
    bool isAvailable() const;                   // Check if the aircraft is available
    void assignToFlight();                      // Placeholder for assigning aircraft to a flight
    void performMaintenance(std::string date);  // Placeholder for performing maintenance
};

#endif
