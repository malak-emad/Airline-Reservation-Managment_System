#include"Flight.hpp"


std::string flightPath = "flights.json";

void Flight :: showMenu(){
    std::cout<<"--- Manage Flights ---\n"
        <<"1. Add New Flight\n"
        <<"2. Update Existing Flight\n"
        <<"3. Remove Flight\n"
        <<"4. View All Flights\n"
        <<"5. Back to Main Menu\n ";
        processChoice();
}

void Flight :: processChoice(){
    cout<<"Enter choice:\n";
    cin>>flightChoice;
    switch(flightChoice) {
        case(1):
        cout<<"--- Add New Flight ---\n";
        add_flight();
        break;
        case(2):
        cout<<"--- Update Existing Flight ---\n";
        update_flight();
        break;
        case(3):
        cout<<"--- Remove Existing Flight ---\n";
        remove_flight();
        break;
        case(4):
        cout<<"--- Existing Flights ---\n";
        print_flights();
        break;
        case(5):
        return;
        break;
        default:
        cout<<"default";
        break;
    }
    showMenu();
}

bool Flight :: file_exists(){
    if (!fs::exists(flightPath)) {
        std::cerr << "File not found: " << flightPath << "\n";
        return false;
    }
    return true;
}


void Flight :: add_flight(){
    if(!file_exists()){
        cerr<< "Error in adding flight! try again later";
    }
    std::ifstream file(flightPath);
    json flightDetails;

    std::ifstream inFile("flights.json");
    if (inFile.is_open()) {
        inFile >> flightDetails;
        inFile.close();
    } else {
        // If file is missing or empty, start with empty array
        flightDetails = json::array();
    }

    cout << "Enter Flight Number: ";
    cin >> number;
    cout << "Enter Origin: ";
    cin.ignore();  // flush newline from previous input
    getline(cin, origin);
    cout << "Enter Destination: ";
    getline(cin, destination);
    cout << "Enter Departure Date and Time (YYYY-MM-DD HH:MM): ";
    getline(cin, depDateTime);
    cout << "Enter Arrival Date and Time (YYYY-MM-DD HH:MM): ";
    getline(cin, arrivalDateTime);
    cout << "Enter Aircraft Type: ";
    getline(cin, type);
    cout << "Enter Total Seats: ";
    cin >> totalSeats;
    cin.ignore(); 
    cout << "Enter Status (Scheduled/Delayed/Canceled): ";
    getline(cin, status);

    // Assign to JSON object
    json newFlight;
    newFlight["number"] = number;
    newFlight["origin"] = origin;
    newFlight["destination"] = destination;
    newFlight["depDateTime"] = depDateTime;
    newFlight["arrivalDateTime"] = arrivalDateTime;
    newFlight["type"] = type;
    newFlight["totalSeats"] = totalSeats;
    newFlight["status"] = status;


    // Add the new flight to the array
    flightDetails.push_back(newFlight);

    // Write back to the file
    ofstream outFile("flights.json");
    outFile << setw(4) << flightDetails << endl;
    cout<< "Flight " <<number <<" has been successfully added to the schedule.\n";
    outFile.close();
}

void Flight :: remove_flight(){
    cout << "Enter Flight Number to remove: \n";
    cin >> flightNumber;

    if(is_flight_available(flightNumber)){
        std::ifstream file(flightPath);
        json flightDetails;
        file >> flightDetails;
        file.close();

        bool removed = false;

        for (auto it = flightDetails.begin(); it != flightDetails.end(); ++it) {
            if ((*it)["number"] == flightNumber) {
                flightDetails.erase(it);
                removed = true;
                break;
            }
        }

        if (removed) {
            // Save the updated JSON array back to the file
            std::ofstream outFile(flightPath);
            outFile << flightDetails.dump(4); 
            outFile.close();

            cout << "Flight " << flightNumber << " has been successfully removed.\n";
            print_flights();
            // showMenu();
        }
    }
    else {
        cout << "Flight number does not exist.\n";
        // showMenu();
    }
}


