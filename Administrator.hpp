#ifndef ADMINISTRATOR_H
#define ADMINISTRATOR_H

#include<iostream>
#include<string>

#include <fstream>
#include <string>
#include <filesystem> 
#include <nlohmann/json.hpp>
#include <functional>  
#include "User.hpp"
#include "MenuInterface.hpp"

using namespace std;
namespace fs = std::filesystem;
using json = nlohmann::json;

class Administrator : public User{
    private:
    int adminChoice;
    std::unique_ptr<MenuInterface> menu;

    public:
    void showDashboard() override;
    void process() override;

};

#endif