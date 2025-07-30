#ifndef BOOKINGAGENT_H
#define BOOKINGAGENT_H

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

class BookingAgent : public User{
    private:
    int bookingChoice;

    public:
    void showDashboard() override;
    void process() override;

};

#endif