void Flight :: update_flight(){
    cout << "Enter Flight Number to Update: \n";
    cin >> flightNumber;
    if(is_flight_available(flightNumber)){
        cout << "Select information to update: \n"
        <<"1. Flight Details \n"
        <<"2. Crew Assignments \n"
        <<"3. Status \n"
        <<"4. Back to Manage Flights \n";
        cin >> updateChoice;
        switch(updateChoice){
            case 1:
            cout<<"1. Flight Details\n";
            update_flight_details("details");
            break;
            case 2:
            cout<<"2. Crew Assignments\n";
            break;
            case 3:
            cout<<"3. status\n";
            update_flight_details("status");
            break;
            case 4:
            cout<<"4. Back to Manage Flights\n";
            showMenu();
            return;
        }
    }
    else{
        cout << "Flight number do not exists.\n";
        // showMenu();
    }
}

            
void Flight :: update_flight_details(string type){
    int fieldToUpdate;
    string update;
    bool updateStatus = false;
    vector<string> mapping = {"origin", "destination", "arrivalDateTime", "depDateTime",  "type", "totalSeats"};

    std::ifstream file(flightPath);
    json flightDetails;
    file >> flightDetails;
    for (auto& flight : flightDetails){
        if(flight["number"] == flightNumber){
            if(type == "details"){
                cout << "Choose the field you want to update: \n"
                <<"1. Origin \n"
                <<"2. Destination \n"
                <<"3. Arrival Date and Time (YYYY-MM-DD HH:MM) \n"
                <<"4. Departure Date and Time (YYYY-MM-DD HH:MM)  \n"
                <<"5. Aircraft Type \n"
                <<"6. Total Seats \n";
                cin >> fieldToUpdate;
                cin.ignore();
                cout << "Enter the update needed: \n";
                getline(cin, update);
                flight[mapping[fieldToUpdate]] = update;
                updateStatus = true;
            }
            else {
                cin.ignore();
                cout << "Enter the update needed: \n";
                getline(cin, update);
                flight["status"] = update;
                updateStatus = true;
            }
            // Save only if updated
            if (updateStatus) {
                std::ofstream outFile(flightPath);
                outFile << flightDetails.dump(4); 
                outFile.close();
                cout << "Updated Successfully!\n";
                print_flights();
                // showMenu();
                break;
            }
        }
    }
}



bool Flight :: is_flight_available(string num){
    if(file_exists()){
        std::ifstream file(flightPath);
        json flightDetails;
        file >> flightDetails;

        for (const auto& flight : flightDetails) {
            if (flight["number"] == num){
                return true;
            }
        }
    }
    return false;
}

void Flight :: print_flights(){
    if(file_exists()){
        std::ifstream file(flightPath);
        json flightDetails;
        file >> flightDetails;

    int count = 1;
    for (const auto& flight : flightDetails) {
        cout << count++ << ". Flight Number: \"" << flight["number"] << "\"\n"
            << "   Origin: \"" << flight["origin"] << "\"\n"
            << "   Destination: \"" << flight["destination"] << "\"\n"
            << "   Departure Date and Time (YYYY-MM-DD HH:MM): \"" << flight["depDateTime"] << "\"\n"
            << "   Arrival Date and Time (YYYY-MM-DD HH:MM): \"" << flight["arrivalDateTime"] << "\"\n"
            << "   Aircraft Type: \"" << flight["type"] << "\"\n"
            << "   Total Seats: \"" << flight["totalSeats"] << "\"\n"
            << "   Status (Scheduled/Delayed/Canceled): \"" << flight["status"] << "\"\n\n";
    }
    }
}

void Flight :: get_flights(){
    if(file_exists()){
        std::ifstream file(flightPath);
        json flightDetails;
        file >> flightDetails;

        cout << "---Flights---\n";
        int count = 1;
        for (const auto& flight : flightDetails) {
            cout << count++ << ". Flight Number: \"" << flight["number"] << "\"\n";
        }
    }
}