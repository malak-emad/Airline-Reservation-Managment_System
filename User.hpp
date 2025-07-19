#ifndef USER_H
#define USER_H

#include<iostream>
#include<string>

#include <fstream>
#include <string>
#include <filesystem> 
#include <nlohmann/json.hpp>
#include <functional>  

using namespace std;
namespace fs = std::filesystem;
using json = nlohmann::json;


class User{
    private:
    string role;
    string username;
    string password;

    public:
    User(){ }

    void showMenu();

    void processUser(void);

    void userInputs(void);

    bool verifyUser();




};



#endif