#ifndef USER_H
#define USER_H

#include<iostream>
#include<string>

#include <fstream>
#include <string>
#include <filesystem> 
#include <nlohmann/json.hpp>
#include <functional>  
#include <memory>

using namespace std;
namespace fs = std::filesystem;
using json = nlohmann::json;

// class Administrator;
// class BookingAgent;
// class Passenger;


class User {
    private:
    int role;
    string username;
    string password;

    protected:
    std::unique_ptr<User> userInterface;

    public:
    // User(){ }

    virtual void showDashboard(void);

    virtual void process(void);

    void user_Inputs(void);

    bool user_verify();

    virtual ~User() = default;
};



#endif