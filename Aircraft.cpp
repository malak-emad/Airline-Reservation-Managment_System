#include "Aircraft.hpp"

// Initialize static vector that contains pointers to all Aircraft objects in the fleet
// Load the list from JSON file when the program starts
std::vector<std::shared_ptr<Aircraft>> Aircraft::aircraftFleet =
    JsonPersistence<Aircraft>::loadFromJson("data/aircrafts.json");

// Display the aircraft management menu for the administrator
void Aircraft :: showMenu() {
    cout<<"--- Manage Aircraft --- \n"
        <<"1. View Aircraft \n"
        <<"2. Add Aircraft \n"
        <<"3. Update Aircraft \n"
        <<"4. Delete Aircraft \n"
        <<"5. Back to Admin Menu \n";
    processChoice();
}

// Process user input for the aircraft management menu
void Aircraft :: processChoice()  {
    cout << "Enter choice: \n";
    cin >> aircraftChoice;
    std::string temp; // temporary variable to hold user input like Aircraft ID
    switch(aircraftChoice){
        case(1):
        cout<<"1. View Aircraft \n";
        viewAircraft(); // Display all aircraft in the fleet
        break;
        case(2):
        cout<<"2. Add Aircraft \n";
        addAircraft(); // Add a new aircraft
        break;
        case(3):
        cout<<"3. Update Aircraft \n";
        cout<<"Enter Aircraft ID: \n";
        cin>>temp;
        updateAircraft(temp); // Update existing aircraft details
        break;
        case(4):
        cout<<"4. Delete Aircraft \n";
        cout<<"Enter Aircraft ID: \n";
        cin>>temp;
        deleteAircraft(temp); // Remove aircraft from fleet
        break;
        case(5):
        cout<<"5. Back to Admin Menu \n";
        return; // Exit to previous menu
        break;
    }
}

// Convert the Aircraft object to JSON format for saving to file
json Aircraft :: toJson() const {
    return {
        {"aircraftID" , aircraftID},
        {"aircraftMode" , model}, // NOTE: Key typo here: "aircraftMode" instead of "model"
        {"totalSeats", totalSeats},
        {"available", available},
        {"lastMaintenanceDate", lastMaintenanceDate}
    };
}

// Populate an Aircraft object from a JSON object
void Aircraft :: fromJson(const json& j) {
    aircraftID = j.value("aircraftID", "");
    model = j.value("model", ""); // Reads model from JSON
    totalSeats = j.value("totalSeats", 0);
    available = j.value("available", true);
    lastMaintenanceDate = j.value("lastMaintenanceDate", "");
}

// Save all aircraft in the fleet to the JSON file
void Aircraft :: saveAircrafts(){
    JsonPersistence<Aircraft>::saveToJson("data/aircrafts.json", aircraftFleet);
}

// Load all aircraft from the JSON file into memory
void Aircraft :: loadAircrafts(){
    aircraftFleet = JsonPersistence<Aircraft>::loadFromJson("data/aircrafts.json");
}

// Return the aircraft ID
std::string Aircraft :: getID() const {
    return aircraftID;
}

// Compare two Aircraft objects by their IDs
bool Aircraft:: operator==(const Aircraft& other) const{
    return (aircraftID==other.aircraftID);
}

// Add a new aircraft to the fleet
void Aircraft :: addAircraft() {
    auto newAircraft = std::make_shared<Aircraft>(); // Create a new aircraft object
    cout << "Enter Flight ID: \n";
    cin >> newAircraft->aircraftID;
    cout << "Enter model: \n";
    cin >> newAircraft->model;
    cout << "Enter Total Seats: ";
    cin >> newAircraft->totalSeats;

    newAircraft->available = true;
    newAircraft->lastMaintenanceDate = "N/A"; // Default value

    aircraftFleet.push_back(newAircraft);
    cout << "Aircraft added successfully!\n";

    saveAircrafts(); // Save to JSON
}

// Display all aircraft in the fleet
void Aircraft::viewAircraft() {
    loadAircrafts(); // Reload the latest data from file
    if (aircraftFleet.empty()) {
        cout << "No aircrafts available in the fleet.\n";
        return;
    }

    cout << "--- Aircraft Fleet ---\n";
    for (const auto& aircraftPtr : aircraftFleet) {
        if (!aircraftPtr) continue; // Skip null pointers

        cout << "Aircraft ID: " << aircraftPtr->aircraftID << "\n"
             << "Model: " << aircraftPtr->model << "\n"
             << "Total Seats: " << aircraftPtr->totalSeats << "\n"
             << "Available: " << (aircraftPtr->available ? "Yes" : "No") << "\n"
             << "Last Maintenance Date: " << aircraftPtr->lastMaintenanceDate << "\n"
             << "-----------------------------\n";
    }
}

// Update the details of an aircraft with a given ID
void Aircraft :: updateAircraft(const std::string& id){
    for(auto& aircraftPtr : aircraftFleet){
        if(aircraftPtr && aircraftPtr->aircraftID == id){
          cout << "--- Update Aircraft " << id << " ---\n";
            cout << "Enter new model (current: " << aircraftPtr->model << "): ";
            cin >> aircraftPtr->model;

            cout << "Enter new total seats (current: " << aircraftPtr->totalSeats << "): ";
            cin >> aircraftPtr->totalSeats;

            cout << "Is the aircraft available? (1 = Yes, 0 = No): ";
            cin >> aircraftPtr->available;

            cout << "Enter last maintenance date (YYYY-MM-DD): ";
            cin >> aircraftPtr->lastMaintenanceDate;

            cout << "Aircraft " << id << " updated successfully!\n";

            saveAircrafts(); // Save changes

            return;
        }
        
    }
    cout << "Error: Aircraft with ID " << id << " not found.\n";
}

// Delete an aircraft from the fleet by ID
void Aircraft :: deleteAircraft(const std::string& id){
    for(auto it = aircraftFleet.begin(); it != aircraftFleet.end(); ++it){
        if( *it && (*it)->aircraftID == id){
            aircraftFleet.erase(it);
            cout << "Aircraft with ID " << id << " deleted successfully.\n";

            saveAircrafts(); // Save changes

            return;
        }
    }
    cout << "Error: Aircraft with ID " << id << " not found.\n";
}

// Set the availability status of an aircraft
void Aircraft :: setAvailability(bool status) {
    available = status;
}

// Return whether the aircraft is available
bool Aircraft :: isAvailable() const {
    return available;
}

// Placeholder function for assigning an aircraft to a flight
void Aircraft :: assignToFlight() {

}

// Placeholder function for performing maintenance on an aircraft
void Aircraft :: performMaintenance(std::string date) {

}
