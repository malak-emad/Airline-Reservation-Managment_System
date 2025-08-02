#ifndef USER_H
#define USER_H

#include <iostream>
#include <string>
#include <fstream>
#include <filesystem>
#include <memory>
#include <functional>
#include <nlohmann/json.hpp>

#include "MenuInterface.hpp"
#include "JsonPersistence.hpp"   // Fixed case
#include "Dashboard.hpp"         // Consider composition instead of inheritance

using namespace std;
namespace fs = std::filesystem;
using json = nlohmann::json;

// ------------------------------------------------------------
// User Class
// Represents a user in the system with login credentials and role.
// Handles basic CRUD operations and JSON persistence.
// ------------------------------------------------------------
class User : public MenuInterface, public JsonPersistence<User>, public DashBoard {
private:
    int choice;                      // For menu choice handling
    string username;                 // Login username
    string password;                 // Login password
    string role;                     // Role: Admin, Passenger, etc.

    // MenuInterface overrides
    void showMenu() override;
    void processChoice() override;

    // Static shared storage for all users
    static std::vector<std::shared_ptr<User>> userList;

    // In-memory session activity log: {UserID, Action}
    static std::vector<std::pair<std::string,std::string>> activityLogs;

protected:
    std::string ID; // Unique user ID (string for flexibility)

public:
    // --------------------------------------------------------
    // Constructors
    // --------------------------------------------------------
    User() = default;  // Default constructor
    User(string u, string p, string id, string r) 
        : username(u), password(p), ID(id), role(r) {}

    // --------------------------------------------------------
    // Getters
    // --------------------------------------------------------
    std::string getUsername() const { return username; }
    std::string getPassword() const { return password; }
    std::string getID() const { return ID; }

    // --------------------------------------------------------
    // Setters
    // --------------------------------------------------------
    void setUsername(const std::string& u) { username = u; }
    void setPassword(const std::string& p) { password = p; }
    void setID(const std::string& id) { ID = id; }

    // Access user list
    static std::vector<std::shared_ptr<User>>& getUserList() {
        return userList;
    }

    // Equality operator: users are equal if IDs match
    bool operator==(const User& other) const;

    // --------------------------------------------------------
    // User management
    // --------------------------------------------------------
    bool isPassenger(const string& pID);

    void get_allUsers();                 // List all users
    void setUser();                      // Create new user
    static void updateUser(const std::string& id);
    static void deleteUser(const std::string& id);

    static void saveUsers();             // Save all users to JSON
    void loadUsers();                    // Load all users from JSON

    // --------------------------------------------------------
    // Authentication (to implement in .cpp)
    // --------------------------------------------------------
    void user_Inputs(void);              // Collect login info
    bool user_verify();                  // Verify credentials

    // --------------------------------------------------------
    // Activity Logging
    // --------------------------------------------------------
    static void generateUserActivityReport();             // From file
    static void logActivity(const std::string& userID, const std::string& action);
    static void showUserActivityReport();                 // In-memory

    // --------------------------------------------------------
    // JSON Persistence
    // --------------------------------------------------------
    json toJson() const override;
    void fromJson(const json& j);

    virtual ~User() = default;
};

#endif
