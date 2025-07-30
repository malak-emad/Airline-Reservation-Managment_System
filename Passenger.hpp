#ifndef PASSENGER_H
#define PASSENGER_H

#include<iostream>
#include<string>

#include <fstream>
#include <string>
#include <filesystem> 
#include <nlohmann/json.hpp>
#include <functional>  
#include "User.hpp"

using namespace std;
namespace fs = std::filesystem;
using json = nlohmann::json;

class Passenger : public User{
    private:
    int passengerChoice;

    public:
    void showDashboard() override;
    void process() override;

};

#endif