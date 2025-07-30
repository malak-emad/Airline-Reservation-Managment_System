#ifndef FLIGHT_H
#define FLIGHT_H

#include<iostream>
#include<string>

#include <fstream>
#include <string>
#include <filesystem> 
#include <nlohmann/json.hpp>
#include <functional>  

#include "MenuInterface.hpp"

using namespace std;
namespace fs = std::filesystem;
using json = nlohmann::json;

class Flight : public MenuInterface
{
    private:
    int flightChoice;
    std::string number, origin, destination, depDateTime, arrivalDateTime, type, status;
    int totalSeats;
    string flightNumber;
    int updateChoice;

    bool file_exists();
    void add_flight();
    void remove_flight();
    void update_flight();
    void update_flight_details(string t);
    bool is_flight_available(string n);
    void print_flights();

    protected:
    void showMenu() override;
    void processChoice() override;

    public: 
    void get_flights();

};

#endif