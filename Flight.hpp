#ifndef FLIGHT_H
#define FLIGHT_H

#include<iostream>
#include<string>
#include<vector>
#include<memory>
#include<filesystem>
#include<nlohmann/json.hpp>
#include "MenuInterface.hpp"
#include "JsonPersistence.hpp"

using namespace std;
namespace fs = std::filesystem;
using json = nlohmann::json;

class Flight : public MenuInterface, public JsonPersistence<Flight> {
private:
    // Flight data
    int flightChoice;                         
    string number;                            
    string origin;                            
    string destination;                       
    string depDateTime;                       
    string arrivalDateTime;                   
    string type;                              
    string status;                            
    int totalSeats;                           
    int availableSeats;                       
    string flightNumber;                      
    string flightPrice;                       
    int updateChoice;                         

    // Static members
    static string flightPath;                 
    static vector<shared_ptr<Flight>> flightList;

    // Crew details
    string pilotID;                           
    string pilotName;                         
    string attendantID;                       
    string attendantName;                     

    // Private methods
    void add_flight();                        
    void remove_flight();                     
    void update_flight();                     
    void update_flight_details(string t);     
    bool is_flight_available(const string& n);
    void assign_crew();                       
    void release_crew(const string& flightNum);
    void print_flights();                     

    // JSON persistence helpers
    static void saveFlights();                
    static void loadFlights();                

    // Seat booking
    std::map<std::string, std::string> bookedSeats;

public:
    // JSON persistence interface
    json toJson() const override;             
    void fromJson(const json& j) override;    
    bool operator==(const Flight& other) const;

    // Menu interface
    void showMenu() override;                 
    void processChoice() override;            

    // Additional functionality
    void get_flights();                       
    const std::string& getOrigin() const { return origin; }
    const std::string& getDestination() const { return destination; }
    const std::string& getPrice() const { return flightPrice; }
    std::string getStatus() const { return status; }
    static shared_ptr<Flight> getFlightByNumber(const string& number);

    void search_flights(const string& searchOrigin,
                        const string& searchDestination,
                        const string& searchDate);

    // Seat management
    bool isSeatAvailable(const string& flightNumber, const string& seat) const;
    bool bookSeat(const string& flightNumber, const string& seat, const string& passengerID);
    bool freeSeat(const std::string& seatNumber);

    string getDepartTime();                   
    string getFlightNumber();                 
    static void generateOperationalReport(const std::string& monthYear);
};

#endif
